import { Body, Controller, Get, HttpCode, ImATeapotException, InternalServerErrorException, NotAcceptableException, Param, Post, Req, Res, StreamableFile, UnauthorizedException, UploadedFile, UseGuards, UseInterceptors } from '@nestjs/common';
import { AuthCredentialsDto } from './dto/auth-credentials.dto';
import { AuthService } from './auth.service';
import { AuthGuard } from '@nestjs/passport';
import { GetUser } from './get-user.decorator';
import { User } from './user.entity';
import { InjectRepository } from '@nestjs/typeorm';
import { UserRepository } from './user.repository';
import { AuthSigninDto } from './dto/auth-signin.dto';
import { ApiTags } from '@nestjs/swagger';
import { Auth2faDto } from './dto/auth-2fa.dto';
import { JwtService } from '@nestjs/jwt';
import { NotFoundError } from 'rxjs';
import { FileInterceptor } from '@nestjs/platform-express';
import { diskStorage } from 'multer';
import { extname, join } from 'path';
import { createReadStream } from 'fs';
import * as fs from 'fs';
import * as path from 'path';
import { UsernameDto } from './dto/username.dto';
import { JwtPayload } from 'jsonwebtoken';

@ApiTags('auth')
@Controller('auth')
export class AuthController {
  constructor(
    @InjectRepository(UserRepository)
    private userRepository: UserRepository,
    private jwtService: JwtService,
    private authService: AuthService) { }

  @UseGuards(AuthGuard())
  @Get('/validate')
  validateUser(@GetUser() user: User) {
    if (user.isFtStudent && user.isFirstCo) {
      throw new ImATeapotException('First CO as FT student, please redirect to changer username page');
    }
    return user.username;
  }

  @Post('/update/username')
  @UseGuards(AuthGuard())
  async updateUsername(@GetUser() user: User,
    @Body() usernameDto: UsernameDto) {
    const { username } = usernameDto;
    const res = await this.userRepository.updateUsername(user, username);
    if (res == true) {
      user.isFirstCo = false;
      user.username = username;
      try {
        await this.userRepository.save(user);
      }
      catch (error) {
        throw new InternalServerErrorException();
      }
    }
    const payload: JwtPayload = { username };
    const accessToken: string = await this.jwtService.sign(payload);
    return { accessToken };
  }

  @Post('/signup')
  signUp(@Body() authCredentialsDto: AuthCredentialsDto): Promise<void> {
    return this.authService.signUp(authCredentialsDto);
  }

  @Post('/signin')
  signIn(@Body() authCredentialsDto: AuthSigninDto): Promise<{ accessToken: string }> {
    const token = this.authService.signIn(authCredentialsDto);
    return token;
  }

  @Post('/2fa/signin')
  signIn2Fa(@Body() authCredentialsDto: AuthSigninDto): Promise<{ accessToken: string }> {
    const token = this.authService.signIn2FA(authCredentialsDto);
    return token;
  }

  @Get('2fa/generate')
  @UseGuards(AuthGuard())
  async generateQrCode(@GetUser() user: User) {
    const obj = await this.userRepository.generateTwoFactorAuthenticationSecret(user);
    const qr = await this.userRepository.generateQrCodeDataURL(obj.otpauthUrl);
    return qr;
  }

