import { Body, Controller, Get, NotFoundException, Param, Post, UseGuards } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { GameService } from './game.service';
import { AddGameDto } from './dto/add-game.dto';
import { GetUser } from 'src/auth/get-user.decorator';
import { User } from 'src/auth/user.entity';
import { UserRepository } from 'src/auth/user.repository';
import { InjectRepository } from '@nestjs/typeorm';
import { LadderDto } from './dto/ladder.dto';

@Controller('game')
@UseGuards(AuthGuard())
export class GameController {
    constructor(
        @InjectRepository(UserRepository)
        private userRepository: UserRepository,
        private gameService: GameService)
    {}
    
    @Post()
    addGame(@Body() addGameDto: AddGameDto, 
            @GetUser() user: User)
    {
        return this.gameService.addGame(addGameDto, user);
    }

    @Get('/history/:user')
    async getUserGames(@Param('user') username: string)
    {
        const user = await this.userRepository.getUserFromName(username);
        if (user == null) {
            throw new NotFoundException();
        }
        return this.gameService.getGames(user); 
    }

    @Get('/history')
    getGames(@GetUser() user: User)
    {
        return this.gameService.getGames(user);
    }

    @Get('/ladder')
    async getLadder()
    {
        let ladder: LadderDto[] = [];
        const userList = await this.gameService.getLadder();
        for (const user of userList) {
            ladder.push({name: user.username, points: user.points});
        }
        return ladder;
    }
}
