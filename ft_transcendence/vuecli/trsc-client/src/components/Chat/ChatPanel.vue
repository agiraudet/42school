<template>
  <div>
    <div class="chat-popup-background" v-if="chatVisible" @click="toggleChat()">
      <div class="chat-panel" @click.stop>
        <div class="panel" id="mode">
          <div class="chat-logo">
            <img src="../../assets/images/msg-icon.svg">
            ChatBox
          </div>
          <div class="modes-div">
            <button @click="changeMode('pvMode')" :class="{ 'mode-btn': true, selected: modeAct === 'pvMode' }">
              <img src="../../assets/images/dm-icon.svg">
              Direct messages<br><i v-if="modeOpt['pvMode'].globalNotif">- ! -</i>
            </button>
            <button @click="changeMode('chanMode')" :class="{ 'mode-btn': true, selected: modeAct === 'chanMode' }">
              <img src="../../assets/images/channels-icon.svg">
              Channels<br><i v-if="modeOpt['chanMode'].globalNotif">- ! -</i>
            </button>
          </div>
        </div>
        <div class="panel" id="conversations">
          <div class="chan-panel" id="listing">
            <div class="chan-list">
              <div v-for="(tab, index) in modeOpt[modeAct].tabs" :key="index" :class="{
                active: index === modeOpt[modeAct].tabCur,
                in: chanIn.includes(tab) || modeAct === 'pvMode'
              }" @click="changeTab(index)">
                {{ tab }} <i v-if="modeOpt[modeAct].notif.includes(tab)">- ! -</i>
              </div>
            </div>
          </div>
          <button v-if="modeAct === 'chanMode'" class="chan-new-btn" @click="createConv()">New</button>
        </div>
        <div class="panel" id="messages">
          <div class="chan-creation" id="creation" v-if="chanForm.creating">
            <div class="creation-menu">
              <h3>New Channel</h3>
              <label for="name">Name</label><br>
              <input v-model="chanForm.name" @keypress.enter="createChan()" type="text" autocomplete="off"
                placeholder="#name" id="name" />
              <br>
              <br>
              <label for="status">Mode</label>
              <br>
              <select v-model="chanForm.status" name="chan-mode" id="status">
                <option value="public">Public</option>
                <option value="private">Private</option>
                <option value="locked">Locked</option>
              </select>
              <br>
              <br>
              <label v-if="chanForm.status === 'locked'" for="pass">Password</label>
              <br>
              <input v-model="chanForm.password" v-if="chanForm.status === 'locked'" @keypress.enter="createChan()"
                type="text" autocomplete="off" placeholder="pass" id="pass" />
              <br>
              <br>
              <button class="create-chan-btn" @click="createChan()">Create</button>
            </div>
          </div>
          <div class="chan-selection" id="selection" v-else-if="chanForm.selecting">
            <div class="message-title">
              <p>{{ modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur] }} <i> {{
                chanForm.chanList[modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur]] }}</i> </p>
              <button v-if="chanForm.selecting" class="option-btn" @click="chanForm.selecting = false">
                <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                  viewBox="0 0 384 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                  <path
                    d="M342.6 150.6c12.5-12.5 12.5-32.8 0-45.3s-32.8-12.5-45.3 0L192 210.7 86.6 105.4c-12.5-12.5-32.8-12.5-45.3 0s-12.5 32.8 0 45.3L146.7 256 41.4 361.4c-12.5 12.5-12.5 32.8 0 45.3s32.8 12.5 45.3 0L192 301.3 297.4 406.6c12.5 12.5 32.8 12.5 45.3 0s12.5-32.8 0-45.3L237.3 256 342.6 150.6z" />
                </svg>
              </button>
            </div>
            <div class="owner-opt" v-if="chanUsrList.owner">
              mode:
              <select v-model="chanForm.status" name="chan-mode" id="status">
                <option value="public">Public</option>
                <option value="private">Private</option>
                <option value="locked">Locked</option>
              </select>
              <input v-model="chanForm.password" v-if="chanForm.status === 'locked'" @keypress.enter="chanForm.chgtStatus()"
                type="text" autocomplete="off" placeholder="password" id="pass" />
              <button @click="chanForm.chgtStatus()">OK</button>
            </div>
            <div class="admin-opt"
              v-if="chanUsrList.admin && chanForm.chanList[modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur]] === 'private'">
              invite:
              <input v-model="chanUsrList.invite" @keypress.enter="sendCmd('inv', chanUsrList.invite)" type="text"
                autocomplete="off" placeholder="username" id="invite-field" />
              <button @click="sendCmd('inv', chanUsrList.invite)">OK</button>
            </div>
            <div class="chan-user-list">
              <ul class="usr-lst">
                <li v-for="usr in chanUsrList.usrList" :key="usr.id" class="usr-name">
                  <div class="usr-status">
                    {{ usr.name }} <i v-if="chanUsrList.isOp(usr.name)">{{ usr.status }}</i>
                  </div>
                  <div class="option-btn-op" v-if="usr.name !== nick">
                    <button class="usr-btn" v-if="chanUsrList.admin && !chanUsrList.isOw(usr.name)"
                      @click="sendCmd('mute', usr.name)">
                      <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 640 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M38.8 5.1C28.4-3.1 13.3-1.2 5.1 9.2S-1.2 34.7 9.2 42.9l592 464c10.4 8.2 25.5 6.3 33.7-4.1s6.3-25.5-4.1-33.7L512.9 376.7C552.2 340.2 576 292.3 576 240C576 125.1 461.4 32 320 32c-67.7 0-129.3 21.4-175.1 56.3L38.8 5.1zM64 240c0 45.1 17.7 86.8 47.7 120.9c-1.9 24.5-11.4 46.3-21.4 62.9c-5.5 9.2-11.1 16.6-15.2 21.6c-2.1 2.5-3.7 4.4-4.9 5.7c-.6 .6-1 1.1-1.3 1.4l-.3 .3 0 0 0 0 0 0 0 0c-4.6 4.6-5.9 11.4-3.4 17.4c2.5 6 8.3 9.9 14.8 9.9c28.7 0 57.6-8.9 81.6-19.3c22.9-10 42.4-21.9 54.3-30.6c31.8 11.5 67 17.9 104.1 17.9c37 0 72.3-6.4 104-17.9L82.9 161.3C70.7 185.6 64 212.2 64 240z" />
                      </svg>
                    </button>
                    <button class="usr-btn" v-if="chanUsrList.admin && !chanUsrList.isOw(usr.name)"
                      @click="sendCmd('ban', usr.name)">
                      <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 512 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M367.2 412.5L99.5 144.8C77.1 176.1 64 214.5 64 256c0 106 86 192 192 192c41.5 0 79.9-13.1 111.2-35.5zm45.3-45.3C434.9 335.9 448 297.5 448 256c0-106-86-192-192-192c-41.5 0-79.9 13.1-111.2 35.5L412.5 367.2zM0 256a256 256 0 1 1 512 0A256 256 0 1 1 0 256z" />
                      </svg>
                    </button>
                    <button class="usr-btn" v-if="chanUsrList.admin && !chanUsrList.isOw(usr.name)"
                      @click="sendCmd('kick', usr.name)">
                      <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 384 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M342.6 150.6c12.5-12.5 12.5-32.8 0-45.3s-32.8-12.5-45.3 0L192 210.7 86.6 105.4c-12.5-12.5-32.8-12.5-45.3 0s-12.5 32.8 0 45.3L146.7 256 41.4 361.4c-12.5 12.5-12.5 32.8 0 45.3s32.8 12.5 45.3 0L192 301.3 297.4 406.6c12.5 12.5 32.8 12.5 45.3 0s12.5-32.8 0-45.3L237.3 256 342.6 150.6z" />
                      </svg>
                    </button>
                    <button class="usr-btn" v-if="chanUsrList.owner && !chanUsrList.isOw(usr.name)"
                      @click="sendCmd('op', usr.name)">
                      <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 384 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M256 48V64c0 17.7-14.3 32-32 32H160c-17.7 0-32-14.3-32-32V48H64c-8.8 0-16 7.2-16 16V448c0 8.8 7.2 16 16 16H320c8.8 0 16-7.2 16-16V64c0-8.8-7.2-16-16-16H256zM0 64C0 28.7 28.7 0 64 0H320c35.3 0 64 28.7 64 64V448c0 35.3-28.7 64-64 64H64c-35.3 0-64-28.7-64-64V64zM160 320h64c44.2 0 80 35.8 80 80c0 8.8-7.2 16-16 16H96c-8.8 0-16-7.2-16-16c0-44.2 35.8-80 80-80zm-32-96a64 64 0 1 1 128 0 64 64 0 1 1 -128 0z" />
                      </svg>
                    </button>
                    <button class="usr-btn" @click="toggleBlockUser(usr.name)">
                      <svg v-if="!(blockedUser.includes(usr.name))" xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 512 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M256 0c4.6 0 9.2 1 13.4 2.9L457.7 82.8c22 9.3 38.4 31 38.3 57.2c-.5 99.2-41.3 280.7-213.6 363.2c-16.7 8-36.1 8-52.8 0C57.3 420.7 16.5 239.2 16 140c-.1-26.2 16.3-47.9 38.3-57.2L242.7 2.9C246.8 1 251.4 0 256 0z" />
                      </svg>
                      <svg v-else xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 512 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M256 0c4.6 0 9.2 1 13.4 2.9L457.7 82.8c22 9.3 38.4 31 38.3 57.2c-.5 99.2-41.3 280.7-213.6 363.2c-16.7 8-36.1 8-52.8 0C57.3 420.7 16.5 239.2 16 140c-.1-26.2 16.3-47.9 38.3-57.2L242.7 2.9C246.8 1 251.4 0 256 0zm0 66.8V444.8C394 378 431.1 230.1 432 141.4L256 66.8l0 0z" />
                      </svg>
                    </button>
                    <button class="usr-btn" @click="inviteToPlay(usr.name); toggleChat()">
                      <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 384 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M73 39c-14.8-9.1-33.4-9.4-48.5-.9S0 62.6 0 80V432c0 17.4 9.4 33.4 24.5 41.9s33.7 8.1 48.5-.9L361 297c14.3-8.7 23-24.2 23-41s-8.7-32.2-23-41L73 39z" />
                      </svg>
                    </button>
                    <!-- @Dkoriaki: test pour acceder au profil a partir du chan -->
                    <button class="usr-btn" @click="goToProfile(usr.name); toggleChat()">
                      <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                        viewBox="0 0 448 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                        <path
                          d="M224 256A128 128 0 1 0 224 0a128 128 0 1 0 0 256zm-45.7 48C79.8 304 0 383.8 0 482.3C0 498.7 13.3 512 29.7 512H418.3c16.4 0 29.7-13.3 29.7-29.7C448 383.8 368.2 304 269.7 304H178.3z" />
                      </svg>
                    </button>
                  </div>
                </li>
              </ul>
            </div>
          </div>
          <div class="ask-pass" id="login" v-else-if="chanForm.askPass">
            <div class="message-title">
              <p>{{ chanForm.name }}</p>
            </div>
            <label for="pass">Password</label><br>
            <input v-model="chanForm.password" @keypress.enter="tryTojoinChan()" type="text" autocomplete="off"
              placeholder="pass" id="pass" />
          </div>
          <div class="message-panel" id="messages" v-else-if="modeOpt[modeAct].tabCur != -1">
            <div class="message-title">
              <p>{{ modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur] }}</p>
              <div class='pv-btn' v-if="modeAct === 'pvMode'">
                <button class="option-btn" @click="toggleBlockUser(modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur])">
                  <svg v-if="!(blockedUser.includes(modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur]))"
                    xmlns="http://www.w3.org/2000/svg" height="1em"
                    viewBox="0 0 512 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                    <path
                      d="M256 0c4.6 0 9.2 1 13.4 2.9L457.7 82.8c22 9.3 38.4 31 38.3 57.2c-.5 99.2-41.3 280.7-213.6 363.2c-16.7 8-36.1 8-52.8 0C57.3 420.7 16.5 239.2 16 140c-.1-26.2 16.3-47.9 38.3-57.2L242.7 2.9C246.8 1 251.4 0 256 0z" />
                  </svg>
                  <svg v-else xmlns="http://www.w3.org/2000/svg" height="1em"
                    viewBox="0 0 512 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                    <path
                      d="M256 0c4.6 0 9.2 1 13.4 2.9L457.7 82.8c22 9.3 38.4 31 38.3 57.2c-.5 99.2-41.3 280.7-213.6 363.2c-16.7 8-36.1 8-52.8 0C57.3 420.7 16.5 239.2 16 140c-.1-26.2 16.3-47.9 38.3-57.2L242.7 2.9C246.8 1 251.4 0 256 0zm0 66.8V444.8C394 378 431.1 230.1 432 141.4L256 66.8l0 0z" />
                  </svg>
                </button>
                <button class="option-btn"
                  @click="inviteToPlay(modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur]); toggleChat()">
                  <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                    viewBox="0 0 384 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                    <path
                      d="M73 39c-14.8-9.1-33.4-9.4-48.5-.9S0 62.6 0 80V432c0 17.4 9.4 33.4 24.5 41.9s33.7 8.1 48.5-.9L361 297c14.3-8.7 23-24.2 23-41s-8.7-32.2-23-41L73 39z" />
                  </svg>
                </button>
                <button class="option-btn"
                  @click="goToProfile(modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur]); toggleChat()">
                  <svg xmlns="http://www.w3.org/2000/svg" height="1em"
                    viewBox="0 0 448 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                    <path
                      d="M224 256A128 128 0 1 0 224 0a128 128 0 1 0 0 256zm-45.7 48C79.8 304 0 383.8 0 482.3C0 498.7 13.3 512 29.7 512H418.3c16.4 0 29.7-13.3 29.7-29.7C448 383.8 368.2 304 269.7 304H178.3z" />
                  </svg>
                </button>
              </div>
              <button v-if="modeAct === 'chanMode'" class="option-btn" @click="gotoChanOpt()"><svg
                  xmlns="http://www.w3.org/2000/svg" height="1em"
                  viewBox="0 0 512 512"><!--! Font Awesome Free 6.4.0 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2023 Fonticons, Inc. -->
                  <path
                    d="M495.9 166.6c3.2 8.7 .5 18.4-6.4 24.6l-43.3 39.4c1.1 8.3 1.7 16.8 1.7 25.4s-.6 17.1-1.7 25.4l43.3 39.4c6.9 6.2 9.6 15.9 6.4 24.6c-4.4 11.9-9.7 23.3-15.8 34.3l-4.7 8.1c-6.6 11-14 21.4-22.1 31.2c-5.9 7.2-15.7 9.6-24.5 6.8l-55.7-17.7c-13.4 10.3-28.2 18.9-44 25.4l-12.5 57.1c-2 9.1-9 16.3-18.2 17.8c-13.8 2.3-28 3.5-42.5 3.5s-28.7-1.2-42.5-3.5c-9.2-1.5-16.2-8.7-18.2-17.8l-12.5-57.1c-15.8-6.5-30.6-15.1-44-25.4L83.1 425.9c-8.8 2.8-18.6 .3-24.5-6.8c-8.1-9.8-15.5-20.2-22.1-31.2l-4.7-8.1c-6.1-11-11.4-22.4-15.8-34.3c-3.2-8.7-.5-18.4 6.4-24.6l43.3-39.4C64.6 273.1 64 264.6 64 256s.6-17.1 1.7-25.4L22.4 191.2c-6.9-6.2-9.6-15.9-6.4-24.6c4.4-11.9 9.7-23.3 15.8-34.3l4.7-8.1c6.6-11 14-21.4 22.1-31.2c5.9-7.2 15.7-9.6 24.5-6.8l55.7 17.7c13.4-10.3 28.2-18.9 44-25.4l12.5-57.1c2-9.1 9-16.3 18.2-17.8C227.3 1.2 241.5 0 256 0s28.7 1.2 42.5 3.5c9.2 1.5 16.2 8.7 18.2 17.8l12.5 57.1c15.8 6.5 30.6 15.1 44 25.4l55.7-17.7c8.8-2.8 18.6-.3 24.5 6.8c8.1 9.8 15.5 20.2 22.1 31.2l4.7 8.1c6.1 11 11.4 22.4 15.8 34.3zM256 336a80 80 0 1 0 0-160 80 80 0 1 0 0 160z" />
                </svg></button>
            </div>
            <div class="message-invite" id="inv"
              v-if="modeAct === 'pvMode' && invList.includes(modeOpt[modeAct].tabs[modeOpt[modeAct].tabCur])">
              Accept the invitation to the game :
              <button class="inv-btn true" @click="acceptInv(true); toggleChat()">Yes</button>
              <button class="inv-btn false" @click="acceptInv(false)">No</button>
            </div>
            <div class="message-box">
              <ul class="message-list">
                <li v-for="msg in modeOpt[modeAct].getMsgList()" :key="msg.id" class="message-item">
                  <p>
                    <span class="msg-from">@{{ msg.from }}</span><br>
                    <span class="msg-body">{{ msg.body }}</span>
                  </p>
                </li>
              </ul>
            </div>
            <div class="message-input">
              <input v-model="inputMsgField" placeholder="Enter your message" @keypress.enter="handleSndMsg" type="text"
                autocomplete="off" />
              <button class="msg-button custom-button" @click="handleSndMsg">
                <img src="../../assets/images/tabler_send.svg">
              </button>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="open-msg-popup" @click="toggleChat()">
      <img src="../../assets/images/msg-icon.svg">
	  <div class="msg-notif" v-if="buttonNotif"></div>
    </div>

  </div>
