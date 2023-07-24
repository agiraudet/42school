import { RulesDto } from "../dto/rules.dto";

export class Rules {
    allowXMvt: boolean;
    plrSizeX: number;
    plrSizeY: number;
    plrSpeed: number;
    maxScore: number;
    ballSize: number;
    ballSpeed: number;
    canvSizeX: number;
    canvSizeY: number;
    dto: RulesDto;

    constructor() {
        this.allowXMvt = false;
        this.plrSizeX = 10;
        this.plrSizeY = 70;
        this.plrSpeed = 4;
        this.maxScore = 11;
        this.ballSize = 15;
        this.ballSpeed = 4;
        this.canvSizeX = 640;
        this.canvSizeY = 480;
        this.dto = new RulesDto();
        this.updateDto();
    }

    updateDto() {
        this.dto.allowXMvt = this.allowXMvt;
        this.dto.plrSizeX = this.plrSizeX;
        this.dto.plrSizeY = this.plrSizeY;
        this.dto.plrSpeed = this.plrSpeed;
        this.dto.maxScore = this.maxScore;
        this.dto.ballSize = this.ballSize;
        this.dto.ballSpeed = this.ballSpeed;
        this.dto.canvSizeX = this.canvSizeX;
        this.dto.canvSizeY = this.canvSizeY;
    }

    setRules(rules: RulesDto) {
        this.allowXMvt = rules.allowXMvt;
        this.plrSizeX = rules.plrSizeX;
        this.plrSizeY = rules.plrSizeY;
        this.plrSpeed = rules.plrSpeed;
        this.maxScore = rules.maxScore;
        this.ballSize = rules.ballSize;
        this.ballSpeed = rules.ballSpeed;
        this.updateDto();
    }
}