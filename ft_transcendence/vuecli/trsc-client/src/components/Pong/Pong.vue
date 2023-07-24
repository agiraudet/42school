<template>
  <div class="pong">
    <div class="score">
      <p v-if="gameState.playerADto !== undefined"> {{ gameState.playerADto.name }} <i> vs </i> {{
        gameState.playerBDto.name }}</p>
      {{ scoreA }} - {{ scoreB }}<br>
      <i>{{ status }}</i>
    </div>
    <div class="canv-cont">
      <canvas ref="canv" class="canv" style="border: 1px solid black;"></canvas>
    </div>
  </div>
</template>

<script lang="ts">
import { io, Socket } from 'socket.io-client';
import { defineComponent } from 'vue';
import { authToken, hostname } from '@/globalProperties';
import type { IRules } from './rules.interface';
import useEventsBus from '@/eventBus';

interface IPlayer {
  name: string;
  id: string;
  x: number;
  y: number;
  score: number;
  ready: boolean;
  direction: string;
}

interface IBall {
  y: number;
  x: number;
  velX: number;
  velY: number;
  lastPaddleHit: number;
  paddleHitCD: number;
}

interface IGameState {
  id: string;
  started: boolean;
  playerADto: IPlayer;
  playerBDto: IPlayer;
  ballDto: IBall;
  rulesDto: IRules;
  updateRate: number;
  ts: number;
}

