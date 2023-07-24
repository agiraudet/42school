<template>
    <div class="ladder">
		<div class="ladder-titles">
			<div class="rank-title">Rank</div>
			<div class="user-title">User</div>
			<div class="points-title">Points</div>
		</div>
		<div class="ladder-users">
        	<div v-for="(user, index) in ladder.ladder"
        	@click="gotoProfile(user.name)"
        	class="user"
        	:key="index">
        		<div class="user-rank"><p>{{ index + 1 }}</p></div>
				<div class="user-infos">
					<Avatar class="avatar" :msg="user.name" />
					<p>{{ user.name }}</p>
				</div>
        		<div class="user-points"><p>{{ user.points }}</p></div>
			</div>
        </div>
    </div>

</template>

<script lang="ts">
import { defineComponent } from 'vue';
import { LadderClass} from './LadderClass';
import { nick } from '@/globalProperties';
import Avatar from '../Profile/Avatar.vue';

export default defineComponent({
    name: 'Ladder',
    components: {
        Avatar,
    },

    data() {
        return {
            ladder: new LadderClass(),
        }
    },

    mounted() {
        this.update();
    },

    methods: {
        async update() {
            await this.ladder.getLadder();
        },

        gotoProfile(name: string) {
            if (name === nick.value) {
                name = '>self<'
            }
            this.$router.push({
                name: 'profile',
                params: {username: name}
            })
        },
    }
})
</script>

  

<style scoped>

.ladder {
	position: relative;
	width: 800px;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
	gap: 16px;
}

.ladder-titles {
	display: inline-flex;
	width: 740px;
}

.rank-title {
	width: 10%;
}

.user-title {
	width: 60%;
}

.points-title {
	width: 30%;
	display: flex;
	justify-content: end;
}

.ladder-users {
	display: flex;
	flex-direction: column;
	width: 100%;
	gap: 10px;
}

.user {
    cursor: pointer;
    display: flex;
    flex-direction: row;
    align-items: center;
    /* border: 1px solid #434343; */
    width: 100%;
	height: 60px;
    border-radius: 20px;
	background: rgba(18, 18, 18, 0.704);
	box-shadow: 0px 0px 10px 0px #00B8F8;
}


.user-rank {
	width: 10%;
	margin-left: 30px;
}

.user-rank p {
	padding-left: 2px;
}
.user-infos {
	width: 60%;
	display: flex;
	align-items: center;
	gap: 14px;
}

.avatar {
    border-radius: 50%;
    border: 1px solid #00B8F8;
    width: 40px;
    height: 40px;
}

.user-points {
	width: 30%;
	display: flex;
	justify-content: end;
	margin-right: 30px;
	
}

p {
	font-size: 16px;
	font-weight: 500;
}

</style>