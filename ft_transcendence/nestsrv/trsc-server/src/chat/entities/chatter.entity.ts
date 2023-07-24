import { Socket } from "socket.io";

export class Chatter {
    nick: string;
    blocked: string[];
    sock: Socket;

    constructor(chatterNick: string, socket: Socket) {
        this.nick = chatterNick;
        this.sock = socket;
        this.blocked = [];
    }
}