import { Inject, Injectable } from '@nestjs/common';
import { Game } from './entities/game.entity';
import { Socket } from 'socket.io';
import { MoveDto } from './dto/move.dto';
import { Interval } from '@nestjs/schedule';
import { decode } from 'jsonwebtoken';
import { JwtPayload } from 'src/auth/jwt-payload.interface';
import { JwtStrategy } from 'src/auth/jwt.strategy';
import { User } from 'src/auth/user.entity';
import { Rules } from './entities/rules.entity';
import { InjectRepository } from '@nestjs/typeorm';
import { UserRepository } from 'src/auth/user.repository';
import { UserStatus } from 'src/user/user-status.enum';
import { AddGameDto } from 'src/game/dto/add-game.dto';
import { GameTableRepository } from 'src/game/game-table.repository';
import { ChatService } from 'src/chat/chat.service';

interface IVsGame { usrA: string, usrB: string, sckA: Socket | null, sckB: Socket | null, accepted: boolean, rules: Rules }
@Injectable()
export class PongService {
  constructor(
    private jwtStrategy: JwtStrategy,
    @InjectRepository(UserRepository)
    private userRepository: UserRepository,
    @InjectRepository(GameTableRepository)
    private gameTableRepository: GameTableRepository,
  ) { }

  private games: { [id: string]: Game } = {};
  private waitList: Socket[] = [];
  private vsWaitList: IVsGame[] = [];

  async getUserFromToken(token: string): Promise<User> {
    const decodedToken = decode(token) as JwtPayload;
    const payload = { username: decodedToken?.username };
    try {
      return await this.jwtStrategy.validate(payload);
    } catch (error) {
      console.error(error);
      return undefined;
    }
  }

  async getNameFromSock(client: Socket): Promise<string> {
    const token = client.handshake.headers.authorization;
    const user = await this.getUserFromToken(token);
    if (user !== undefined) {
      return user.username;
    }
    return '';
  }

  addToWaitList(sock: Socket): void {
    this.waitList.push(sock);
    sock.emit('status', 'looking for an opponent');
    this.resolveWaitList();
  }

  addToVsWaitList(from: string, to: string, rules: Rules) {
    const vsGame = { usrA: from, usrB: to, sckA: null, sckB: null, accepted: false, rules: rules };
    const index = this.userInVsWaitList(from);
    if (index === -1) {
      this.vsWaitList.push(vsGame);
    }
    else {
      if (this.vsWaitList[index].usrA === from) {
        this.vsWaitList[index] = vsGame;
      }
      else {
        this.refuseVsGame(from, to);
      }
    }
  }

  userInVsWaitList(username: string): number {
    let index = 0;
    for (const vs of this.vsWaitList) {
      if (vs.usrA === username || vs.usrB === username) {
        return index;
      }
      index++;
    }
    return -1;
  }

  clientInVsWaitList(client: Socket): number {
    let index = 0;
    for (const vs of this.vsWaitList) {
      if (vs.sckA === client || vs.sckB === client) {
        return index;
      }
      index++;
    }
    return -1;
  }

  removeFromVsWaitList(client: Socket) {
    const index = this.clientInVsWaitList(client);
    if (index !== -1) {
      this.vsWaitList.splice(index, 1);
    }
  }

  removeFromWaitList(sock: Socket): void {
    const index = this.waitList.indexOf(sock);
    if (index > -1) {
      this.waitList.splice(index, 1);
    }
  }

  async createGame(sockA: Socket, sockB: Socket, rules: Rules): Promise<string> {
    const id = Math.random().toString(36).slice(2, 7);
    const nameA = await this.getNameFromSock(sockA);
    const nameB = await this.getNameFromSock(sockB);
    const game = new Game(id, sockA, sockB, nameA, nameB, rules);
    this.games[id] = game;
    sockA.emit('status', 'about to start');
    sockB.emit('status', 'about to start');
    game.init();
    return id;
  }

  createVsGame(index: number) {
    this.createGame(this.vsWaitList[index].sckA, this.vsWaitList[index].sckB, this.vsWaitList[index].rules);
    this.vsWaitList.splice(index, 1);
  }

  resolveWaitList(): void {
    if (this.waitList.length > 1) {
      this.createGame(this.waitList.shift(), this.waitList.shift(), new Rules());
    }
  }

  clientInGame(clientId: string): string {
    for (const gameId in this.games) {
      if (this.games[gameId].getPlayer(clientId) !== undefined) {
        return gameId;
      }
    }
    return undefined;
  }

