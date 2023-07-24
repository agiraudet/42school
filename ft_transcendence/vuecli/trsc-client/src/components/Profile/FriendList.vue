<template>
    <div class="friend-panel">
        <h2>FRIENDS</h2>
        <div class="no-friend" v-if="friendList.length <= 0">
            <i>You have no friends yet</i>
        </div>
        <div class="friend-list" v-else>
            <div v-for="(friend, index) in friendList"
            @click="gotoProfile(friend.name)"
            :key="index"
            :class="friend.status">
                {{ friend.name }}
            </div>
        </div>
    </div>
</template>

<script lang="ts">
import { defineComponent, watch } from 'vue';
import { authToken, hostname } from "@/globalProperties";
import useEventsBus from '@/eventBus';

interface IFriend {name: string, status: string};

export default defineComponent({
    name: 'FriendList',
    data() {
        return {
            friendList: [] as Array<IFriend>,
        }
    },

    created() {
        const {bus} = useEventsBus();
        watch(()=>bus.value.get('updateFriendList'), (val) => {
        const [customInvBus] = val ?? [];
        this.updateFriendList();
        });
    },

    mounted() {
        this.updateFriendList();
    },

    methods: {

        gotoProfile(name: string) {
            this.$router.push({
                name: 'profile',
                params: {username: name}
            })
        },

        async requestFriendList() {
            const requestOption = {
                method: 'GET',
                headers: {
                    'Authorization': `Bearer ${authToken.value}`,
                    'accept': 'application/json',
                }
            }
            return fetch(`${hostname.value}/user/friendsstatus`, requestOption)
                .then(response => response.json())
                .then(data => {
                    return data;
                })
                .catch(error => { 
                    //console.error(error);
                });
        },

        async updateFriendList() {
            const response = await this.requestFriendList();
            this.friendList = response; 
        },
    }
})
</script>

<style>
.friend-panel {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

.friend-list {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

.friend-list div {
    cursor: pointer;
    padding: 5px;
    margin: 3px;
    border-radius: 5px;
}

.friend-list .online {
    border: 1px solid green;
}

.friend-list .ingame {
    border: 1px solid orange;
}

.friend-list .offline {
    border: 1px solid red;
}
</style>