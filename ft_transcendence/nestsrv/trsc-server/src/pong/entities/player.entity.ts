import { PlayerDto } from "../dto/player.dto";
import { RulesDto } from "../dto/rules.dto";

export class Player {
    id: string;
    name: string;
    x: number;
    y: number;
    score: number;
    ready: boolean;
    dto: PlayerDto;
    direction: string;
    rules: RulesDto;

    constructor(x: number, id: string, name: string, rules: RulesDto) {
        this.id = id;
        this.name = name;
        this.x = x;
        this.y = 200;
        this.score = 0;
        this.ready = false;
        this.dto = new PlayerDto();
        this.direction = 'none';
        this.rules = rules;
        this.dto.id = this.id;
        this.dto.name = this.name;
    }

    updateDto(): void {
        this.dto.x = this.x;
        this.dto.y = this.y;
        this.dto.score = this.score;
        this.dto.ready = this.ready;
        this.dto.direction = this.direction;
    }

    setReady(ready: boolean): void {
        this.ready = ready;
    }

    moveIfLegal(move: number): boolean {
        if (this.y + move > 0 && this.y + move + this.rules.plrSizeY < this.rules.canvSizeY) {
            this.y += move;
            return true;
        }
        return false;
    }

    update(): boolean {
        let legal = false;
        switch (this.direction) {
            case 'up':
                legal = this.moveIfLegal(-this.rules.plrSpeed);
                break;
            case 'down':
                legal = this.moveIfLegal(this.rules.plrSpeed);
                break;
            default:
                legal = true;
                break;
        }
        if (!legal) {
            this.direction = 'none';
        }
        return (!legal);
    }

}