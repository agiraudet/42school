<template>
    <main>
        <FriendList />
    </main>
</template>

<script setup lang="ts">


import FriendList from '@/components/Profile/FriendList.vue';
import Profile from '@/components/Profile/Profile.vue';

</script>

<style scoped>

main {
	display: flex;
	flex-direction: column;
	justify-content: center;
	align-items: center;
}



</style>