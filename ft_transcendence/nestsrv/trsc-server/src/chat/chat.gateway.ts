import { ConnectedSocket, SubscribeMessage, WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { ChatService } from './chat.service';
import { Server, Socket } from 'socket.io';
import { Injectable, UseGuards } from '@nestjs/common';
import { Chatter } from './entities/chatter.entity';
import { Chan } from './entities/chan.entity';
import { ChatMsgDto } from './dto/chat-msg.dto';
import { WsJwtGuard } from './chat.authguard';
import { InviteDto } from './dto/invite.dto';

@Injectable()
@UseGuards(WsJwtGuard)
@WebSocketGateway({ namespace: 'chat', cors: true })
export class ChatGateway {
  constructor(private chatService: ChatService) { }

  @WebSocketServer()
  server: Server;

  statusUpdated() {
    this.server.emit('newco');
  }

  async addChatter(client: Socket, token: string) {
    const user = await this.chatService.getUserFromToken(token);
    if (user === undefined) {
      return;
    }
    const nick = user.username;
    this.chatService.addChatter(nick, client);
    client.emit('nick', nick);
    this.server.emit('newco');
  }

  handleConnection(@ConnectedSocket() client: Socket): void {
    const auth_token = client.handshake.headers.authorization;
    this.addChatter(client, auth_token);
  }

  handleDisconnect(@ConnectedSocket() client: Socket): void {
    const chatter = this.chatService.getChatterFromSock(client);
    if (chatter) {
      this.chatService.removeChatter(chatter);
    }
    this.server.emit('newco');
    this.server.emit('newchan');
  }

  @SubscribeMessage('msg')
  handleMessage(client: Socket, payload: ChatMsgDto): void {
    if (payload.to[0] === '#') {// && client.rooms.has(payload.to)) { // Msg to Chan
      if (this.chatService.clientIsOnChan(payload.to, client)) {
        if (this.chatService.chatterCanSpeak(payload.to, client)) {
          this.server.to(payload.to).emit('msg', payload);
        }
      }
    }
    else { // Msg Priv
      const target = this.chatService.getChatterFromNick(payload.to);
      if (target !== undefined) {
        this.server.to(target.sock.id).emit('msg', payload);
        this.server.to(client.id).emit('msg', payload);
      }
      else {
        this.emitError(client.id, "user not found", payload);
      }
    }
  }

  @SubscribeMessage('invGame')
  handleInv(client: Socket, payload: InviteDto) {
    const chatter = this.chatService.getChatterFromNick(payload.to);
    chatter.sock.emit('invGame', payload);
  }

  @SubscribeMessage('updateStatus')
  updateStatus(client: Socket, status: string) {
    this.chatService.updateStatus(client, status);
    this.server.emit('newco');
  }

  addToChan(chatter: Chatter, chan: Chan, password?: string): boolean {
    if (chatter !== undefined && chan !== undefined && this.chatService.chatterAllowedOnChan(chan, chatter.nick, password)) {
      chatter.sock.join(chan.name);
      this.informChan(chan.name, chatter.nick, 'has joined the chan.');
      return true;
    }
    else {
      return false;
    }
  }

  removeFromChan(chatter: Chatter, chan: Chan): void {
    this.informChan(chan.name, chatter.nick, 'has left the chan.');
    chatter.sock.leave(chan.name);
    chatter.sock.emit('newchan');
  }

  emitError(targetId: string, error: string, arg: ChatMsgDto): void {
    const userNick = arg.from;
    switch (error) {
      case 'user not found':
        arg.from = arg.to;
        arg.body = error;
        arg.to = userNick;
        break;
    }
    this.server.to(targetId).emit('msg', arg);
  }

  informChan(chanName: string, target: string, info: string): void {
    this.server.to(chanName).emit('msg', {
      to: chanName,
      from: chanName,
      body: `${target} ${info}`
    });
  }

  informInv(chanName: string, chatter: Chatter): void {
    chatter.sock.emit('inv', chanName);
  }

  cancelGameInv(username: string, from: string): void {
    const chatter = this.chatService.getChatterFromNick(username);
    chatter?.sock.emit('cancelInv', from)
  }
}