</template>

<script lang="ts">
import { io, Socket } from 'socket.io-client';
import { defineComponent, watch } from 'vue';
import ChatTabs from './ChatTab';
import ChanForm from './ChanForm';
import UsrList from './UsrList';
import { authToken, hostname, coList, nick } from '@/globalProperties';
import useEventsBus from '@/eventBus';


interface IModeOption { [key: string]: ChatTabs };
interface IMsg { from: string, body: string, to: string };
interface IInv { from: string, to: string };

export default defineComponent({
  name: 'ChatPanel',
  data() {
    return {
      invList: [] as Array<string>,
      blockedUser: [] as Array<string>,
      chatVisible: false,
      chanIn: [] as Array<string>,
      pvIn: [] as Array<string>,
      modeOpt: { 'chanMode': new ChatTabs(), 'pvMode': new ChatTabs() } as IModeOption,
      modeAct: 'pvMode',
      chanForm: new ChanForm(),
      chanUsrList: new UsrList(),
      inputMsgField: '',
      nick: 'guest',
      buttonNotif: false,
      socket: null as null | Socket,
      socketOptions: {
        transportOptions: {
          polling: {
            extraHeaders: {
              Authorization: authToken.value,
            }
          }
        }
      },
    }
  },

  created() {
    this.socket = io(`${hostname.value}/chat`, this.socketOptions);
    const { bus } = useEventsBus();
    watch(() => bus.value.get('customInv'), (val) => {
      const [customInvBus] = val ?? [];
      this.socket?.emit('invGame', { from: this.nick, to: customInvBus });
    });
    watch(() => bus.value.get('updateStatus'), (val) => {
      const [statusBus] = val ?? [];
      this.socket?.emit('updateStatus', statusBus);
    });
  },

  mounted() {
    this.socket?.on('msg', data => {
      this.handleRcvMsg(data as IMsg);
    });
    this.socket?.on('newchan', data => {
      this.updateChanList();
    });
    this.socket?.on('nick', data => {
      this.nick = data;
      this.updateChanList();
      this.updatePvList();
      this.chanForm.mode('none')
      this.modeOpt['chanMode'].tabCur = -1;
      this.modeOpt['chanMode'].tabCur = -1;
      this.invList = [];
    })
    this.socket?.on('newco', data => {
      this.updatePvList();
      const { emit } = useEventsBus();
      emit('updateFriendList', "helloWolrd!");
    })
    this.socket?.on('inv', data => {
      this.msgNotif(data);
    })
    this.socket?.on('invGame', data => {
      if (this.blockedUser.includes(data.from)) {
        this.acceptInv(false);
      }
      else {
        this.handleRcvInv(data);
        this.msgNotif(data.from);
      }
    })
  },

  /*
    beforeMount() {
      window.addEventListener("beforeunload", this.preventRefresh);
    },
    */

  beforeUnmount() {
    this.socket?.close();
    // window.removeEventListener("beforeunload", this.preventRefresh);
  },

  methods: {

    preventRefresh(event: Event) {
      event.preventDefault();
    },

    toggleChat() {
      this.chatVisible = !this.chatVisible;
      if (this.chatVisible) {
        this.buttonNotif = false;
      }
    },

    goToProfile(name: string) {
      this.$router.push({
        name: 'profile',
        params: { username: name }
      })
    },

    gotoChanOpt() {
      this.chanForm.mode('selection');
      const chanName = this.modeOpt[this.modeAct].tabs[this.modeOpt[this.modeAct].tabCur]
      this.chanForm.name = chanName;
      this.chanForm.status = this.chanForm.chanList[chanName];
      this.chanUsrList.init(chanName);
    },

    updateGlobalCoList(userList: string[]) {
      coList.value = [];
      for (const user of userList) {
        coList.value.push({ name: user, status: 'online' });
      }
    },

    async updatePvList() {
      const pvList = await this.chanForm.getPvList();
      const index = pvList.indexOf(this.nick);
      pvList.splice(index, 1);
      this.updateGlobalCoList(pvList);
      this.modeOpt['pvMode'].updateConvList(pvList);
      this.pvIn = [];
      for (let conv in this.modeOpt['pvMode'].tabMsg) {
        if (this.modeOpt['pvMode'].tabMsg[conv].length > 0) {
          this.pvIn.push(conv);
        }
      }
    },

    async updateChanList() {
      const chanList = await this.chanForm.getChanList();
      this.chanIn = await this.chanForm.getChanIn();
      let chanNameList: string[] = [];
      if (chanList.length) {
        for (let chan of chanList) {
          chanNameList.push(chan.name);
          this.chanForm.chanList[chan.name] = chan.status;
        }
      }
      this.modeOpt['chanMode'].updateConvList(chanNameList);
      this.sortChan();
    },

    sortChan() {
      this.chanIn.sort((a, b) => a.localeCompare(b));
      this.modeOpt['chanMode'].tabs = this.chanIn.concat(this.modeOpt['chanMode'].tabs.filter((value: string) => !this.chanIn.includes(value)));
    },

    changeMode(mode: string) {
      this.modeOpt[this.modeAct].tabCur = -1;
      this.modeAct = mode;
      this.chanForm.mode('none');
      if (mode === 'chanMode') {
        this.updateChanList();
      }
      this.modeOpt[this.modeAct].globalNotif = false;
    },

    scrollToBottom() {
      this.$nextTick(() => {
        const messageBox = document.querySelector(".message-box");
        if (messageBox) {
          messageBox.scrollTop = messageBox.scrollHeight;
        }
      })
    },

    async tryTojoinChan() {
      const chanName = this.chanForm.name;
      if (await this.chanForm.join() === 201) {
        await this.updateChanList();
        this.modeOpt['chanMode'].switchTab(this.modeOpt['chanMode'].tabs.indexOf(chanName));
      }
      this.chanForm.reset();
    },

    checkIfJoinNeedPass(chanName: string): boolean {
      if (this.chanForm.chanList[chanName] === 'locked') {
        this.chanForm.askPass = true;
        return true;
      }
      return false;
    },


    changeTab(newTab: number) {
      this.chanForm.reset();
      const chanName = this.modeOpt[this.modeAct].tabs[newTab];
      if (chanName[0] === '#' && !this.chanIn.includes(chanName)) {
        this.chanForm.name = chanName;
        if (!this.checkIfJoinNeedPass(chanName)) {
          this.tryTojoinChan();
        }
      }
      else {
        this.modeOpt[this.modeAct].switchTab(newTab);
      }
    },

    createConv() {
      if (this.modeAct === 'chanMode') {
        this.chanForm.mode('creation');
      }
      else if (this.modeAct === 'pvMode') {
        this.chanForm.mode('selection');
      }
    },

    msgNotif(conv: string) {
      if (!this.chatVisible) {
        this.buttonNotif = true;
      }
      const mode = (conv[0] === '#') ? 'chanMode' : 'pvMode';
      if (this.modeOpt[this.modeAct].tabs[this.modeOpt[this.modeAct].tabCur] != conv) {
        this.modeOpt[mode].addNotif(conv);
      }
      if (mode != this.modeAct) {
        this.modeOpt[mode].globalNotif = true;
      }
    },

    handleRcvInv(inv: IInv) {
      if (!(this.invList.includes(inv.from))) {
        this.invList.push(inv.from);
      }
    },

    handleRcvMsg(msg: IMsg) {
      if (this.blockedUser.includes(msg.from)) {
        return;
      }
      const handle = (msg.to === this.nick) ? msg.from : msg.to;
      const tab = (handle[0] === '#') ? this.modeOpt['chanMode'] : this.modeOpt['pvMode'];
      tab.addConv(handle);
      tab.tabMsg[handle].push({
        id: Math.random().toString(36).substring(2, 11),
        from: msg.from,
        body: msg.body
      });
      this.scrollToBottom();
      this.msgNotif(handle);
    },

    handleSndMsg() {
      if (this.inputMsgField.length > 0) {
        this.socket?.emit('msg', {
          body: this.inputMsgField,
          to: this.modeOpt[this.modeAct].getMsgTarget(),
          from: this.nick
        });
        this.inputMsgField = '';
      }
    },

    toggleBlockUser(userName: string) {
      this.blockUser(userName, !(this.blockedUser.includes(userName)));
    },

    blockUser(userName: string, block: boolean) {
      if (!(this.blockedUser.includes(userName)) && block) {
        this.blockedUser.push(userName);
      }
      else {
        const index = this.blockedUser.indexOf(userName);
        if (index >= 0 && !block) {
          this.blockedUser.splice(index, 1);
        }
      }
    },

    async createChan() {
      const response = await this.chanForm.create(this.nick);
      if ('name' in response) {
        await this.chanForm.join();
        this.updateChanList();
        this.modeOpt[this.modeAct].addConv(response.name);
      }
      this.chanForm.reset();
    },

    async joinChan() {
      const response = await this.chanForm.join();
      this.chanForm.reset();
    },

    sendCmd(cmd: string, target: string) {
      this.chanUsrList.sendCmd(cmd, target);
      this.chanForm.selecting = false;
      this.chanUsrList.invite = '';
    },


    async acceptInv(answer: boolean) {
      try {
        const ansCode = answer ? 'y' : 'n';
        const target = this.modeOpt[this.modeAct].tabs[this.modeOpt[this.modeAct].tabCur];
        const index = this.invList.indexOf(target);
        if (index !== -1) {
          this.invList.splice(index, 1);
        }
        const response = await fetch(`${hostname.value}/pong/vs/${target}/${ansCode}`, {
          method: 'POST',
          headers: {
            'Authorization': `Bearer ${authToken.value}`,
            'accept': 'application/json',
          },
        });
        if (answer && response.status === 201) {
          const currentPath = this.$router.currentRoute.value.name;
          if (currentPath !== 'pong') {
            // this.$router.push({ name: 'pong' });
            this.$router.push({ name: 'pong', query: { reload: 0 } });
          }
          else {
            // this.$router.replace({ name: 'home' });
            this.$router.push({ name: 'pong', query: { reload: 1 } });
          }
        }
        return response.status;
      } catch (error) {
        // console.error(error);
        return 0;
      }
    },

    async inviteToPlay(target: string) {
      if (this.invList.includes(target)) {
        this.acceptInv(true);
        return 1;
      }
      try {
        const response = await fetch(`${hostname.value}/pong/vs/${target}`, {
          method: 'POST',
          headers: {
            'Authorization': `Bearer ${authToken.value}`,
            'accept': 'application/json',
          },
        });
        if (response.status === 201) {
          this.socket?.emit('invGame', { from: this.nick, to: target });
          const currentPath = this.$router.currentRoute.value.name;
          if (currentPath !== 'pong') {
            // this.$router.push({ name: 'pong' });
            this.$router.push({ name: 'pong', query: { reload: 0 } });
          }
          else {
            // this.$router.replace({ name: 'home'});
            // this.$router.replace({ name: 'home' });
            this.$router.push({ name: 'pong', query: { reload: 1 } });
          }
        }
        return response.status;
      } catch (error) {
        // console.error(error);
        return 0;
      }
    },
  },

})
</script>

