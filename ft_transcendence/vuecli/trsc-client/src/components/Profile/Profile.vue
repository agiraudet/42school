<script lang="ts">
  	import { defineComponent } from 'vue';
  	import { authToken, hostname, nick } from "@/globalProperties";
	import { MatchStats, type IMatch } from "./MatchStats";
	import { LadderClass } from '@/components/Ladder/LadderClass';
	import Avatar from '@/components/Profile/Avatar.vue';
	import AccountFunc from '../Account/AccountFunct';
	import { ref } from 'vue';
  
  	export default defineComponent({
  	name: 'Profile',
  	components: {
		Avatar,
  	},
  	data() {
  	  	return {
  	    	currentComponent: 'ProfileStats' as string,
			ladder: new LadderClass(),
      		histo: [] as Array<IMatch>,
      		stats: new MatchStats(),
      		loading: true,
      		userExist: true,
      		isFriend: false,
      		self: false,
      		userName: '',
			rank: 0,
			AccountFunc: new AccountFunc,
    		is2FAEnabled: false,
    		qrCodeLink: "",
    		avCount: 0,
    		avatar: null as File | null,
    		authCode: '',
    		selectedFile: null as File | null,
    		avatarUrl: ref(''),
    		isErrorCode: false,
    		isSuccess2FA: false,
    		activating2FA: false,
			fileTooLarge: false,
  		};
  	},

	mounted() {
    	this.userName = this.$route.params.username as string;
    	if (this.userName === '>self<') {
      		this.self = true;
      		this.userName = nick.value;
    	}
    	this.loadStats();
		this.isTrue2FA();
  	},

  	methods: {
		// goToAccount() {
      	// 	this.$router.push({ name: 'account' });
    	// },

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
    	},

		switchComponent() {
  	    	if (this.currentComponent === 'ProfileStats') {
  	      		this.currentComponent = 'ProfileSettings';
  	    	} else {
  	      		this.currentComponent = 'ProfileStats';
  	    	}
  	  	},

		disconnect() {
      		sessionStorage.removeItem('authToken');
      		authToken.value = '';
    	},

		// Account part below
		twofaTurnOff() {
    	  this.activating2FA = false;
    	  this.deactivate2fa();
    	},

    	twofaTurnOn() {
    	  this.activating2FA = true;
    	  this.generateQRCode();
    	},

    	onFileChange(e: Event) {
    	  const target = e.target as HTMLInputElement;
    	  if (target.files) {
    	    this.selectedFile = target.files[0];
    	  }
    	},

    	async isTrue2FA() {
    	  this.is2FAEnabled = await this.AccountFunc.is2faActivated(this.is2FAEnabled);
    	},

    	async submitFile() {
    	  const token = authToken.value;
    	  if (!this.selectedFile) {
    	    // console.error("No file selected");
    	    return;
    	  }

    	  let formData = new FormData();
    	  formData.append('file', this.selectedFile);
    	  try {
    	    const requestOption = {
    	      method: 'POST',
    	      headers: {
    	        'Authorization': `Bearer ${token}`,
    	        'accept': 'application/json',
    	      },
    	      body: formData
    	    }
    	    const response = await fetch(`${hostname.value}/auth/upload`, requestOption);

    	    if (!response.ok) {
				this.fileTooLarge = true;
    	    //   throw new Error(`HTTP error! status: ${response.status}`);
    	    } else {
    	      this.avatar = this.selectedFile;
    	      this.selectedFile = null;
    	      this.avCount++;
			  this.fileTooLarge = false;
    	    }

    	  } catch (error) {
    	    // console.error('There was a problem with the fetch operation: ' + error);
    	  }
    	},

    	async deactivate2fa() {
    	  try {
    	    await this.AccountFunc.deactivate2fa();
    	    this.is2FAEnabled = false;
    	  } catch (error) {
    	    // console.error(error);
    	  }
    	},

    	toggle2FA() {
    	  this.is2FAEnabled = true;
    	},

    	async generateQRCode() {
    	  this.qrCodeLink = await this.AccountFunc.generateQrCode();
    	},

    	copyQRCodeLink() {
    	  navigator.clipboard.writeText(this.qrCodeLink);
    	},

    	async validate2FA() {
    	  try {
    	    const res = await this.AccountFunc.turnOn2fa(this.authCode, this.isErrorCode);
    	    if (res < 0) {
    	      this.isErrorCode = true;
    	      this.isSuccess2FA = false;
    	    }
    	    if (res == 1) {
    	      this.isErrorCode = false;
    	      this.isSuccess2FA = true;
    	      this.activating2FA = false;
    	      this.is2FAEnabled = true;
    	    }
    	  } catch (error) {
    	    // console.error('Failed to validate 2FA code:', error);
    	  }
    	},
  	},
});  
</script>

