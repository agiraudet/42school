import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthController } from './auth.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from './user.entity';
import { UserRepository } from './user.repository';
import { PassportModule } from '@nestjs/passport';
import { JwtModule } from '@nestjs/jwt';
import { JwtStrategy } from './jwt.strategy';
import { SchoolIntranetStrategy } from './ft-intra.strategy';
import { HttpModule } from '@nestjs/axios';
import { GameTableRepository } from 'src/game/game-table.repository';
import { ConfigModule, ConfigService } from '@nestjs/config';

@Module({
  imports: [
    HttpModule,
    PassportModule,
    PassportModule.register({defaultStrategy: 'jwt'}), 
    JwtModule.registerAsync({
      imports: [ConfigModule],
      inject: [ConfigService],
      useFactory: async (configService: ConfigService) => ({
        secret: configService.get('JWT_SECRET'),
        signOptions: {
          expiresIn: +configService.get('JWT_EXPIRATION_TIME'), //seconds (one hour)
        }
      }),
    }),
    TypeOrmModule.forFeature([User]),
  ],
  providers: [
    AuthService, 
    UserRepository, 
    JwtStrategy, 
    SchoolIntranetStrategy,
  ],
  controllers: [AuthController],
  exports: [
    JwtStrategy,
    PassportModule,
  ],
})
export class AuthModule {}
