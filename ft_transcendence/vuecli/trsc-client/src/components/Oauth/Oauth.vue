<template>
  <!-- <div class="login-panel">
      <button v-if="block == 0" @click="send2fa()">CONTINUE</button>
      <p v-if="block != 0"> Please Wait...</p>
      <input v-if="block == 0" v-model="OauthForm.twoFactorAuthenticationCode"
              type="text"
              id="code2fa"
              autocomplete="off"
              placeholder="2fa code" />
  </div> -->
  	<div class="o-auth">
		<div class="o-auth-panel">
			<p v-if="block == 0">If you have enabled two-factor authentication, please provide the 2fa code, if not, just click continue.</p>
			<input v-if="block == 0" v-model="OauthForm.twoFactorAuthenticationCode"
            @change="checkCode()"
            type="text"
            id="code2fa"
            autocomplete="off"
            placeholder="2fa code" />
      <p v-if="codeInvalid">The code must be 6 digits</p>
			<button v-if="block == 0" @click="send2fa()">Continue</button>
			<p v-if="block != 0"> Please Wait...</p>
		</div>
	</div>
</template>

<script lang="ts">

import { authToken } from '@/globalProperties';
import  OauthForm  from './OautForm';

export default {
  name: "Callback",
  data() {
    return {
      is2faEnabled: false,
      OauthForm: new OauthForm(), 
      token: "",
      code: "" as string | null,
      block: 0,
      codeInvalid: false,
    };
  },
  mounted() {
    
  }, 
  methods: {
    checkCode() {
      this.codeInvalid = false;
      if (this.OauthForm.twoFactorAuthenticationCode == null || this.OauthForm.twoFactorAuthenticationCode.length === 0) {
        this.codeInvalid = false;
      }
      else {
        if (this.OauthForm.twoFactorAuthenticationCode.length !== 6) {
          this.codeInvalid = true;
        }
        for (const c of this.OauthForm.twoFactorAuthenticationCode) {
          if (!/\d/.test(c)) {
            this.codeInvalid = true;
          }
        }
      }
    },
    
      async continueFt()
      {
        const urlParams = new URLSearchParams(window.location.search);
        this.code = urlParams.get('code');
        this.token = await this.OauthForm.signin(this.code);
        if (this.token === '2fa') {
                        //todo
                        this.is2faEnabled = true;
                        return ;
                    }
        else if (this.token != undefined) {
                        authToken.value = this.token;
                        sessionStorage.setItem('authToken', authToken.value)
                        this.$router.push({name: 'home'});
                    }
        else
        {
            this.$router.push({name: '/login'});
        }
      },
      async send2fa()
      {
        if (this.codeInvalid) {
          return;
        }
        this.block++;
        const urlParams = new URLSearchParams(window.location.search);
        this.code = urlParams.get('code');
        this.token = await this.OauthForm.signin2fa(this.code);
        if (this.token != undefined) {
                        authToken.value = this.token;
                        sessionStorage.setItem('authToken', authToken.value)
                        this.$router.push({name: 'home'});
        }
        else
        {
            this.$router.push({name: 'login'});
          return;
        }
      },
}
}
</script>

<style scoped>
.o-auth {
	min-height: 96vh;
	display: flex;
	justify-content: center;
	align-items: center;
}

.o-auth-panel {
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

.o-auth-panel p {
	text-align: center;
	font-size: 14px;
	font-weight: 500;
}
</style>