<style scoped>
/* /////////// GLOBAL /////////// */

.chat-popup-background {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.6);
  backdrop-filter: blur(2px);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 90;
  overflow-x: auto;
}

.open-msg-popup {
  display: flex;
  justify-content: center;
  align-items: center;
  position: fixed;
  bottom: 3rem;
  right: 5rem;
  z-index: 55;
  width: 54px;
  height: 54px;
  border-radius: 50%;
  cursor: pointer;
  border: 1px solid #00B8F8;
  background: #121212;
  box-shadow: 0px 0px 15px 0px #00B8F8;
  transition: 100ms ease-out;
}

.open-msg-popup .msg-notif {
	position: absolute;
	right: 0;
	bottom: 0;
	content: '';
	width: 12px;
	height: 12px;
	background: #00B8F8;
	border-radius: 50%;
}

.open-msg-popup:hover {
  background: #262626;
}

.chat-logo {
  display: flex;
  align-items: center;
  justify-content: start;
  gap: 6px;
  font-size: 16px;
  font-weight: 600;
  padding-left: 10px;
}

.chat-panel {
  height: 80vh;
  width: 70vw;
  min-width: 1100px;
  max-width: 1200px;
  background: #121212;
  border: 1px solid #00B8F8;
  box-shadow: 0px 0px 15px 0px #00B8F8;
  border-radius: 20px;
  display: flex;
  flex-direction: row;
  color: #FFFFFF;
}


