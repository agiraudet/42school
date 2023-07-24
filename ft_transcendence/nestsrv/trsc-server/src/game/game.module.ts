import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AuthModule } from 'src/auth/auth.module';
import { GameTable } from './game-table.entity';
import { GameService } from './game.service';
import { UserRepository } from 'src/auth/user.repository';
import { GameTableRepository } from './game-table.repository';
import { GameController } from './game.controller';

@Module({
    imports: [
        TypeOrmModule.forFeature([GameTable]),
        AuthModule,
    ],
    controllers: [
        GameController,
    ], 
    providers: [
        GameService,
        UserRepository,
        GameTableRepository,
    ],
})

export class GameModule {}
