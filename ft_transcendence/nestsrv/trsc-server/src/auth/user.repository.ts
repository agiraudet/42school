import { ConflictException, Inject, Injectable, InternalServerErrorException } from "@nestjs/common";
import { DataSource, Repository } from "typeorm";
import { User } from "./user.entity";
import { AuthCredentialsDto } from "./dto/auth-credentials.dto";
import * as bcrypt from 'bcrypt';
import { authenticator } from "otplib";
import { toDataURL } from 'qrcode';
import { UserStatus } from "src/user/user-status.enum";
import { ConfigService } from "@nestjs/config";

@Injectable()
export class UserRepository extends Repository<User>
{
  constructor(
    private dataSource: DataSource,
    private config: ConfigService,
  ) {
    super(User, dataSource.createEntityManager());

  }

  async createUser(authCredentialsDto: AuthCredentialsDto): Promise<void> {
    const { username,
      password,
      email,
    } = authCredentialsDto;
    const salt = await bcrypt.genSalt();


    const hashedPassword = await bcrypt.hash(password, salt);
    const user = this.create({
      username,
      password: hashedPassword,
      email,
      twoFactorAuthenticationSecret: "",
      isTwoFactorAuthenticationEnabled: false,
      isFtStudent: false,
      ftId: '',
      friends: [],
      blocks: [],
      avatar: 'uploads/default-avatar.jpeg',
      userStatus: UserStatus.OFFLINE,
      gameTable: [],
      points: 0,
      wins: 0,
      loss: 0,
      isFirstCo: true,
    });
    try {
      await this.save(user);
    }
    catch (error) {
      console.log(error);
      if (error.code === '23505')
        throw new ConflictException('Username already exists');
      else
        throw new InternalServerErrorException();
    }
  }

  async createFtUser(username: string,
    email: string, ftId: string): Promise<void> {
    let checkDupli;
    let i = 0;
    while (checkDupli = await this.getUserFromName(username)) {
      if (checkDupli && i < 999999999999) {
        username = username + i;
      }
      i++;
    }
    const user = this.create({
      ftId: ftId,
      username: username,
      email: email,
      password: this.config.get('PWD_FT'), // (avoid warning: null value) we don't care about this password, since it is related to OAuth(42api)
      twoFactorAuthenticationSecret: "", // (warning: null value)
      isTwoFactorAuthenticationEnabled: false,
      isFtStudent: true,
      friends: [],
      blocks: [],
      avatar: 'uploads/default-avatar.jpeg',
      userStatus: UserStatus.OFFLINE,
      gameTable: [],
      points: 0,
      wins: 0,
      loss: 0,
      isFirstCo: true,
    });
    try {
      await this.save(user);
    }
    catch (error) {
      console.log(error.code);
      if (error.code === '23505')
        throw new ConflictException('Username already exists');
      else
        throw new InternalServerErrorException();
    }
  }

  async generateQrCodeDataURL(otpAuthUrl: string) {
    return toDataURL(otpAuthUrl);
  }

  async generateTwoFactorAuthenticationSecret(user: User) {
    const secret = authenticator.generateSecret();

    const otpauthUrl = authenticator.keyuri(user.email, 'AUTH_APP_NAME', secret);
    await this.setTwoFactorAuthenticationSecret(secret, user.id);
    return {
      secret,
      otpauthUrl
    }
  }

  async setTwoFactorAuthenticationSecret(secret: string, userId: string) {
    await this.update(userId, { twoFactorAuthenticationSecret: secret });
  }

  async updateId(userId: string, newId: string) {
    await this.update(userId, { id: newId });
  }

  async updateUsername(user: User, newUsername: string) {
    /* when used, the newUsername should go throught validation pipe using a DTO*/
    try {
      await this.update(user.id, { username: newUsername });
      await this.save(user);
      return true;
    } catch (error) {
      if (error.code === '23505') {  // '23505' is the error code for unique_violation in PostgreSQL.
        throw new ConflictException('Username already exists');
      } else {
        throw new InternalServerErrorException();
      }
    }
  }

  async updateStatus(username: string, newUserStatus: UserStatus) {
    const user = await this.findOneBy({ username: username });
    await this.update(user.id, { userStatus: newUserStatus });

  }

  async deactivate2fa(user: User) {
    await this.update(user.id, { isTwoFactorAuthenticationEnabled: false });
  }

  async getStatus(username: string): Promise<UserStatus> {
    const user = await this.findOneBy({ username: username });
    return user.userStatus;
  }

  async getUserFromName(username: string) {
    return await this.findOneBy({ username: username });
  }

  async turnOnTwoFactorAuthentication(userId: string) {
    await this.update({ id: userId }, { isTwoFactorAuthenticationEnabled: true });
  }

  async isFtStudent(ftId: string): Promise<boolean> {
    const query = this.createQueryBuilder('user');
    query.where({ ftId });
    query.andWhere('user.ftId = :ftId', { ftId });
    query.andWhere('user.isFtStudent = true');
    const user = await query.getOne();
    if (!user) {
      return false;
    }
    return true;
  }
}