.panel {
  padding: 24px 18px;
  display: flex;
  flex-direction: column;
  justify-content: start;
  align-items: start;
  box-sizing: border-box;
  /* background: yellowgreen; */
}


.panel:first-child {
  position: relative;
  flex: 0.8;
  border-right: 1px solid #00B8F8;
  justify-content: start;
  align-items: left;
  gap: 24px;

}

.panel:nth-child(2) {
  position: relative;
  display: flex;
  flex: 0.9;
  padding-bottom: 16px;
}

.panel:last-child {
  position: relative;
  border-left: 1px solid #00B8F8;
  flex: 2;
  padding: 0;
  width: 100%;
}

/* /////////// MODE /////////// */

.modes-div {
  display: flex;
  flex-direction: column;
  width: 100%;
  gap: 4px;
}

.mode-btn {
  display: flex;
  justify-content: start;
  align-items: center;
  background-color: #121212;
  border: 0px;
  color: #FFFFFF;
  border-radius: 10px;
  padding: 12px 14px;
  font-size: 14px;
  ;
  font-weight: 500;
  cursor: pointer;
  width: 100%;
  gap: 8px;
}

.mode-btn:hover {
  background-color: #262626;
}

.selected {
  background-color: #262626;
}

/* /////////// CHAN/USER LIST /////////// */

