import { ConnectedSocket, MessageBody, SubscribeMessage, WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { PongService } from './pong.service';
import { MoveDto } from './dto/move.dto';
import { Injectable, UseGuards } from '@nestjs/common';
import { WsJwtGuard } from 'src/chat/chat.authguard';
import { ChatService } from 'src/chat/chat.service';

@Injectable()
@UseGuards(WsJwtGuard)
@WebSocketGateway({ cors: true , namespace: 'pong' })
export class PongGateway {
  constructor(private pongService: PongService) {}

  @WebSocketServer()
  server: Server;

  handleConnection(@ConnectedSocket() client: Socket): void {
    const token = client.handshake.headers.authorization;
    this.pongService.clientConnected(client, token)
  }

  handleDisconnect(@ConnectedSocket() client: Socket): void {
    this.pongService.clientDisconnected(client);
  }

  @SubscribeMessage('ready')
  handleReady(@ConnectedSocket() client: Socket, @MessageBody() gameId: string): void {
    this.pongService.playerReady(client.id, gameId);
  }

  @SubscribeMessage('move')
  handleMove(@ConnectedSocket() client: Socket, @MessageBody() data:{ id:string, direction:string } ): void {
    let moveDto = new MoveDto;
    moveDto.gameId = data.id;
    moveDto.direction = data.direction;
    this.pongService.playerMoved(client.id, moveDto);
  }
}
