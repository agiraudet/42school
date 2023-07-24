import { Module } from '@nestjs/common';
import { PongGateway } from './pong.gateway';
import { PongService } from './pong.service';
import { PongController } from './pong.controller';
import { JwtStrategy } from 'src/auth/jwt.strategy';
import { UserRepository } from 'src/auth/user.repository';
import { AuthModule } from 'src/auth/auth.module';
import { JwtModule } from '@nestjs/jwt';
import { GameTableRepository } from 'src/game/game-table.repository';

@Module({
  imports: [
    AuthModule,
    JwtModule.register({
      secret: 'topSecret51', // not safe
      signOptions: {
        expiresIn: 3600, //seconds (one hour)
      }
    }),
  ],
  providers: [
    PongGateway,
    PongService,
    JwtStrategy,
    UserRepository,
    GameTableRepository,
    ],
  controllers: [PongController]
})
export class PongModule {}
