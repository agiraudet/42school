import { Injectable } from '@nestjs/common';
import { Chan } from './entities/chan.entity';
import { ChanStatusDto } from './dto/chan-status.dto';
import { Chatter } from './entities/chatter.entity';
import { ChanCreateDto } from './dto/chan-create.dto';
import { Socket } from 'socket.io';
import { User } from 'src/auth/user.entity';
import { JwtStrategy } from 'src/auth/jwt.strategy';
import { JwtPayload, decode } from 'jsonwebtoken';
import { InjectRepository } from '@nestjs/typeorm';
import { UserRepository } from 'src/auth/user.repository';
import { UserStatus } from 'src/user/user-status.enum';

@Injectable()
export class ChatService {
  constructor(
    private jwtStrategy: JwtStrategy,
    @InjectRepository(UserRepository)
    private userRepository: UserRepository,
  ) { }

  private chans: Chan[] = [];
  private chatters: Chatter[] = [];

  async updateStatus(client: Socket, status: string) {
    let chatter = this.getChatterFromSock(client);
    let newStatus = undefined;
    if (status === "ingame") {
      newStatus = UserStatus.IN_GAME;
    }
    else if (status === "offgame") {
      newStatus = await this.userRepository.getStatus(chatter.nick);
      if (newStatus === UserStatus.IN_GAME) {
        newStatus = UserStatus.ONLINE;
      }
    }
    this.userRepository.updateStatus(chatter.nick, newStatus);
  }

  async getUserFromToken(token: string): Promise<User> {
    const decodedToken = decode(token) as JwtPayload;
    const payload = { username: decodedToken?.username };
    try {
      return await this.jwtStrategy.validate(payload);
    } catch (error) {
      return undefined;
    }
  }

  getAllChansStatus(): ChanStatusDto[] {
    const chanList: ChanStatusDto[] = [];
    for (const chan of this.chans) {
      const newChanStatus = { name: chan.name, status: chan.status };
      chanList.push(newChanStatus);
    }
    return chanList;
  }

  getAllChansName(): string[] {
    const chanNameList: string[] = [];
    for (const chan of this.chans) {
      chanNameList.push(chan.name);
    }
    return chanNameList;
  }

  getChanChatterIn(chatterNick: string): string[] {
    const chanList: string[] = [];
    for (const chan of this.chans) {
      if (chan.members.includes(chatterNick)) {
        chanList.push(chan.name);
      }
    }
    return chanList;
  }

  createChan(chanData: ChanCreateDto): boolean {
    if (
      this.getAllChansName().includes(chanData.name) ||
      chanData.name[0] !== '#' ||
      chanData.name.length <= 1 ||
      chanData.name.length > 15 ||
      (chanData.status !== 'locked' && chanData.status !== 'public' && chanData.status !== 'private')
    ) {
      return false;
    }
    this.chans.push(new Chan(chanData.name, chanData.status, chanData.owner, chanData.password));
    return true;
  }

  getChan(chanName: string): Chan | undefined {
    return this.chans.find(chan => chan.name === chanName);
  }

  updateChanPasswd(chan: Chan, newPass: string): void {
    chan.password = newPass;
    if (newPass.length === 0 && chan.status === 'locked') {
      chan.status = 'public';
    }
    else {
      chan.status = 'locked';
    }
  }

  clientIsOnChan(chanName: string, client: Socket): boolean {
    const chatter = this.getChatterFromSock(client);
    const chan = this.getChan(chanName);
    return (chan.members.includes(chatter.nick));
  }

  addChatter(chatterNick: string, chatterSock: Socket) {
    this.chatters.push(new Chatter(chatterNick, chatterSock));
    this.userRepository.updateStatus(chatterNick, UserStatus.ONLINE);
  }

  removeChatter(chatter: Chatter) {
    this.userRepository.updateStatus(chatter.nick, UserStatus.OFFLINE);
    if (chatter) {
      const chanList = this.getChanChatterIn(chatter.nick);
      for (const chanName of chanList) {
        this.removeChatterFromChan(chatter.nick, chanName);
      }
      const index = this.chatters.indexOf(chatter);
      this.chatters.splice(index, 1);
    }
  }

  removeChatterFromChan(chatterNick: string, chanName: string) {
    const chan = this.getChan(chanName);
    if (chan) {
      const index = chan.members.indexOf(chatterNick);
      chan.members.splice(index, 1);
      if (chan.owner === chatterNick) {
        if (chan.admins.length) {
          chan.owner = chan.admins[0];
          chan.admins.splice(0, 1);
        }
        else if (chan.members.length) {
          chan.owner = chan.members[0];
        }
        else {
          const chanIndex = this.chans.indexOf(chan);
          this.chans.splice(chanIndex, 1);
        }
      }
    }
  }

  getAllChatters(): string[] {
    const nickList: string[] = [];
    for (const chatter of this.chatters) {
      nickList.push(chatter.nick)
    }
    return nickList;
  }

  getChatterFromNick(nick: string): Chatter | undefined {
    return this.chatters.find(chatter => chatter.nick === nick);
  }

  getChatterFromSock(sock: Socket): Chatter | undefined {
    return this.chatters.find(chatter => chatter.sock.id === sock.id);
  }

  chatterAllowedOnChan(chan: Chan, chatterName: string, password?: string): boolean {
    if (chan === undefined || (chan.banned.includes(chatterName) && chatterName !== chan.owner)) {
      return false;
    }
    if (chan.status === 'public') {
      return true;
    }
    else if (chan.status === 'private') {
      return (chan.admins.includes(chatterName) || chan.owner === chatterName || chan.invited.includes(chatterName));
    }
    else if (chan.status === 'locked') {
      return (password === chan.password);
    }
    return false;
  }

  chatterIsAdmin(chan: Chan, chatterNick: string): boolean {
    if (chan === undefined || (chatterNick !== chan.owner && !chan.admins.includes(chatterNick))) {
      return false;
    }
    return true;
  }

  chatterCanSpeak(chanName: string, client: Socket): boolean {
    const chan = this.getChan(chanName);
    const chatter = this.getChatterFromSock(client);
    if (chan && chatter) {
      if (chan.owner === chatter.nick) {
        return true;
      }
      if (this.chatterIsMute(chan, chatter.nick) > 0) {
        return false;
      }
      return true;
    }
    return false;
  }

  chatterIsMute(chan: Chan, chatterNick: string): number {
    if (!(chatterNick in chan.muted)) {
      return 0;
    }
    const currentTime = new Date().getTime();
    if (chan.muted[chatterNick] <= currentTime) {
      delete chan.muted[chatterNick];
      return 0;
    }
    else {
      return chan.muted[chatterNick] - currentTime;
    }
  }

  chatterMute(chan: Chan, chatterNick: string): void {
    const currentTime = new Date().getTime();
    let duration = this.chatterIsMute(chan, chatterNick);
    duration = duration === 0 ? 51000 : duration * 2;
    chan.muted[chatterNick] = currentTime + duration;
  }

  chatterBlock(chatter: Chatter, target: string, block: boolean): void {
    const index = chatter.blocked.indexOf(target);
    if (index < 0 && block) {
      chatter.blocked.push(target);
    }
    else if (index >= 0 && !block) {
      chatter.blocked.splice(index, 1);
    }
  }
}
