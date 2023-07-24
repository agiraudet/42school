import { ExtractJwt, Strategy } from 'passport-jwt';
import { PassportStrategy } from '@nestjs/passport';
import { Injectable } from '@nestjs/common';
import { UserRepository } from './user.repository';
import { InjectRepository } from '@nestjs/typeorm';
import { User } from './user.entity';
import { ConfigService } from '@nestjs/config';


@Injectable()
export class Jwt2faStrategy extends PassportStrategy(Strategy, 'jwt-2fa') {
  constructor(
    @InjectRepository(UserRepository)
    private readonly userRepository: UserRepository,
    private config: ConfigService,
    ) {
    super({
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
      secretOrKey: config.get('JWT_SECRET'),
    });
  }

  async validate(payload: any) {
    const user = await this.userRepository.findOne(payload.email);
    if (!user.isTwoFactorAuthenticationEnabled) {
      return user;
    }
    if (payload.isTwoFactorAuthenticated) {
      return user;
    }
  }
}