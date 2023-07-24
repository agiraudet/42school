<template>
  <div class="unnamed-menu">
    <div class="unnamed-panel">
      <p>Choose a unique username.</p>
      <input type=text v-model="name" placeholder="username" @keydown.enter="sendName()" />
      <button @click="sendName()">Confirm</button>
      <p v-if="used"> Username [{{ oldname }}] already taken. Please choose another.</p>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue';
import { hostname, authToken } from '@/globalProperties';

export default defineComponent({
  name: 'Unnamed',
  data() {
    return {
      name: '',
      used: false,
      oldname: '',
    }
  },

  methods: {
    async sendName() {
      const requestOption = {
        method: 'POST',
        headers: {
          'Authorization': `Bearer ${authToken.value}`,
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          username: this.name
        })
      }
      return fetch(`${hostname.value}/auth/update/username`, requestOption)
        .then(response => {
          if (response.status === 409) {
            this.used = true;
            this.oldname = this.name;
            return ({ accessToken: 'used' });
          }
          else {
            return response.json();
          }
        })
        .then(data => {
          if (data.accessToken !== 'used') {
            authToken.value = data.accessToken;
            sessionStorage.setItem('authToken', authToken.value)
            this.$router.push({ name: 'home' });
          }
        })
    },
  }
})
</script>

<style scoped>
.unnamed-menu {
  min-height: 96vh;
  display: flex;
  justify-content: center;
  align-items: center;
}

.unnamed-panel {
  display: flex;
  flex-direction: column;
  width: 400px;
  padding: 30px;
  justify-content: center;
  align-items: center;
  gap: 20px;
  border-radius: 20px;
  background: rgba(18, 18, 18, 0.704);
  box-shadow: 0px 0px 10px 0px #00B8F8;
}
</style>