<template>
	<div class="container">
		<div class="loading" v-if="loading">
    		<i>loading...</i>
  		</div>
		<div class="profile-container" v-else>
			<div class="profile-header-container" v-if="userExist">
				<div class="profile-picture">
					<Avatar class="avatar" :msg="userName" :key="avCount" />
		  		</div>
				<div class="profile-title-buttons">
					<div class="top-section">
					  	{{ userName }}
					</div>
					<div class="bottom-section-self" v-if="self">
					  	<button class="icon-button" @click="switchComponent" v-if="currentComponent === 'ProfileStats'">
							<img class="icon" src="../../assets/images/Setting.svg" />
							Settings
					  	</button>
						<button class="icon-button" @click="switchComponent" v-else>
							<img class="icon" src="../../assets/images/profile.svg" />
							Profile
					  	</button>
						<RouterLink to="/login" @click="disconnect()">
							<button class="icon-button">
								<img class="icon" src="../../assets/images/Logout.svg" />
									Disconnect
					  		</button>
						</RouterLink>
					</div>
					<div class="bottom-section-other" v-else>
						<button class="icon-button" v-if="!isFriend" @click="addFriend()">
							<img class="icon" src="../../assets/images/profile.svg" />
							Add friend
					  	</button>
						<button class="icon-button" v-else @click="removeFriend()">
							<img class="icon" src="../../assets/images/profile.svg" />
							Remove friend
					  	</button>
					</div>
		  		</div>
			</div>
			<div class="stat-history-container" v-if="currentComponent === 'ProfileStats' && userExist">
				<div class="stat-container">
					<img src="../../assets/images/stats-arcade.png">
					<div class="stat">
						<div class="stat-ranking-points">
							<div class="stat-1">
								Rank
								<span>{{ rank }}</span>
							</div>
							<div class="stat-1">
								Points
								<span>{{ stats.xp }}</span>
							</div>
						</div>
						<div class="stat-games-played">
							<div class="games-played">
								<div class="stat-1">
									Total
									<span>{{ stats.nMatch }}</span>
								</div>
								<div class="stat-1 green">
									Victories
									<span>{{ stats.wins }}</span>
								</div>
								<div class="stat-1 red">
									Defeats
									<span>{{ stats.loss }}</span>
								</div>
							</div>
							<div class="stat-1">
								Win rate
								<span>{{ stats.winrate }}%</span>
							</div>
						</div>
						<div class="stat-points">
							Points stats
							<div class="points">
								Max: {{ stats.maxScore }}<br>
          						Min: {{ stats.minScore }} <br>
          						Avg: {{ stats.avgScore }}
							</div>
						</div>
					</div>
				</div>
				<div class="history-container">
					<img src="../../assets/images/history-arcade.png">
					<div v-if="stats.nMatch <= 0">
        				<i>{{ userName }} have not played a single match yet !</i>
     				 </div>
					<div class="history" v-if="stats.nMatch > 0">
						<div v-for="(match, index) in histo" :key="index" :class="{
          				match,
          				won: match.isWinner,
          				lost: !match.isWinner,
        				}">
						<p v-if="match.isWinner">Victory</p>
						<p v-else>Defeat</p>
          				<span>{{ userName }} {{ match.scoreUser }} <i>vs</i> {{ match.scoreOpponent }} {{ match.opponent }}</span>
        				</div>
					</div>
				</div>
			</div>
			<div class="settings-container" v-else-if="currentComponent === 'ProfileSettings' && userExist">
				<img src="../../assets/images/settings-arcade.png">
				<div class="settings">
					<div class="account">
  						<div class="account-settings">
  						  <div class="tfa-settings">
  						    <div class="tfa-set-on" v-if="!is2FAEnabled">
							  <p>2FA authentication</p>
  						      <div class="tfa-btn" v-if="!activating2FA">
  						        <button @click="twofaTurnOn()">Enable 2FA</button>
  						      </div>
  						      <div class="tfa-qr" v-else>
  						        <img class="qrcode" :src="qrCodeLink" />
  						        <button @click="copyQRCodeLink()">Copy link</button>
  						        <input type="text" placeholder="Enter your 6 digits code" v-model="authCode" />
  						        <button @click=validate2FA()>Submit</button>
  						        <p v-if="isErrorCode == true"> Wrong code ! Please try again</p>
  						        <p v-if="isSuccess2FA == true"> 2FA has been activated</p>
  						      </div>
  						    </div>
  						    <div class="tfa-set-off" v-else>
  						      <button @click="twofaTurnOff()">Disable 2FA</button>
  						    </div>
  						  </div>
  						  <div class="avatar-settings">
  						    <div class="avatar-menu">
								<p>Avatar :</p>
								<p>File max : 1Mo</p>
  						      <!-- <input type="file" @change="onFileChange"> -->
  		      				  <input type="file" accept="image/jpg, image/png, image/jpeg" @change="onFileChange">
  						      <button @click="submitFile" v-if="selectedFile != null">Upload</button>
							  <span class="error" v-if="fileTooLarge">Error: Something wrong or your file is too large.</span>
							</div>
							<br>
							Preview:
  						    <Avatar :msg="userName" :key="avCount" />
  						  </div>
  						</div>
					</div>
				</div>
			</div>
			<div class="no-user-stats" v-else>
      			<i>User not found.</i>
    		</div>
		</div>
	</div>
