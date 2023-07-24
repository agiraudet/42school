import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AuthModule } from 'src/auth/auth.module';
import { BlockController, UserController } from './user.controller';
import { UserService } from './user.service';
import { UserRepository } from 'src/auth/user.repository';
import { Friend } from './friend.entity';
import { Block } from './block.entity';
import { FriendRepository } from './friend.repository';
import { BlockRepository } from './block.repository';

@Module({
    imports: [
        TypeOrmModule.forFeature([Friend, Block]),
        AuthModule,
    ],
    controllers: [UserController, BlockController],
    providers: [
        UserService, 
        UserRepository, 
        FriendRepository, 
        BlockRepository,
    ],
})
export class UserModule {}