.chan-panel {
  overflow-y: auto;
  flex: 1;
  width: 100%;
  display: flex;
  justify-content: start;
  align-items: start;
  /* padding: 40px 40px; */
}

.chan-list {
  display: flex;
  flex-direction: column;
  justify-content: start;
  align-items: left;
  width: 100%;
  gap: 4px;
}

.chan-list div {
  border: none;
  color: #535353;
  border-radius: 10px;
  padding: 12px 14px;
  font-size: 14px;
  font-weight: 500;
  cursor: pointer;
  /* width: 100%; */
  /* gap: 8px; */
  transition: all 100ms ease;
}

.chan-list div:hover {
  background-color: #262626;
}

.chan-list .in {
  color: #ffffff;
  background-color: #121212;
}

.chan-list .unread {
  font-weight: 700;
  background-color: #612121;
}

.chan-list .active {
  background-color: #262626;
}

.chan-new-btn {
  border-radius: 10px;
  border: 1px solid #00B8F8;
  color: #FFFFFF;
  background-color: #161616;
  cursor: pointer;
  width: 100%;
  font-size: 14px;
  font-weight: 600;
}

.chan-new-btn:hover {
  background-color: #262626;
}

/* /////////// CHAN CREATION /////////// */
.creation-menu {
  padding: 10px;
}