  async clientConnected(client: Socket, token: string) {
    const user = await this.getUserFromToken(token);
    const index = this.userInVsWaitList(user.username);

    if (index !== -1) {
      if (this.vsWaitList[index].usrA === user.username) {
        this.vsWaitList[index].sckA = client;
        client.emit('status', `waiting for ${this.vsWaitList[index].usrB}`)
      }
      else if (this.vsWaitList[index].accepted) {
        this.vsWaitList[index].sckB = client;
      }
      else {
        this.addToWaitList(client);
      }
      if (this.vsWaitList[index].sckA != null && this.vsWaitList[index].sckB != null) {
        this.createVsGame(index);
      }
    }
    else {
      this.addToWaitList(client);
    }
  }

  clientDisconnected(client: Socket) {
    const clientId = client.id;
    this.removeFromVsWaitList(client);
    this.removeFromWaitList(client);
    const gameId = this.clientInGame(clientId);
    if (gameId !== undefined) {
      const game = this.games[gameId];
      this.updateGameHistoDeco(game, client);
      const remainingClient = (clientId === game.sockA.id) ? game.sockB : game.sockA;
      remainingClient.emit('end', "Opponent disconnected");
      delete this.games[gameId];
      this.addToWaitList(remainingClient);
    }
  }

  findVsGame(plrA: string, plrB: string): number {
    let index = 0;
    for (const vs of this.vsWaitList) {
      if (vs.usrA === plrA && vs.usrB === plrB) {
        return index;
      }
      index++;
    }
    return -1;
  }

  acceptVsGame(plrB: string, plrA: string): boolean {
    const index = this.findVsGame(plrA, plrB);
    if (index !== -1) {
      this.vsWaitList[index].accepted = true;
      return true;
    }
    return false;
  }

  refuseVsGame(plrB: string, plrA: string) {
    const index = this.findVsGame(plrA, plrB);
    if (index !== -1) {
      if (this.vsWaitList[index].sckA != null) {
        this.vsWaitList[index].sckA.emit('status', `${this.vsWaitList[index].usrB} refused the invite.`);
      }
      this.vsWaitList.splice(index, 1);
    }
  }

  playerReady(playerId: string, gameId: string) {
    this.games[gameId].playerReady(playerId);
  }

  playerMoved(playerId: string, moveDto: MoveDto) {
    this.games[moveDto.gameId].playerMoved(playerId, moveDto.direction);
  }

  async updateGameHistoDeco(game: Game, deco: Socket) {
    const plrADto: AddGameDto = {
      isWinner: (game.playerB.id === deco.id),
      points: (game.playerB.id === deco.id) ? 10 : -5,
      opponent: game.playerB.name,
      scoreUser: game.playerA.score,
      scoreOpponent: game.playerB.score,
    }
    const plrBDto: AddGameDto = {
      isWinner: (game.playerA.id === deco.id),
      points: (game.playerA.id === deco.id) ? 10 : -5,
      opponent: game.playerA.name,
      scoreUser: game.playerB.score,
      scoreOpponent: game.playerA.score,
    }
    const userA = await this.userRepository.findOneBy({ username: game.playerA.name });
    const userB = await this.userRepository.findOneBy({ username: game.playerB.name });
    this.gameTableRepository.addGame(plrADto, userA);
    this.gameTableRepository.addGame(plrBDto, userB);
  }

  async updateGameHistory(game: Game) {
    const plrADto: AddGameDto = {
      isWinner: (game.playerA.score > game.playerB.score),
      points: (game.playerA.score > game.playerB.score) ? 10 : -5,
      opponent: game.playerB.name,
      scoreUser: game.playerA.score,
      scoreOpponent: game.playerB.score,
    }
    const plrBDto: AddGameDto = {
      isWinner: (game.playerB.score > game.playerA.score),
      points: (game.playerB.score > game.playerA.score) ? 10 : -5,
      opponent: game.playerA.name,
      scoreUser: game.playerB.score,
      scoreOpponent: game.playerA.score,
    }
    const userA = await this.userRepository.findOneBy({ username: game.playerA.name });
    const userB = await this.userRepository.findOneBy({ username: game.playerB.name });
    this.gameTableRepository.addGame(plrADto, userA);
    this.gameTableRepository.addGame(plrBDto, userB);
  }

  @Interval(10)
  updateGames(): void {
    for (const gameId in this.games) {
      const game = this.games[gameId];
      game.update();
      if (game.gameIsFinished()) {
        this.updateGameHistory(game);
        delete this.games[gameId];
      }
    }
  }
}