  @Post('2fa/turn-on')
  @UseGuards(AuthGuard())
  async turnOnTwoAuthentication(
    @GetUser() user: User,
    @Body() auth2faDto: Auth2faDto) {
    const { twoFactorAuthenticationCode } = auth2faDto;
    const isCodeValid = this.authService.isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode,
      user);
    if (!isCodeValid) {
      throw new UnauthorizedException('Wrong authentication code');
    }
    await this.userRepository.turnOnTwoFactorAuthentication(user.id);
  }

  @Post('2fa/authenticate')
  @HttpCode(200)
  @UseGuards(AuthGuard())
  async autheticate(@GetUser() user: User, @Body() body) {
    const isCodeValid = this.authService.isTwoFactorAuthenticationCodeValid(
      body.twoFactorAuthenticationCode,
      user,
    );

    if (!isCodeValid) {
      throw new UnauthorizedException('Wrong authentication code');
    }

    return this.authService.loginWith2fa(user);
  }

  @Get('deactivate-2fa')
  @UseGuards(AuthGuard())
  deactivate2fa(@GetUser() user: User) {
    this.authService.deactivate2fa(user);
    return true;
  }

  @Get('is2fa')
  @UseGuards(AuthGuard())
  isUser2Fa(@GetUser() user: User) {
    if (user.isTwoFactorAuthenticationEnabled == true)
      return true;
    return false;
  }
  // This route will redirect the user to your school's OAuth server
  @Get('school')
  @UseGuards(AuthGuard('school')) // Attaching the Guard that uses your SchoolIntranetStrategy
  async schoolAuth(@Req() req) { }

  // The route that the OAuth server will redirect back to
  @Post('school/callback')
  @UseGuards(AuthGuard('school')) // Attaching the Guard that uses your SchoolIntranetStrategy
  async schoolCallback(@Body('code') code: string, @Req() req) {
    // After successful login, the user object will be set at req.user.
    /*
      based on 42 ID 
      search if this id  already exists
      if it doesn't exist :
      create account 
        then sign token
      if it exists
        fetch account then
        sign token 
    */
    const res = await this.userRepository.isFtStudent(req.user.id);
    if (!res) {
      this.userRepository.createFtUser(req.user.username, req.user.email, req.user.id);
      return await this.authService.signInFt(req.user.id, req.user.username);
    }
    return await this.authService.signInFt(req.user.id, req.user.username);
  }

  @Post('school/callback2fa')
  @UseGuards(AuthGuard('school')) // Attaching the Guard that uses your SchoolIntranetStrategy
  async schoolCallback2fa(@Body('code') code: string,
    @Body() auth2faDto: Auth2faDto,
    @Req() req) {
    const { twoFactorAuthenticationCode } = auth2faDto;
    const res = await this.userRepository.isFtStudent(req.user.id);
    if (!res) {
      await this.userRepository.createFtUser(req.user.username, req.user.email, req.user.id);
      return await this.authService.signInFt(req.user.id, req.user.username);
    }
    const userVerif = await this.userRepository.findOneBy({ ftId: req.user.id });
    if (!userVerif || userVerif.isTwoFactorAuthenticationEnabled == false) {
      return this.authService.signInFt(req.user.id, req.user.username);
    }
    return this.authService.signInFt2FA(req.user.id, twoFactorAuthenticationCode, req.user.username);
  }


  @Post('upload')
  @UseInterceptors(FileInterceptor('file', {
    storage: diskStorage({
      destination: './uploads', // This sets the destination of the uploaded files
      filename: (req, file, cb) => {
        // This function sets the name of the file
        const randomName = Array(32).fill(null).map(() => (Math.round(Math.random() * 16)).toString(16)).join('')
        return cb(null, `${randomName}${extname(file.originalname)}`)
      }
    }),
    limits: { fileSize: 1024 * 1024 }, // Here, you are limiting the file size to 1MB
  }))
  @UseGuards(AuthGuard())
  async uploadFile(@UploadedFile() file: Express.Multer.File,
    @GetUser() user: User
  ) {
    await this.userRepository.update(user.id, { avatar: file.path });
    return { message: 'File uploaded successfully' };
  }

  @Get('avatar')
  @UseGuards(AuthGuard())
  serveAvatar(@GetUser() user: User, @Res({ passthrough: true }) res: Response) {
    const file = path.join(process.cwd(), user.avatar);
    if (!fs.existsSync(file)) {
      throw new NotAcceptableException('Avatar not found.');
    }
    try {
      const filee = fs.readFileSync(file);
      const base64image = filee.toString('base64');
      return base64image;
    } catch (error) {
      console.log(error);
    }
  }

  @Get('avatar/:username')
  @UseGuards(AuthGuard())
  async getAvatarByUsername(@GetUser() user: User,
    @Res({ passthrough: true }) res: Response,
    @Param('username') username: string) {
    const userToFind = await this.userRepository.findOneBy({ username: username });
    const file = path.join(process.cwd(), userToFind.avatar);
    if (!fs.existsSync(file)) {
      throw new NotAcceptableException('Avatar not found.');
    }
    try {
      const filee = fs.readFileSync(file);
      const base64image = filee.toString('base64');
      return base64image;
    } catch (error) {
      console.log(error);
    }
  }
}
