<script lang="ts">
import ChatPanel from './components/Chat/ChatPanel.vue';
import Background from './components/Background/Background.vue';
import { authToken } from './globalProperties';
import { defineComponent } from 'vue';

export default defineComponent({
  name: 'App',
  components: {
    ChatPanel,
	Background,
  },
  data() {
    return {
      authToken,
    }
  },

  created() {
    let storedToken = sessionStorage.getItem('authToken');
    authToken.value = storedToken ? storedToken : '';
  },

  methods: {
    disconnect() {
      sessionStorage.removeItem('authToken');
      authToken.value = '';
    }
  }

})
</script>

<template>
  <div class="app">
    <header>
      <div class="router-panel" v-if="authToken !== '' && $route.name !== 'unnamed' && $route.name !== 'oauth'">
		<RouterLink to="/" :class="{ active: $route.name === 'home' }">
  		<img class="header-logo" src="./assets/images/logo.svg" alt="logo" />
	    </RouterLink>
        <nav class="menu" v-if="authToken != '' && $route.name != 'unnamed'">
          <RouterLink class="menu-btn" to="/" :class="{ active: $route.name === 'home' }">Home</RouterLink>
		  <RouterLink class="menu-btn" to="/ladder" :class="{ active: $route.name === 'ladder' }">Ladder</RouterLink>
          <!-- <RouterLink class="menu-btn" to="/play" :class="{ active: $route.name === 'play' }">Play</RouterLink> -->
          <RouterLink class="menu-btn" to="/friends" :class="{ active: $route.name === 'friends' }">Friends</RouterLink>
		  <RouterLink class="menu-btn" :to="{ name: 'profile', params: { username: '>self<' } }"
            :class="{ active: $route.name === 'profile' }">Profile</RouterLink>
          <!-- <RouterLink class="menu-btn" to="/login" @click="disconnect()">Log out</RouterLink> -->
        </nav>
		<RouterLink class="button-3d" to="/play" :class="{ active: $route.name === 'play' }">Play</RouterLink>
      </div>
    </header>
    <br>
  	<div class="router-view">
		<RouterView :key="$route.fullPath"/>
    </div>
	<br>
    <div class="chat" v-if="authToken !== '' && $route.name !== undefined && $route.name !== 'unnamed' && $route.name !== 'oauth'">
      <ChatPanel />
    </div>
	<Background />
  </div>
</template>

<style scoped>

.app {
	width: 100%;
}

header {
	display: flex;
	justify-content: center;
}
.router-view {
	position: relative;
	z-index: 50;
}

.router-panel {
	position: relative;
	/* background: green; */
	z-index: 50;
	padding-top: 30px;
	width: 1180px;
	display: flex;
	justify-content: space-between;
	align-items: center;
	/* gap: 15vw; */
}

.header-logo {
	width: 70px;
	height: 70px;
}

.menu{
	font-size: 12px;
	text-align: center;
	display: flex;
	gap: 30px;
}

.menu-btn {
	position: relative;
	color: #FFFFFF;
	text-decoration: none;
	font-size: 16px;
	font-weight: 500;
	transition: 150ms;

}

.menu-btn.active {
	color: #00B8F8;
}

.menu-btn:after {
	content: '';
	position: absolute;
	left: 0;
	right: 0;
	margin: auto;
	bottom: -5px; 
	width: 0px;
	height: 6px;
	border-radius: 50%;
	background-color: #00B8F8; 
}

.menu-btn:hover {
	color: #00B8F8;
}


.menu-btn.active:after {
	content: '';
	position: absolute;
	left: 0;
	right: 0;
	margin: auto;
	bottom: -5px; 
	width: 6px;
	height: 6px;
	border-radius: 50%;
	background-color: #00B8F8;
}

</style>
