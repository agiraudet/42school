import { reactive, toRefs } from 'vue';

export interface IUserStatus {name: string, status: string}

export const globalProperties = reactive({
  authToken: '',
  nick: '',
  hostname: 'http://localhost:3000',
  coList: [] as Array<IUserStatus>,
});

export const { authToken, nick, hostname, coList } = toRefs(globalProperties);
