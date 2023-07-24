<template>
  <div class="loading" v-if="loading">
    <i>loading...</i>
  </div>
  <div class="state-stats" v-else>
    <div class="profile-header" v-if="userExist">
      <div class="pic-name">
        <Avatar :msg="userName" />
        <h2>{{ userName }}</h2>
      </div>
      <div class="profile-menu" v-if="self">
        <button @click="goToAccount()">settings</button>
      </div>
      <div class="profile-menu" v-else>
        <button v-if="!isFriend" @click="addFriend()">add friend</button>
        <button v-else @click="removeFriend()">remove friend</button>
      </div>
    </div>
	<!-- UP DONE -->
    <div class="user-stats" v-if="userExist">
      <div class="no-stats" v-if="stats.nMatch <= 0">
        <i>{{ userName }} have not played a single match yet !</i>
      </div>
      <div class="stats" v-if="stats.nMatch > 0">
        <div class="stat-winrate">
          {{ stats.nMatch }}G
          {{ stats.wins }}W
          {{ stats.loss }}L<br>
          <b>{{ stats.winrate }}%</b>
        </div>
        <div class="stat-minmax">
          Max: {{ stats.maxScore }}<br>
          Min: {{ stats.minScore }} <br>
          Avg: {{ stats.avgScore }}
        </div>
        <div class="rank">
          xp: {{ stats.xp }}<br>
          rank: {{ rank }}
        </div>
      </div>
      <div class="histo">
        <div v-for="(match, index) in histo" :key="index" :class="{
          match,
          won: match.isWinner,
          lost: !match.isWinner,
        }">
          {{ userName }} {{ match.scoreUser }} <i>vs</i> {{ match.scoreOpponent }} {{ match.opponent }}
        </div>
      </div>
    </div>
    <div class="no-user-stats" v-else>
      <i>User not found.</i>
    </div>
  </div>
</template>

<script lang="ts">
import { authToken, hostname, nick } from "@/globalProperties";
import { defineComponent, ref } from 'vue';
import { MatchStats, type IMatch } from "./MatchStats";
import { LadderClass } from '@/components/Ladder/LadderClass';
import Avatar from '@/components/Profile/Avatar.vue';

export default defineComponent({
  name: 'MatchHisto',
  components: {
    Avatar,
  },

  data() {
    return {
      ladder: new LadderClass(),
      histo: [] as Array<IMatch>,
      stats: new MatchStats(),
      loading: true,
      userExist: true,
      isFriend: false,
      self: false,
      userName: '',
      rank: 0,
    }
  },

  mounted() {
    this.userName = this.$route.params.username as string;
    if (this.userName === '>self<') {
      this.self = true;
      this.userName = nick.value;
    }
    this.loadStats();
  },

  methods: {

    goToAccount() {
      this.$router.push({ name: 'account' });
    },

    async loadIsfriend() {
      if (!this.self) {
        const is = await this.userIsFriend();
        if (is) {
          this.isFriend = true;
        }
        else {
          this.isFriend = false;
        }
      }
    },

    async loadStats() {
      this.loadIsfriend();
      await this.getMatchHisto();
      await this.ladder.getLadder();
      this.rank = this.ladder.ladder.findIndex((lad) => lad.name === this.userName) + 1;
      this.loading = false;
    },

    async userIsFriend() {
      const requestOption = {
        method: 'GET',
        headers: {
          'Authorization': `Bearer ${authToken.value}`,
          'accept': 'application/json',
        }
      }
      return fetch(`${hostname.value}/user/isfriend/${this.userName}`, requestOption)
        .then(response => response.json())
        .catch(error => { 
          //console.error(error);
        });
    },

    async getMatchHisto() {
      const requestOption = {
        method: 'GET',
        headers: {
          'Authorization': `Bearer ${authToken.value}`,
          'accept': 'application/json',
        }
      }
      return fetch(`${hostname.value}/game/history/${this.userName}`, requestOption)
        .then(response => {
          if (response.status === 404) {
            this.userExist = false;
          }
          return response.json()
        })
        .then(data => {
          if (this.userExist) {
            this.histo = data;
            this.stats.setStat(data);
          }
        })
        .catch(error => { 
          //console.error(error);
        });
    },

    async addFriend() {
      const requestOption = {
        method: 'POST',
        headers: {
          'Authorization': `Bearer ${authToken.value}`,
          'accept': 'application/json',
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          username: this.userName
        })
      };
      const status = await fetch(`${hostname.value}/user/addFriend`, requestOption)
        .then(response => response.status)
        .catch(error => { 
          //console.error(error);
        });
      this.loadIsfriend();
    },

    async removeFriend() {
      const requestOption = {
        method: 'DELETE',
        headers: {
          'Authorization': `Bearer ${authToken.value}`,
          'accept': 'application/json',
        }
      }
      const status = await fetch(`${hostname.value}/user/delete-friend/${this.userName}`, requestOption)
        .then(response => response.status)
        .catch(error => { 
          //console.error(error); 
        });
      this.loadIsfriend();
    }
  }

})
</script>

<style scoped>
.loading {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100px;
  font-size: 18px;
}

.state-stats {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  background: pink;
}

.profile-header {
  display: flex;
  flex-direction: row;
  justify-content: space-around;
  margin-bottom: 20px;
}

.pic-name {
  display: flex;
  align-items: center;
}

.pic-name h2 {
  margin-left: 10px;
}

.profile-menu {
  display: flex;
}

.profile-menu button {
  padding: 5px 10px;
  margin-right: 10px;
}

.user-stats {
  margin-bottom: 20px;
}

.no-stats {
  font-style: italic;
}

.stats {
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
}

.stats div {
  padding: 5px;
  text-align: center;
}

.stat-winrate {
  font-weight: bold;
}

.stat-minmax {
  margin-top: 10px;
}

.rank {
  margin-top: 10px;
}

.histo {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}

.match {
  padding: 5px;
  margin: 5px;
  border-radius: 5px;
}

.won {
  border: solid 2px green;
}

.lost {
  border: solid 2px red;
}

.no-user-stats {
  font-style: italic;
}
</style>
