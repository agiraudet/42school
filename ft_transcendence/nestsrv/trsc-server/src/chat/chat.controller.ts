import { Body, ConflictException, Controller, ForbiddenException, Get, Param, ParseIntPipe, Post, UseGuards } from '@nestjs/common';
import { ChatService } from './chat.service';
import { ChanStatusDto } from './dto/chan-status.dto';
import { ApiConflictResponse, ApiCreatedResponse, ApiForbiddenResponse, ApiOkResponse, ApiTags } from '@nestjs/swagger';
import { ChanCreateDto } from './dto/chan-create.dto';
import { ChatGateway } from './chat.gateway';
import { AuthGuard } from '@nestjs/passport';
import { GetUser } from 'src/auth/get-user.decorator';
import { User } from 'src/auth/user.entity';
import { UsrListDto } from './dto/usr-lst.dto';

@ApiTags('chat')
@Controller('chat')
@UseGuards(AuthGuard())
export class ChatController {
  constructor(private chatService: ChatService, private chatGateway: ChatGateway) { }

  @ApiOkResponse({ type: ChanStatusDto, isArray: true })
  @Get('chan-list')
  getChanList(): ChanStatusDto[] {
    return this.chatService.getAllChansStatus();
  }

  @ApiOkResponse({ type: String, isArray: true })
  @Get('chan-in')
  getChanListUserIsIn(
    @GetUser() user: User,
  ): string[] {
    return this.chatService.getChanChatterIn(user.username);
  }

  @ApiOkResponse({ type: String, isArray: true })
  @Get('chatter-list')
  getChatterList(): string[] {
    return this.chatService.getAllChatters();
  }

  @ApiCreatedResponse({ type: ChanStatusDto, isArray: false })
  @ApiConflictResponse()
  @Post('new-chan')
  createChan(
    @GetUser() user: User,
    @Body() body: ChanCreateDto
  ): ChanStatusDto {
    body.owner = user.username;
    if (this.chatService.createChan(body)) {
      const chanConfirmation = new ChanStatusDto;
      chanConfirmation.name = body.name;
      chanConfirmation.status = body.status;
      this.chatGateway.server.emit('newchan', '');
      return (chanConfirmation);
    }
    else {
      throw new ConflictException();
    }
  }

  @ApiCreatedResponse({ type: String })
  @ApiForbiddenResponse()
  @Get('opstatus/:chname')
  getOpStatus(
    @GetUser() user: User,
    @Param('chname') chName: string
  ) {
    const chan = this.chatService.getChan(chName);
    if (chan.owner === user.username) {
      return { status: 'owner' };
    }
    else if (chan.admins.includes(user.username)) {
      return { status: 'admin' };
    }
    else {
      return { status: 'none' };
    }
  }

  @ApiCreatedResponse({ type: UsrListDto, isArray: true })
  @Get('usrlst/:chname')
  getUsrInChatLst(@Param('chname') chName: string) {
    const chan = this.chatService.getChan(chName);
    const usrLst = new Array<UsrListDto>;
    for (const mem of chan.members) {
      let usrStatus = chan.admins.includes(mem) ? 'admin' : 'none';
      usrStatus = mem === chan.owner ? 'owner' : usrStatus;
      usrLst.push({ name: mem, status: usrStatus });
    }
    return usrLst;
  }

  @ApiCreatedResponse({ description: 'The user have joined the channel' })
  @ApiForbiddenResponse()
  @Post('join/:chname')
  joinChan(
    @Param('chname') chName: string,
    @GetUser() user: User,
    @Body() requestBody?: { chanPass: string }
  ): string {
    const chanPass = requestBody?.chanPass;
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    if (chan !== undefined && chatter !== undefined && this.chatGateway.addToChan(chatter, chan, chanPass)) {
      chan.members.push(chatter.nick);
      return 'Joined chan';
    }
    else {
      throw new ForbiddenException();
    }
  }

  @ApiCreatedResponse({ description: 'The user have been banned' })
  @ApiForbiddenResponse()
  @Post('ban/:chname/:target')
  banChatter(
    @GetUser() user: User,
    @Param('chname') chName: string,
    @Param('target') target: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    if (chan !== undefined && chatter !== undefined && !chan.banned.includes(target) && this.chatService.chatterIsAdmin(chan, chatter.nick) && chan.owner !== target) {
      chan.banned.push(target);
      this.chatGateway.informChan(chName, target, `got banned by ${user.username}.`);
      return `${target} is banned from ${chName}`;
    }
    else {
      throw new ForbiddenException();
    }
  }

  @ApiCreatedResponse({ description: 'The user have been kicked' })
  @ApiForbiddenResponse()
  @Post('kick/:chname/:target')
  kickChatter(
    @GetUser() user: User,
    @Param('chname') chName: string,
    @Param('target') target: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    const chatterTargeted = this.chatService.getChatterFromNick(target);
    if (chatterTargeted !== undefined && chan !== undefined && chatter !== undefined && this.chatService.chatterIsAdmin(chan, chatter.nick) && chan.owner !== target) {
      const index = chan.members.indexOf(target);
      chan.members.splice(index, 1);
      this.chatGateway.removeFromChan(chatterTargeted, chan);
      return `${target} is kicked from ${chName}`;
    }
    else {
      throw new ForbiddenException();
    }

  }