.ask-pass {
  width: 100%;
}

.ask-pass .message-title {
  margin-bottom: 10px;
}

.ask-pass label {
  margin-left: 16px;

}

.ask-pass input {
  margin-left: 14px;
  margin-top: 6px;
}

/* /////////// CHAN USERLIST /////////// */
.chan-selection {
  display: flex;
  flex-direction: column;
  overflow-y: auto;
  flex-grow: 1;
  width: 100%
}

.usr-lst {
  padding-left: 0;
  list-style-type: none;
}

.usr-name {
  display: flex;
  margin: 0px 10px;
  padding: 10px 0px;
  border-bottom: 1px solid rgb(80, 80, 80);
  justify-content: space-between;
}

.option-btn-op {
  /* margin-right: 15px; */
}

.usr-btn {
  border: none;
  fill: white;
  padding: 8px 6px;
}

.usr-name i {
  color: #868686;
}

.usr-name button {
  margin-right: 5px;
  color: #FFFFFF;
}

.owner-opt {
  margin-top: 5px;
  margin-left: 10px;
}

.owner-opt>* {
  margin: 5px;
}

.admin-opt {
  margin-top: 5px;
  margin-left: 10px;
}

.admin-opt>* {
  margin: 5px;
}



/* ////////// MESSAGES //////////// */

