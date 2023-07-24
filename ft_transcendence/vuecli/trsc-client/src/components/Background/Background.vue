<template>
	<div class="ellipses">
    	<div class="ellipse-1"></div>
    	<div class="ellipse-2"></div>
    	<div class="ellipse-3"></div>
    	<div class="ellipse-4"></div>
    	<div class="ellipse-5"></div>
    	<div class="ellipse-6"></div>
    	<div class="ellipse-7"></div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue';

export default defineComponent({
  name: 'Background',
  })
</script>

<style scoped>
.ellipses {
	display: flex;
	justify-content: center;
}

.ellipse-1 {
	position: absolute;
	width: 500px;
	height: 500px;
	z-index: 0;
	top: 431px;
	margin-left: -1100px;
	border-radius: 50%;
	background: #F800F8;
	filter: blur(500px);
	opacity: 0.9;
}

.ellipse-2 {
	position: absolute;
	width: 196px;
	height: 196px;
	z-index: 0;
	top: 80px;
	margin-left: -200px;
	border-radius: 50%;
	background: #9747FF;
	filter: blur(130px);
}

.ellipse-3 {
	position: absolute;
	width: 280px;
	height: 280px;
	z-index: 0;
	top: -59px;
	margin-left: 900px;
	border-radius: 50%;
	background: #00B8F8;
	filter: blur(220px);
}

.ellipse-4 {
	position: absolute;
	width: 250px;
	height: 250px;
	z-index: 0;
	top: 560px;
	margin-left: 500px;
	border-radius: 50%;
	background: #00F8F8;
	filter: blur(200px);
}

.ellipse-5 {
	position: absolute;
	width: 196px;
	height: 196px;
	z-index: 0;
	top: 960px;
	margin-left: 1000px;
	border-radius: 50%;
	background: #9747FF;
	filter: blur(130px);
}

.ellipse-6 {
	position: absolute;
	width: 280px;
	height: 280px;
	z-index: 0;
	top: 1619px;
	margin-left: -1000px;
	border-radius: 50%;
	background: #00B8F8;
	filter: blur(220px);
}

.ellipse-7 {
	position: absolute;
	width: 500px;
	height: 500px;
	z-index: 0;
	top: 1800px;
	margin-left: 1000px;
	border-radius: 50%;
	background: #F800F8;
	filter: blur(500px);
	opacity: 0.9;
}
</style>