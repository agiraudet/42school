<template>
    <main>
		<Profile />
		<!-- <br> -->
        	<!-- <MatchHisto/> -->
        	<!-- <FriendList v-if="$route.params.username === '>self<'" /> -->
    </main>
</template>

<script setup lang="ts">


import FriendList from '@/components/Profile/FriendList.vue';
import MatchHisto from '@/components/Profile/MatchHisto.vue';
import Profile from '@/components/Profile/Profile.vue';

</script>

<style scoped>

main {
	display: flex;
	flex-direction: column;
	justify-content: center;
	align-items: center;
}



.profile-picture {
	display: flex;
}

.profile-title-buttons {
	display: flex;
	justify-content: space-between;
	flex-direction: column;
	background-color: green;
	width: 100%;
}
.top-section {
	text-align: left;
	font-weight: 600;
	color: white;
}
.bottom-section {
	display: inline-flex;
	justify-content: space-between;
	background-color: blue;
	width: 100%;
}

.profile-pic {
	border-radius: 10px;
	border: 1px solid #00B8F8;
	box-shadow: 0px 0px 15px 0px #00B8F8;
}

.icon-button {
	display: inline-flex;
	padding: 8px 14px;
	justify-content: center;
	align-items: center;
	gap: 10px;
	border-radius: 10px;
	border: 1px solid #00B8F8;
	background: #121212;
	box-shadow: 0px 0px 15px 0px #00B8F8;
	font-weight: 600;
	color: white;
	font-size: 14px;
	cursor: pointer;
  }

</style>
