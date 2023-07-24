<template>
  <div class="game-result">
    <p class="players">{{ playerA }} - {{ playerB }}</p>
    <p class="scores">{{ scoreA }} - {{ scoreB }}</p>
    <p class="status">{{ status }}</p>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue';

export default defineComponent({
  name: 'GameResult',
  data() {
    return {
      playerA: '',
      playerB: '',
      scoreA: 0,
      scoreB: 0,
      statusCode: '',
      status: '',
    }
  },

  mounted() {
    this.playerA = this.$route.params.plrA as string;
    this.playerB = this.$route.params.plrB as string;
    this.scoreA = parseInt(this.$route.params.scA as string);
    this.scoreB = parseInt(this.$route.params.scB as string);
    this.statusCode = this.$route.params.stc as string;
    switch(this.statusCode) {
      case 'deco':
        this.status = 'The opponent has left the game!';
        break;
      case 'A':
        this.status = `${this.playerA} wins the game!`;
        break;
      case 'B':
        this.status = `${this.playerB} wins the game!`;
        break;
    }
  }
})
</script>

<style scoped>
.game-result {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: fit-content;
  background-color: #262626;
  border-radius: 8px;
  border: solid 1px white;
  text-align: center;
  color: #888888;
  max-width: 500px;
  margin: auto;
}

.players {
  font-size: 24px;
  font-weight: bold;
  margin-bottom: 5px;
}

.scores {
  font-size: 48px;
  color: #FFFFFF;
}

.status {
  font-size: 18px;
  margin-top: 5px;
}

</style>
