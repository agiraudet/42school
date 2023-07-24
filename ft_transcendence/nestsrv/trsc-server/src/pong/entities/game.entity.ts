import { GameStateDto } from "../dto/game-state.dto";
import { Ball } from "./ball.entity";
import { Player } from "./player.entity";
import { Socket } from 'socket.io';
import { Rules } from "./rules.entity";

export class Game {
    rules: Rules;
    id: string;
    playerA: Player;
    playerB: Player;
    ball: Ball;
    sockA: Socket;
    sockB: Socket;
    started: boolean;
    dto: GameStateDto;
    lastUpdate: number;
    updateRate: number;
    updateTimer: number;

    constructor(id: string, sockA: Socket, sockB: Socket, nameA: string, nameB: string, rules: Rules) {
        const padding = 50;
        this.rules = rules;
        this.id = id;
        this.playerA = new Player(padding, sockA.id, nameA, this.rules.dto);
        this.playerB = new Player(this.rules.canvSizeX - this.rules.plrSizeX - padding, sockB.id, nameB, this.rules.dto);
        this.ball = new Ball(this.rules.dto);
        this.sockA = sockA;
        this.sockB = sockB;
        this.started = false;
        this.dto = new GameStateDto();
        this.lastUpdate = 0;
        this.updateTimer = 1000;
        this.updateRate = 10;
        this.dto.updateRate = this.updateRate;
        this.dto.rulesDto = this.rules.dto;
        this.dto.id = this.id;
    }

    updateDto(): GameStateDto {
        this.ball.updateDto()
        this.playerA.updateDto();
        this.playerB.updateDto();
        this.dto.playerADto = this.playerA.dto;
        this.dto.playerBDto = this.playerB.dto;
        this.dto.ballDto = this.ball.dto;
        this.dto.started = this.started;
        this.dto.ts = this.lastUpdate;
        return this.dto;
    }

    init(): void {
        this.updateDto();
        this.sockA.emit('init', this.dto);
        this.sockB.emit('init', this.dto);
    }

    transmitState(): void {
        this.lastUpdate = Date.now();
        this.updateDto();
        this.sockA.emit('state', this.dto);
        this.sockB.emit('state', this.dto);
    }

    getPlayer(playerId: string): Player | undefined {
        if (playerId === this.sockA.id) {
            return this.playerA;
        }
        else if (playerId === this.sockB.id) {
            return this.playerB
        }
        else {
            return undefined;
        }
    }

    playerReady(playerId: string): void {
        let player = this.getPlayer(playerId);
        if (player) {
            console.log(`${playerId} ready`)
            player.setReady(true);
            if (this.sockA.id === playerId) {
                this.sockA.emit('status', `game ID #${this.id}`);
            }
            else if (this.sockB.id === playerId) {
                this.sockB.emit('status', `game ID #${this.id}`);
            }
        }
    }

    playerMoved(playerId:string, direction: string): void {
        let player = this.getPlayer(playerId);
        if (player) {
            player.direction = direction;
            this.transmitState();
        }
    }

    gameIsFinished(): boolean {
        const finished = (this.playerA.score >= this.rules.maxScore || this.playerB.score >= this.rules.maxScore);
        if (finished) {
            this.sockA.emit('end', 'finished');
            this.sockB.emit('end', 'finished');
        }
        return finished;
    }

    update(): void {
        let forceUpdate = false;
        this.started = (this.playerA.ready && this.playerB.ready);
        if (this.started) {
            forceUpdate = (
                this.ball.update(this.playerA, this.playerB) ||
                this.playerA.update() ||
                this.playerB.update()
            );
        }
        if (forceUpdate || Date.now() >= this.lastUpdate + this.updateTimer) {
            this.transmitState();
        }
    }
}