</template>
  
<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>

.profile-container {
	width: 970px;
	display: flex;
	flex-direction: column;
	gap: 50px;
}
.profile-header-container {
	position: relative;
	width: 100%;
	display: flex;
	gap: 26px;

}

.profile-picture {
	display: flex;
}

.profile-picture .avatar {
	border-radius: 20px;
	border: 1px solid #00B8F8;
	box-shadow: 0px 0px 15px 0px #00B8F8;
	width: 119px;
	height: 119px;
}

.profile-title-buttons {
	display: flex;
	justify-content: space-between;
	flex-direction: column;
	width: 100%;
}

.top-section {
	text-align: left;
	font-weight: 600;
	font-size: 20px;
	color: white;
}
.bottom-section-self {
	display: inline-flex;
	justify-content: space-between;
	width: 100%;
} 

.bottom-section-other {
	display: inline-flex;
	justify-content: start;
	gap: 20px;
	width: 100%;
}

.profile-pic {
	border-radius: 10px;
	border: 1px solid #00B8F8;
	box-shadow: 0px 0px 15px 0px #00B8F8;
}

.stat-history-container {
	display: flex;
	justify-content: start;
	gap: 30px;
}

.stat-container {
	display: flex;
	flex-direction: column;
	justify-content: start;
	align-items: center;
	gap: 24px;
	width:270px;
}


.stat {
	width: 100%;
	/* height: 100px; */
	border-radius: 20px;
	border: 1px solid #00B8F8;
	background: rgba(18, 18, 18, 0.60);
	box-shadow: 0px 0px 15px 0px #00B8F8;
	padding: 22px 0px;
	display: flex;
	flex-direction: column;
	align-items: center;
}

.stat-ranking-points {
	width: 230px;
	border-bottom: 1px solid #00B8F8;
	display: flex;
	padding-bottom: 14px;
}