export default defineComponent({
  name: 'Pong',
  data() {
    return {
      finished: false,
      status: '',
      scoreA: 0,
      scoreB: 0,
      lastUpdate: 0,
      keyDownPressed: false,
      keyUpPressed: false,
      gameState: {} as IGameState,
      socket: {} as Socket,
      canv: {} as HTMLCanvasElement,
      context: {} as CanvasRenderingContext2D | null,
      socketOptions: {
        transportOptions: {
          polling: {
            extraHeaders: {
              Authorization: authToken.value,
            }
          }
        }
      },
    }
  },

  created() {
    this.socket = io(`${hostname.value}/pong`, this.socketOptions);
    const { emit } = useEventsBus();
    emit('updateStatus', 'ingame');
  },

  mounted() {
    window.addEventListener('resize', this.handleResize);
    window.addEventListener('keydown', this.handleKey);
    window.addEventListener('keyup', this.handleKey);
    this.canv = this.$refs.canv as HTMLCanvasElement;
    this.context = this.canv.getContext("2d");
    this.socket.on('init', data => {
      this.socket.emit('ready', data.id);
      this.gameState = data;
    });
    this.socket.on('state', data => {
      this.gameState = data;
      this.scoreA = data.playerADto.score;
      this.scoreB = data.playerBDto.score;
      this.lastUpdate = data.ts;
    });
    this.socket.on('end', data => {
      this.finished = true;
      this.status = data;
      const statusCode = this.getStatusCode();
      this.$router.push({
        name: 'g-res',
        params: {
          plrA: this.gameState.playerADto.name,
          plrB: this.gameState.playerBDto.name,
          scA: this.scoreA,
          scB: this.scoreB,
          stc: statusCode,
        }
      })
    })
    this.socket.on('status', data => {
      this.status = data;
    })
    this.handleResize();
    this.gameLoop();
  },

  beforeUnmount() {
    this.socket.close();
    window.removeEventListener('resize', this.handleResize);
    window.removeEventListener('keydown', this.handleKey);
    window.removeEventListener('keyup', this.handleKey);
    const { emit } = useEventsBus();
    emit('updateStatus', 'offgame');
  },

  methods: {

    handleResize() {
      const ratio = 640 / 480;
      let containerWidth = this.canv.parentElement?.offsetWidth || 0;
      let containerHeight = this.canv.parentElement?.offsetHeight || 0;
      if (containerWidth === undefined || containerHeight === undefined) { return; }

      this.canv.width = containerWidth;
      this.canv.height = containerWidth / ratio;

      if (this.canv.height > containerHeight) {
        this.canv.height = containerHeight;
        this.canv.width = containerWidth * ratio;
      }
      this.renderGame();
    },

    getStatusCode(): string {
      if (this.status === 'Opponent disconnected') {
        return 'deco';
      }
      else {
        return this.scoreA > this.scoreB ? 'A' : 'B';
      }
    },

    renderPlayer(player: IPlayer) {
      const rules = this.gameState.rulesDto;
      this.renderScale(player.x, player.y, rules.plrSizeX, rules.plrSizeY);
    },

    renderBall() {
      const ball = this.gameState.ballDto;
      const rules = this.gameState.rulesDto;
      this.renderScale(ball.x, ball.y, rules.ballSize, rules.ballSize);
    },

    renderScale(posX: number, posY: number, sizeX: number, sizeY: number) {
      const scaleX = this.canv.width / this.gameState.rulesDto.canvSizeX;
      const scaleY = this.canv.height / this.gameState.rulesDto.canvSizeY;
      this.context?.fillRect(posX * scaleX, posY * scaleY, sizeX * scaleX, sizeY * scaleY);
    },

    renderGame() {
      if (!this.context) { return; }
      this.context.clearRect(0, 0, this.canv.width, this.canv.height);
      this.context.fillStyle = '#000000';
      this.context.fillRect(0, 0, this.canv.width, this.canv.height);
      this.context.fillStyle = '#FFFFFF';
      if (this.gameState.id) {
        this.renderPlayer(this.gameState.playerADto);
        this.renderPlayer(this.gameState.playerBDto);
        this.renderBall();
      }
    },

    checkCollision(direction: string): boolean {
      const player = (this.gameState.playerADto.id === this.socket.id) ? this.gameState.playerADto : this.gameState.playerBDto;
      const rules = this.gameState.rulesDto;
      if (direction === 'up') {
        return (player.y - rules.plrSpeed > 0);
      }
      if (direction === 'down') {
        return (player.y + rules.plrSpeed + rules.plrSizeY < rules.canvSizeY);
      }
      return true;
    },

    move() {
      let direction = '';
      if (this.keyDownPressed === this.keyUpPressed) {
        direction = 'none';
      }
      if (this.keyDownPressed) {
        direction = 'down';
      }
      else if (this.keyUpPressed) {
        direction = 'up';
      }
      else {
        direction = 'none';
      }
      if (this.checkCollision(direction)) {
        this.socket.emit('move', { id: this.gameState.id, direction: direction });
      }
    },

    handleKey(event: KeyboardEvent) {
      if (!this.gameState || !this.gameState.started) { return; }
      if (event.type === 'keydown') {
        if (event.key === 'ArrowDown' || event.key === 'ArrowUp') {
          event.preventDefault();
        }
        if (event.key === 'ArrowDown' && !this.keyDownPressed) {
          this.keyDownPressed = true;
        }
        else if (event.key === 'ArrowUp' && !this.keyUpPressed) {
          this.keyUpPressed = true;
        }
        this.move();
      }
      else if (event.type === 'keyup') {
        if (event.key === 'ArrowDown') {
          this.keyDownPressed = false;
        }
        else if (event.key === 'ArrowUp') {
          this.keyUpPressed = false;
        }
        this.move();
      }
    },

    checkBallCollision(player: IPlayer, nbUpdate: number) {
      const ball = this.gameState.ballDto;
      const currentTime = Date.now();
      if (
        currentTime > ball.lastPaddleHit + ball.paddleHitCD &&
        ball.x < player.x &&
        ball.x + this.gameState.rulesDto.ballSize > player.x &&
        ball.y < player.y + this.gameState.rulesDto.plrSizeY &&
        ball.y + this.gameState.rulesDto.ballSize > player.y
      ) {
        ball.velX *= -1;
        ball.x += (ball.velX * nbUpdate);
        ball.lastPaddleHit = currentTime;
      }
    },

    checkBallPlr(plrx: number, plry:number, nbUpdate: number) {
      const ball = this.gameState.ballDto;
      const currentTime = Date.now();
      if (
        currentTime > ball.lastPaddleHit + ball.paddleHitCD &&
        ball.x < plrx &&
        ball.x + this.gameState.rulesDto.ballSize > plrx &&
        ball.y > plry &&
        ball.y < plry + this.gameState.rulesDto.plrSizeY
      ) {
        ball.velX *= -1;
        ball.x += (ball.velX * nbUpdate);
        ball.lastPaddleHit = currentTime;
      }

    },

    checkBallCollBorder(nbUpdate: number) {
      const ball = this.gameState.ballDto;
      if (ball.y < 0 || ball.y + this.gameState.rulesDto.ballSize >= this.gameState.rulesDto.canvSizeY) {
        ball.velY *= -1;
        ball.y += (ball.velY * nbUpdate);
      }
    },

    moveBall(nbUpdate: number) {
      this.gameState.ballDto.x += (this.gameState.ballDto.velX * nbUpdate);
      this.gameState.ballDto.y += (this.gameState.ballDto.velY * nbUpdate);
      // this.checkBallCollision(this.gameState.playerADto, nbUpdate);
      // this.checkBallCollision(this.gameState.playerBDto, nbUpdate);
      this.checkBallPlr(this.gameState.playerADto.x + this.gameState.rulesDto.plrSizeX, this.gameState.playerADto.y, nbUpdate);
      this.checkBallPlr(this.gameState.playerBDto.x, this.gameState.playerBDto.y, nbUpdate);
      this.checkBallCollBorder(nbUpdate);
    },

    movePlayer(player: IPlayer, nbUpdate: number) {
      if (player.direction === 'up') {
        player.y -= (this.gameState.rulesDto.plrSpeed * nbUpdate);
      }
      else if (player.direction === 'down') {
        player.y += (this.gameState.rulesDto.plrSpeed * nbUpdate);
      }
    },

    moveElems() {
      if (!this.gameState || !this.gameState.started) { return; }
      const currentTime = Date.now();
      const nbUpdate = (currentTime - this.lastUpdate) / this.gameState.updateRate;
      this.moveBall(nbUpdate);
      this.movePlayer(this.gameState.playerADto, nbUpdate);
      this.movePlayer(this.gameState.playerBDto, nbUpdate);
      this.lastUpdate = currentTime;
    },

    gameLoop() {
      if (this.finished) { return; }
      this.moveElems();
      this.renderGame();
      requestAnimationFrame(this.gameLoop);
    },
  }
})
</script>

<style>
.pong {
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
}

.score {
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  font-size: larger;
  font-weight: bolder;
}

.score i {
  font-weight: lighter;
  font-size: medium;
}

.canv-cont {
  position: relative;
  width: 60%;
  height: 0;
  padding-bottom: 45%;
  border: 3px solid white;
  box-sizing: border-box;
  overflow: hidden;
}

.canv {
  position: absolute;
  top: -3px;
  left: -3px;
  width: calc(100% + 6px);
  height: calc(100% + 6px);
}
</style>
