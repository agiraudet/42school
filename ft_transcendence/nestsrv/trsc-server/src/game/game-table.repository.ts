import { Injectable, NotFoundException } from "@nestjs/common";
import { DataSource, Repository } from "typeorm";
import { GameTable } from "./game-table.entity";
import { AddGameDto } from "./dto/add-game.dto";
import { User } from "src/auth/user.entity";
import { NotFoundError } from "rxjs";
import { InjectRepository } from "@nestjs/typeorm";
import { UserRepository } from "src/auth/user.repository";


@Injectable()
export class GameTableRepository extends Repository<GameTable>
{
    constructor(
        @InjectRepository(UserRepository)
        private userRepository: UserRepository,
        private dataSource: DataSource,
        )
    {
        super(GameTable, dataSource.createEntityManager());
    }
    
    async addGame(addGameDto: AddGameDto, user: User) : Promise <GameTable>
    {
        const {isWinner, points, opponent, scoreUser, scoreOpponent} = addGameDto;
        const game = this.create({
            user, isWinner, points, opponent, scoreUser, scoreOpponent,
        });
        await this.save(game); 
        const newPoints = user.points + points;
        await this.userRepository.update(user.id, {points: newPoints});
        if (isWinner == true)
        {
            const newWins = user.wins + 1;
            await this.userRepository.update(user.id, {wins: newWins});
        }
        else
        {
            const newLoss = user.loss + 1;
            await this.userRepository.update(user.id, {loss: newLoss});
        }
        return game;
    }

    async getGames(user : User) : Promise<GameTable[]>
    {
        const query = this.createQueryBuilder('gameTable');
        query.where({user});
        const games = await query.getMany();
        if (!games)
            throw new NotFoundException('The user has not played yet');
        return games;
    }

    async getLadder() : Promise<User[]>
    {
        const users = await this.userRepository.find({
            order: {
              points: 'DESC', // Or 'ASC' for ascending
            },
          });
        return users;
    }
}