<template>
	<div class="play-menu">
		<div class="menu-mode" v-if="mode === 'menu'">
			<button class="play-menu-btn" @click="changeMode('normal')">Normal Game</button>
			<button class="play-menu-btn" @click="changeMode('custom')">Custom Game</button>
		</div>
		<div class="normal-mode" v-else-if="mode === 'normal'">
			<button class="play-menu-btn" @click="goToPong()">Find a game</button>
		</div>
		<div class="custom-mode" v-else-if="mode === 'custom'">
			<h3>Custom Game</h3>
			<div class="custom-settings">
				<div class="custom-label">
					<label for="plrSizeX">Player Width</label>
					<label for="plrSizeY">Player Height</label>
					<label for="plrSpeed">Player Speed</label>
					<label for="maxScore">Max Score</label>
					<label for="ballSize">Ball Size</label>
					<label for="ballSpeed">Ball Speed</label>
				</div>
				<div class="custom-input">
					<input @change="checkRules()" v-model="rules.plrSizeX" type="number" id="plrSizeX" min="10" max="50">
					<input @change="checkRules()" v-model="rules.plrSizeY" type="number" id="plrSizeY" min="10" max="200">
					<input @change="checkRules()" v-model="rules.plrSpeed" type="number" id="plrSpeed" min="1" max="100">
					<input @change="checkRules()" v-model="rules.maxScore" type="number" id="maxScore" min="1" max="999">
					<input @change="checkRules()" v-model="rules.ballSize" type="number" id="ballSize" min="1" max="100">
					<input @change="checkRules()" v-model="rules.ballSpeed" type="number" id="ballSpeed" min="1" max="100">
				</div>
			</div>
			<div class="custom-invite"> 
				<label for="opponent">Opponent</label>
				<input v-model="opponent" type="text" id="opponent" placeholder="Enter opponent's name">
				<button class="play-menu-btn" @click="createCustom()">Invite</button>
				<i v-if="!opponentFound">{{ opponentName }} is not a connected user</i>
			</div>
		</div>
		<div class="all-mode" v-if="mode !== 'menu'">
			<button class="play-menu-btn" @click="changeMode('menu')">Back</button>
		</div>
	</div>
</template>

<script lang='ts'>
import { defineComponent } from 'vue';
import type { IRules } from '@/components/Pong/rules.interface';
import { authToken, coList, hostname } from '@/globalProperties';
import useEventsBus from '@/eventBus';

export default defineComponent({
	name: 'PlayMenu',
	data() {
		return {
			mode: 'menu',
			opponent: '',
			opponentName: '',
			opponentFound: true,
			rules: {
        		allowXMvt: false,
        		plrSizeX: 10,
        		plrSizeY: 70,
        		plrSpeed: 4,
        		maxScore: 11,
        		ballSize: 15,
        		ballSpeed: 4,
        		canvSizeX: 640,
        		canvSizeY: 480,
			} as IRules,
		}
	},

	methods: {
		changeMode(newMode: string) {
			this.mode = newMode;
		},

		goToPong() {
            this.$router.push({ name: 'pong', query:{reload:0} });
		},

		setRule(rule: number, min: number, max: number): number {
			if (rule < min) {
				return min;
			}
			else if (rule > max) {
				return max;
			}
			else {
				return rule;
			}
		},

		checkRules() {
			this.rules.plrSizeX = this.setRule(this.rules.plrSizeX, 10, 50);
			this.rules.plrSizeY = this.setRule(this.rules.plrSizeY, 10, 200);
			this.rules.plrSpeed = this.setRule(this.rules.plrSpeed, 1, 100);
			this.rules.maxScore = this.setRule(this.rules.maxScore, 1, 999);
			this.rules.ballSize = this.setRule(this.rules.ballSize, 1, 100);
			this.rules.ballSpeed = this.setRule(this.rules.ballSpeed, 1, 100);
		},

		async createCustom() {
			this.opponentName = this.opponent;
			this.opponentFound = coList.value.some((user) => user.name === this.opponentName);
			if (!(this.opponentFound)) {
				return;
			}
			const requestOption = {
				method: 'POST',
				headers: {
					'Authorization': `Bearer ${authToken.value}`,
					'accept': 'application/json',
					'Content-Type': 'application/json'
				},
				body: JSON.stringify(this.rules)
			}
			try {
				const response = await fetch(`${hostname.value}/pong/custom/${this.opponentName}`, requestOption);
				if (response.status === 201) {
					const {emit} = useEventsBus();
					emit('customInv', this.opponentName);
					this.$router.push({ name: 'pong'});
				}
				else if (response.status === 404) {
					this.opponentFound = false;
				}
			} catch (error) {
				//console.error(error);
			}
		},
	}
})
</script>

<style scoped>
.menu-mode {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.normal-mode {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.custom-mode {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.custom-settings {
	display: flex;
	flex-direction: row;
}

.custom-label {
	display: flex;
	flex-direction: column;
	align-items: end;
}

.custom-label label {
	display: flex;
	align-items: center;
	height: 40px;
	margin-right: 20px;
	margin-bottom: 12px;
	font-size: 16px;
	font-weight: 500;
}

.custom-input {
	display: flex;
	flex-direction: column;
}

.custom-input input {
	margin-bottom: 10px;
	width: 75px;
}

.custom-invite {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.custom-invite * {
	margin: 5px;
}

.all-mode {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.play-menu {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	min-width: 440px;
	min-height: 240px;
	background: #121212;
    border: 1px solid #00B8F8;
	box-shadow: 0px 0px 15px 0px #00B8F8;
	border-radius: 20px;
	padding: 24px 0px;
}

.play-menu-btn:hover {
    background-color: #888888;
}

.play-menu-btn {
    background-color: #262626;
    border: 0px;
    color: #FFFFFF;
    border-radius: 10px;
    padding-top: 10px;
    padding-bottom: 10px;
	width: 250px;
    margin: 10px;
    font-size: large;
    font-weight: bold;
    cursor: pointer;

}

</style>