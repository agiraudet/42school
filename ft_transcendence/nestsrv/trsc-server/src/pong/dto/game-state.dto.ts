import { BallDto } from "./ball.dto";
import { PlayerDto } from "./player.dto";
import { RulesDto } from "./rules.dto";

export class GameStateDto {
    id: string;
    started: boolean;
    playerADto: PlayerDto;
    playerBDto: PlayerDto;
    ballDto: BallDto;
    rulesDto: RulesDto;
    updateRate: number;
    ts: number;
}