import { Module } from '@nestjs/common';
import { ChatGateway } from './chat.gateway';
import { ChatController } from './chat.controller';
import { ChatService } from './chat.service';
import { AuthModule } from 'src/auth/auth.module';
import { JwtModule } from '@nestjs/jwt';
import { JwtStrategy } from 'src/auth/jwt.strategy';
import { UserRepository } from 'src/auth/user.repository';

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
    ChatGateway,
    ChatService,
    JwtStrategy,
    UserRepository
  ],
  controllers: [ChatController],
})
export class ChatModule {}
