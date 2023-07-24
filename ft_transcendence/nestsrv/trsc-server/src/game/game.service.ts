import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { GameTableRepository } from './game-table.repository';
import { AddGameDto } from './dto/add-game.dto';
import { User } from 'src/auth/user.entity';

@Injectable()
export class GameService {
    constructor(
        @InjectRepository(GameTableRepository) //repository
        private gameTableRepository: GameTableRepository,
    ) {}

    addGame(addGameDto: AddGameDto, user: User)
    {
        return this.gameTableRepository.addGame(addGameDto, user);
    }

    getGames(user: User)
    {
        return this.gameTableRepository.getGames(user);
    }

    getLadder()
    {
        return this.gameTableRepository.getLadder();
    }
}
