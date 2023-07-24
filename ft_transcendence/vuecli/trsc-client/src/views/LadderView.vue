<template>
	<div class ="ladder">
		<div class="ladder-header">
			<img src="../assets/images/LeaderBoard.png">
		</div>
		<Ladder/>
	</div>

</template>

<script setup lang="ts">
import Ladder from '@/components/Ladder/Ladder.vue';
</script>

<style scoped>

.ladder {
	display: flex;
	flex-direction: column;
	align-items: center; /* Centre verticalement */
	justify-content: center; /* Centre horizontalement */
	padding-bottom: 80px;
}

.ladder-header {
	margin-top: 30px;
	margin-bottom: 50px;

}

</style>