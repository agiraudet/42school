import { ConflictException, Injectable, ServiceUnavailableException, UnauthorizedException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { UserRepository } from './user.repository';
import { AuthCredentialsDto } from './dto/auth-credentials.dto';
import * as bcrypt from 'bcrypt';
import { JwtService } from '@nestjs/jwt';
import { JwtPayload } from './jwt-payload.interface';
import { authenticator } from 'otplib';
import { User } from './user.entity';
import { toDataURL } from 'qrcode';
import { AuthSigninDto } from './dto/auth-signin.dto';
import { access } from 'fs';
import { UserService } from 'src/user/user.service';
import { UserStatus } from 'src/user/user-status.enum';

@Injectable()
export class AuthService {
    constructor(
        @InjectRepository(UserRepository)
        private userRepository: UserRepository,
        private jwtService: JwtService,
    ) {}

    async signUp(authCredentialsDto: AuthCredentialsDto): Promise<void>
    {
        return this.userRepository.createUser(authCredentialsDto);
    }

    async signIn(authCredentialsDto: AuthSigninDto): Promise<{accessToken: string}>
    {
        const {username, password, twoFactorAuthenticationCode} = authCredentialsDto;
        const user = await this.userRepository.findOneBy({username: username});
        if (user && (user.userStatus == UserStatus.IN_GAME || user.userStatus == UserStatus.ONLINE))
        {
          throw new ConflictException("User already online");
        }
        if (user && (await bcrypt.compare(password, user.password)) && !user.isTwoFactorAuthenticationEnabled
            && !user.isFtStudent)
        {
            const payload : JwtPayload = {username};
            const accessToken : string = await this.jwtService.sign(payload);
            return { accessToken };
        }
        else if (user && user.isTwoFactorAuthenticationEnabled && !user.isFtStudent)
        {
          throw new ServiceUnavailableException('Redirect 2FA'); //503
        }
        else
        {
            throw new UnauthorizedException('Please check your login credentials'); // 401
        }
    }

    async signInFt(ftId: string, username: string): Promise<{accessToken: string}>
    {
        const user = await this.userRepository.findOneBy({ftId: ftId});
        if (user && (user.userStatus == UserStatus.IN_GAME || user.userStatus == UserStatus.ONLINE))
        {
          throw new ConflictException("User already online");
        }
        if (user  && !user.isTwoFactorAuthenticationEnabled)
        {
            username = user.username;
            const payload : JwtPayload = {username};
            const accessToken : string = await this.jwtService.sign(payload);
            return { accessToken };
        }
        else if (user && user.isTwoFactorAuthenticationEnabled)
        {
          throw new ServiceUnavailableException('Redirect 2FA'); //503
        }
        else
        {
            throw new UnauthorizedException('Please check your login credentials');
        }
    }

    async signInFt2FA(ftId: string, twoFactorAuthenticationCode: string,username: string): Promise<{accessToken: string}>
    {
        const user = await this.userRepository.findOneBy({ftId: ftId});
        if (user && (user.userStatus == UserStatus.IN_GAME || user.userStatus == UserStatus.ONLINE))
        {
          throw new ConflictException("User already online");
        }
        if (user  && !user.isTwoFactorAuthenticationEnabled)
        {
            username = user.username;
            const payload : JwtPayload = {username};
            const accessToken : string = await this.jwtService.sign(payload);
            return { accessToken };
        }
        else if (user && user.isTwoFactorAuthenticationEnabled)
        {
          const isCodeValid = this.isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode, user);
          if (!isCodeValid)
          {
            throw new UnauthorizedException('Wrong authentication code');
          }
          const {email, access_token} = await this.loginWith2fa(user);
          const accessToken: string = access_token;
          return { accessToken};
        }
        else
        {
            throw new UnauthorizedException('Please check your login credentials');
        }
    }

    async signIn2FA(authCredentialsDto: AuthSigninDto): Promise<{accessToken: string}>
    {
        const {username, password, twoFactorAuthenticationCode} = authCredentialsDto;
        const user = await this.userRepository.findOneBy({username: username});
        if (user && (await bcrypt.compare(password, user.password)) && !user.isTwoFactorAuthenticationEnabled 
            && !user.isFtStudent)
        {
            const payload : JwtPayload = {username};
            const accessToken : string = await this.jwtService.sign(payload);
            return { accessToken };
        }
        else if (user && user.isTwoFactorAuthenticationEnabled)
        {
            const isCodeValid = this.isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode, user);
            if (!isCodeValid)
            {
              throw new UnauthorizedException('Wrong authentication code');
            }
            const {email, access_token} = await this.loginWith2fa(user);
            const accessToken: string = access_token;
            return { accessToken};
        }
        else
        {
            throw new UnauthorizedException('Please check your login credentials');
        }
    }

    isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode: string, user: User) {
      return authenticator.verify({
        token: twoFactorAuthenticationCode,
        secret: user.twoFactorAuthenticationSecret,
      });
    }

    async generateQrCodeDataURL(otpAuthUrl: string) {
      return toDataURL(otpAuthUrl);
    }
    async loginWith2fa(userWithoutPsw: User) {
        const payload = {
          email: userWithoutPsw.email,
          username: userWithoutPsw.username,
          isTwoFactorAuthenticationEnabled: !!userWithoutPsw.isTwoFactorAuthenticationEnabled,
          isTwoFactorAuthenticated: true,
        };
    
        return {
          email: payload.email,
          access_token: this.jwtService.sign(payload),
        };
      }

      deactivate2fa(user: User)
      {
        return this.userRepository.deactivate2fa(user);
      }
}