.stat-games-played {
	width: 230px;
	border-bottom: 1px solid #00B8F8;
	padding-bottom: 14px;
	margin-top: 16px;
	display: flex;
	flex-direction: column;
	align-items: center;
	gap: 12px;
}

.stat-points {
	margin-top: 16px;
	font-size: 12px;
	text-transform: uppercase;
	font-weight: 500;
	color: #c5c5c5;
	display: flex;
	flex-direction: column;
	gap: 4px;
	align-items: center;
}

.stat-points .points {
	color: white;
	font-size: 14px;
	font-weight: 700;
}

.games-played {
	width: 100%;
	display: flex;
	justify-content: space-between;
}

/* .average {
	displ
} */
.stat-1 {
	flex: 1;
	display: flex;
	flex-direction: column;
	justify-content: center;
	align-items: center;
	font-size: 12px;
	text-transform: uppercase;
	font-weight: 500;
	color: #c5c5c5;
}

.stat-1 span {
	color: #FFF;
	/* text-shadow: 0px 0px 10px 0px rgba(255, 255, 255, 0.50); */
	font-family: Poppins;
	font-size: 22px;
	font-style: normal;
	font-weight: 700;
	line-height: normal;
}

.green {
	color: green;
}

.red {
	color: rgb(179, 0, 0);
}

.history-container {
	display: flex;
	flex-direction: column;
	justify-content: start;
	align-items: center;
	gap: 24px;
	width: 670px;
}

.history {
	width: 100%;
	display: flex;
	flex-direction: column;
	gap: 16px;
}

.match {
	position: relative;
	border-radius: 20px;
	border: 1px solid #00B8F8;
	background: rgba(18, 18, 18, 0.60);
	box-shadow: 0px 0px 15px 0px #00B8F8;
	display: flex;
	justify-content: center;
	align-items: center;
	gap:32px;
	height: 60px;
	padding-left: 24px;
}

.won {
  border-color: #00B8F8;
}

.won p {
	color: #00B8F8;
	font-weight: 700;
	text-transform: uppercase;
	font-size: 14px;
}

.lost {
  border-color: #C90000;
  box-shadow: 0px 0px 15px 0px #C90000;
}

.lost p {
	color: #C90000;
	font-weight: 700;
	text-transform: uppercase;
	font-size: 14px;
}

.match p {
	position: absolute;
	left: 32px
}

.settings-container {
	display: flex;
	flex-direction: column;
	justify-content: center;
	align-items: center;
	width: 970px;
	gap: 24px;
}

.settings {
	width: 100%;
	border-radius: 20px;
	border: 1px solid #00B8F8;
	background: rgba(18, 18, 18, 0.60);
	box-shadow: 0px 0px 15px 0px #00B8F8;
	height: 500px;
	padding: 60px 0px;
}




.icon-button {
	display: inline-flex;
	padding: 8px 14px;
	justify-content: center;
	height: 38px;
	align-items: center;
	gap: 10px;
	border-radius: 10px;
	border: 1px solid #00B8F8;
	background: #121212;
	box-shadow: 0px 0px 15px 0px #00B8F8;
	font-weight: 500;
	color: white;
	font-size: 14px;
	cursor: pointer;
}
.icon-button:hover {
	background: #262626;
}

/* Account css */
.account {
	display: flex;
	justify-content: center;
	align-items: center;
}

.account-settings {
  display: flex;
  align-items: center;
  gap: 80px;
}


.tfa-settings{
	border-right: 1px solid white;
	padding-right: 40px;
}

.tfa-set-on{
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: start;
	gap: 16px;
}

.tfa-qr{
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 16px;
}

/* .account-settings div {
  margin-bottom: 20px;
} */

.tfa-settings div {
  display: flex;
  flex-direction: column;
  align-items: center;
}


.avatar-settings {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.avatar-menu{
	display: flex;
	flex-direction: column;
	align-items: center;
	gap: 10px;
}
.avatar-menu .error {
	color: red;
}

.no-user-stats {
	align-items: center;
	justify-content: center;
}

</style>