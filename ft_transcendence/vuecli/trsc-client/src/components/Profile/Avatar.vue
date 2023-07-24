<template>
  <img :src="avatarUrl" class="avatar-pic" alt="User Avatar">
</template>

<script lang="ts">
import { authToken, hostname, nick } from '@/globalProperties';
import { defineComponent, ref } from 'vue';

export default defineComponent({
  data() {
    return {
      avatarUrl: ref(''),
      username: '',
    }
  },

  props: {
    msg: {
      type: String,
      required: true
    }
  },

  mounted() {
    this.username = (this.msg === '>self<') ? nick.value : this.msg;
    this.fetchAvatar();
  },

  methods: {
    async fetchAvatar() {
      const token = authToken.value;
      const requestOption = {
        method: 'GET',
        headers: {
          'Authorization': `Bearer ${token}`,
          'Content-Type': 'application/json',
        },
      };
      const response = await fetch(`${hostname.value}/auth/avatar/${this.username}`, requestOption);
      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }
      else {
        const base64Image = await response.text();
        this.avatarUrl = 'data:image/jpeg;base64,' + base64Image;
      }
    },
  }
})
</script>

<style>
.avatar-pic {
  width: 150px;
  height: 150px;
  /* border-radius: 50%; */
  /* border: solid 2px white; */
}
</style>
