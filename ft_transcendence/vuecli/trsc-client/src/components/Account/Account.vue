<template>
	<div class="account">
  		<div class="account-settings">
  		  <div class="tfa-settings">
  		    <div class="tfa-set-on" v-if="!is2FAEnabled">
  		      <div class="tfa-btn" v-if="!activating2FA">
  		        <button @click="twofaTurnOn()">Enable 2FA</button>
  		      </div>
  		      <div class="tfa-qr" v-else>
  		        <img class="qrcode" :src="qrCodeLink" />
  		        <button @click="copyQRCodeLink()">Copy link</button>
  		        <input type="text" placeholder="0123456" v-model="authCode" />
  		        <button @click=validate2FA()>Submit</button>
  		        <p v-if="isErrorCode == true"> Wrong code ! Please try again</p>
  		        <p v-if="isSuccess2FA == true"> 2FA has been activated</p>
  		      </div>
  		    </div>
  		    <div class="tfa-set-off" v-else>
  		      <button @click="twofaTurnOff()">Disable 2FA</button>
  		    </div>
  		  </div>
  		  <div class="avatar-settings">
  		    <div class="avatar-menu">
  		      <input type="file" accept="image/jpg, image/png, image/jpeg" @change="onFileChange">
  		      <button @click="submitFile" v-if="selectedFile != null">Upload</button>
  		    </div>
  		    <Avatar :msg="username" :key="avCount" />
  		  </div>
  		</div>
	</div>
</template>

<script lang="ts">
import Avatar from '@/components/Profile/Avatar.vue';
import { authToken } from '@/globalProperties';
import AccountFunc from './AccountFunct';
import { hostname, nick } from '@/globalProperties';
import { ref } from 'vue';

export default {
  name: 'Account',
  components: {
    Avatar,
  },
  data() {
    return {
      username: nick.value, //
      AccountFunc: new AccountFunc,
      is2FAEnabled: false,
      qrCodeLink: "",
      avCount: 0,
      avatar: null as File | null,
      authCode: '',
      selectedFile: null as File | null,
      avatarUrl: ref(''),
      isErrorCode: false,
      isSuccess2FA: false,
      activating2FA: false,
    };
  },

  mounted() {
    this.isTrue2FA();
  },

  methods: {

    twofaTurnOff() {
      this.activating2FA = false;
      this.deactivate2fa();
    },

    twofaTurnOn() {
      this.activating2FA = true;
      this.generateQRCode();
    },

    onFileChange(e: Event) {
      const target = e.target as HTMLInputElement;
      if (target.files) {
        this.selectedFile = target.files[0];
      }
    },

    async isTrue2FA() {
      this.is2FAEnabled = await this.AccountFunc.is2faActivated(this.is2FAEnabled);
    },

    async submitFile() {
      const token = authToken.value;
      if (!this.selectedFile) {
        // console.error("No file selected");
        return;
      }

      let formData = new FormData();

      formData.append('file', this.selectedFile);
      try {
        const requestOption = {
          method: 'POST',
          headers: {
            'Authorization': `Bearer ${token}`,
            'accept': 'application/json',
          },
          body: formData
        }
        const response = await fetch(`${hostname.value}/auth/upload`, requestOption);

        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        } else {
          this.avatar = this.selectedFile;
          this.selectedFile = null;
          this.avCount++;
        }

      } catch (error) {
        // console.error('There was a problem with the fetch operation: ' + error);
      }
    },

    async deactivate2fa() {
      try {
        await this.AccountFunc.deactivate2fa();
        this.is2FAEnabled = false;
      } catch (error) {
        // console.error(error);
      }
    },

    toggle2FA() {
      this.is2FAEnabled = true;
    },

    async generateQRCode() {
      this.qrCodeLink = await this.AccountFunc.generateQrCode();
    },

    copyQRCodeLink() {
      navigator.clipboard.writeText(this.qrCodeLink);
    },

    async validate2FA() {
      try {
        const res = await this.AccountFunc.turnOn2fa(this.authCode, this.isErrorCode);
        if (res < 0) {
          this.isErrorCode = true;
          this.isSuccess2FA = false;
        }
        if (res == 1) {
          this.isErrorCode = false;
          this.isSuccess2FA = true;
          this.activating2FA = false;
          this.is2FAEnabled = true;
        }
      } catch (error) {
        // console.error('Failed to validate 2FA code:', error);
      }
    },
  },
};
</script>

<style scoped>
.account-settings {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.account-settings div {
  margin-bottom: 20px;
}

.tfa-settings div {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.tfa-settings {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.avatar-settings {
  display: flex;
  flex-direction: column;
  align-items: center;
}
</style>