.message-panel {
  width: 100%;
  display: flex;
  flex-direction: column;
  overflow-y: auto;
  flex-grow: 1;
}

.message-title {
  border-radius: 0 20px 0 0;
  padding: 0 14px;
  font-size: 18px;
  font-weight: 600;
  /* background-color: #262626; */
  display: flex;
  justify-content: space-between;
  align-items: center;
  border-bottom: 1px solid #00B8F8;
}

.message-box {
  flex: 1;
  overflow-y: auto;
  margin: 10px 10px;
}

.message-list {
  padding-left: 4px;
  margin: 0;
  list-style-type: none;
  display: flex;
  flex-direction: column;
  gap: 4px;
}

.message-item {
  font-weight: 400;
  font-size: 14px;
}

.message-item p {
  margin: 0;
}

.message-item .msg-from {
  color: #a7a7a7;
  font-size: 12px;
  font-weight: 600;
  /* margin-bottom: 0.5em; */
}

.message-invite {
  display: flex;
  justify-content: start;
  align-items: center;
  gap: 12px;
  background-color: #262626;
  padding: 10px 20px;
  font-weight: 500;
  font-size: 14px;
}


.inv-btn {
  font-weight: 500;
  font-size: 14px;
  border-radius: 5px;
  padding: 6px 12px;
}

.inv-btn.true {
  background-color: rgb(33, 126, 33);
}

.inv-btn.false {
  background-color: rgb(224, 59, 59);
}


/* //    SEND MESSAGE // */
.message-input {
  margin-bottom: 16px;
  margin-right: 10px;
  margin-left: 10px;
  display: flex;
  justify-content: center;
  align-items: center;
  border-radius: 10px;
  background: #262626;

}

.message-input input {
  flex: 1;
  border: none;
}


.message-input button {
  background: none;
  border: none;
  cursor: pointer;
  font-weight: bold;
}

.pv-btn {
  display: flex;
  justify-content: end;
  gap: 16px;
}

.option-btn {
  border: 1px solid #00B8F8;
}


.option-btn svg {
  fill: white;
}

.chat-form {
  display: flex;
  padding: 10px 10px;
}

.send-button {
  /* background: #ccc; */
  border: none;
  border-radius: 0 4px 4px 0;
  padding: 8px;
  cursor: pointer;
  fill: white;
}
</style>