  @ApiCreatedResponse({ description: 'The user is now admin' })
  @ApiForbiddenResponse()
  @Post('op/:chname/:target')
  opChatter(
    @GetUser() user: User,
    @Param('chname') chName: string,
    @Param('target') target: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    const chatterTargeted = this.chatService.getChatterFromNick(target);
    if (chatterTargeted !== undefined && chan !== undefined && chatter !== undefined && chan.owner === chatter.nick) {
      if (chan.owner !== target) {
        const index = chan.admins.indexOf(target);
        if (index < 0) {
          chan.admins.push(target);
          this.chatGateway.informChan(chName, target, 'is now admin.');
          return `${target} is now admin on ${chName}`;
        }
        else {
          chan.admins.splice(index, 1);
          this.chatGateway.informChan(chName, target, 'is no longer admin.');
          return `${target} is no longer admin on ${chName}`;
        }
      }
    }
    else {
      throw new ForbiddenException();
    }
  }

  @ApiCreatedResponse({ description: 'The status has benn changed' })
  @ApiForbiddenResponse()
  @Post('status/:chname/:status')
  chgtStatus(
    @GetUser() user: User,
    @Param('chname') chName: string,
    @Param('status') status: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    if (chan !== undefined && chatter !== undefined && chan.owner === chatter.nick) {
      chan.status = status;
      this.chatGateway.informChan(chName, user.username, `has set the chan to ${status}.`);
      this.chatGateway.server.emit('newchan', '');
      return `new chan status: ${status}`;
    }
    else {
      throw new ForbiddenException();
    }
  }

  @ApiCreatedResponse({ description: 'The password has been updated' })
  @ApiForbiddenResponse()
  @Post('psswd/:chname/:pass')
  chgtPsswd(
    @GetUser() user: User,
    @Param('chname') chName: string,
    @Param('pass') pass: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    if (chan !== undefined && chatter !== undefined && chan.owner === chatter.nick) {
      if (chan.status !== 'locked') {
        this.chatGateway.informChan(chName, user.username, 'has set the chan to locked.');
      }
      this.chatService.updateChanPasswd(chan, pass);
      if (chan.status === 'locked') {
        this.chatGateway.informChan(chName, user.username, 'has changed the password.');
      }
      else {
        this.chatGateway.informChan(chName, user.username, 'has removed the password.');
      }
      this.chatGateway.server.emit('newchan', '');
      return `changed password on ${chName}`;
    }
    else {
      throw new ForbiddenException();
    }
  }

  @ApiCreatedResponse({ description: 'The user has been muted' })
  @ApiForbiddenResponse()
  @Post('mute/:chname/:target')
  muteChatter(
    @GetUser() user: User,
    @Param('chname') chName: string,
    @Param('target') target: string,
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    if (chan !== undefined && chatter !== undefined && this.chatService.chatterIsAdmin(chan, chatter.nick) && chan.owner !== target) {
      this.chatService.chatterMute(chan, target);
      const timeMuted = Math.floor(this.chatService.chatterIsMute(chan, target) / 10000);
      this.chatGateway.informChan(chName, target, `got muted by ${user.username} for ${timeMuted} min.`);
      return `${target} is now muted on ${chName}:`;
    }
    else {
      throw new ForbiddenException();
    }
  }

  @ApiCreatedResponse({ description: 'The user has been invited' })
  @ApiForbiddenResponse()
  @Post('inv/:chname/:target')
  inviteChatter(
    @GetUser() user: User,
    @Param('chname') chName: string,
    @Param('target') target: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    const chan = this.chatService.getChan(chName);
    const targetUser = this.chatService.getChatterFromNick(target);
    if (targetUser !== undefined && chan !== undefined && chatter !== undefined && this.chatService.chatterIsAdmin(chan, chatter.nick)) {
      if (!(chan.invited.includes(target))) {
        chan.invited.push(target);
        this.chatGateway.informChan(chName, target, `got invited by ${user.username}.`);
        this.chatGateway.informInv(chName, targetUser);
        return `${target} is now invited on ${chName}`;
      }
    }
    else {
      throw new ForbiddenException();
    }
  }

  @ApiCreatedResponse({ description: 'The user have been blocked' })
  @Post('block/:target')
  blockChatter(
    @GetUser() user: User,
    @Param('target') target: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    if (chatter !== undefined) {
      this.chatService.chatterBlock(chatter, target, true);
    }
    return `${target} is now blocked`;
  }

  @ApiCreatedResponse({ description: 'The user have been unblocked' })
  @Post('unblock/:target')
  unblockChatter(
    @GetUser() user: User,
    @Param('target') target: string
  ): string {
    const chatter = this.chatService.getChatterFromNick(user.username);
    if (chatter !== undefined) {
      this.chatService.chatterBlock(chatter, target, false);
    }
    return `${target} is now unblocked`;
  }
}
