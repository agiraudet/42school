import { BallDto } from "../dto/ball.dto";
import { RulesDto } from "../dto/rules.dto";
import { Player } from "./player.entity";

export class Ball {
  x: number;
  y: number;
  velX: number;
  velY: number;
  dto: BallDto;
  paddleHitCD: number;
  lastPaddleHit: number;
  rules: RulesDto;

  constructor(rules: RulesDto) {
    this.rules = rules;
    this.paddleHitCD = 100;
    this.dto = new BallDto();
    this.dto.paddleHitCD = this.paddleHitCD;
    this.reset();
  }

  updateDto() {
    this.dto.x = this.x;
    this.dto.y = this.y;
    this.dto.velX = this.velX;
    this.dto.velY = this.velY;
    this.dto.lastPaddleHit = this.lastPaddleHit;
  }

  randomizeDirection(): void {
    const magnitude = this.rules.ballSpeed;
    let angle = Math.random() * Math.PI;
    while (angle > 1.3 && angle < 1.8) {
      angle = Math.random() * Math.PI;
    }
    this.velX = Math.cos(angle) * magnitude;
    this.velY = Math.sin(angle) * magnitude;
  }

  reset(): void {
    this.x = 320;
    this.y = 240;
    this.randomizeDirection();
    this.lastPaddleHit = 0;
  }

  checkCollPlr(plrx: number, plry: number): boolean {
    const currentTime = Date.now();
    if (
      currentTime > this.lastPaddleHit + this.paddleHitCD &&
      this.x < plrx &&
      this.x + this.rules.ballSize > plrx &&
      this.y > plry &&
      this.y < plry + this.rules.plrSizeY
    ) {
      this.velX *= -1;
      this.x += this.velX;
      this.lastPaddleHit = currentTime;
      return true;
    }
    return false;
  }

  checkCollisionPlayer(player: Player, padding: number): boolean {
    const currentTime = Date.now();
    if (
      currentTime > this.lastPaddleHit + this.paddleHitCD &&
      this.x < player.x + padding &&
      this.x + this.rules.ballSize > player.x - padding &&
      this.y < player.y + this.rules.plrSizeY + padding &&
      this.y + this.rules.ballSize > player.y - padding
    ) {
      this.velX *= -1;
      this.x += this.velX;
      this.lastPaddleHit = currentTime;
      return true;
    }
    return false;
  }

  checkCollisionBorder(canvasSizeY: number, padding: number): boolean {
    if (this.y < 0 + padding || this.y + this.rules.ballSize + padding >= canvasSizeY) {
      this.velY *= -1;
      this.y += this.velY;
      return true;
    }
    return false;
  }

  checkScore(playerA: Player, playerB: Player): boolean {
    if (this.x < 0) {
      playerB.score += 1;
      this.reset();
      return true;
    }
    else if (this.x + this.rules.ballSize > this.rules.canvSizeX) {

      playerA.score += 1;
      this.reset();
      return true;
    }
    return false;
  }

  move() {
    this.x += this.velX;
    this.y += this.velY;
  }

  update(playerA: Player, playerB: Player): boolean {
    const padding = 0;
    this.move();
    let forceUpate = (
      this.checkScore(playerA, playerB) ||
      this.checkCollPlr(playerA.x + this.rules.plrSizeX, playerA.y) ||
      this.checkCollPlr(playerB.x, playerB.y) ||
      // this.checkCollisionPlayer(playerA, padding) ||
      // this.checkCollisionPlayer(playerB, padding) ||
      this.checkCollisionBorder(this.rules.canvSizeY, padding)
    );
    return forceUpate;
  }
}
