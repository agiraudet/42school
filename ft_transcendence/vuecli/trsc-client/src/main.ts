import'./assets/main.css'
import'./assets/fonts.css'

import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import { authToken } from './globalProperties'

const app = createApp(App);

app.use(router);
app.provide('authToken', authToken);
app.mount('#app');
