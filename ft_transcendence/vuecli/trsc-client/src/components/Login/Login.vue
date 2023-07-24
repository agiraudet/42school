<template>
	<div class="login">
		<div class="login-header">
			<img src="../../assets/images/Login-img.png"/>
			<p>Connect, Compete, and Conquer the Pong Arena !</p>
		</div>
		<div class="signin-signout-container">
			<!-- sign in with 42 -->
			<div class="ft-signin-div">
				<button class="button-3d" @click="schoolAuth()">Sign in with 42</button>
			</div>
			<div class="horizontal-div">
				<hr class="horizontal-line">
				<span class="text">or</span>
				<hr class="horizontal-line">
			</div>
			<!-- Classic Sign in -->
			<div class="sign-div" v-if=" mode === 'signin'">
				<div class="sign-buttons">
					<button class="sign-button-active">
						Sign in
					</button>
					<button class="sign-button" @click="toggleMode()">
						Sign up
					</button>
				</div>
				<div class="sign-forms">
					<div class="sign-form">
						<span class="placeholder">Username</span>
						<input class ="form" v-model="loginForm.username"
    	    	    	@keydown.enter="sendForm()"
    	    	    	type="text"
    	    	    	id="username" 
    	    	    	autocomplete="off"
    	    	    	placeholder="username" />
					</div>
					<div class="sign-form">
							<span class="placeholder">Password</span>
							<input class ="form" v-model="loginForm.password"
    	    	    		@keydown.enter="sendForm()"
    	    	    		type="password"
    	    	    		id="password"
    	    	    		autocomplete="off"
    	    	    		placeholder="password" />
					</div>
					<div class="sign-form" v-if="is2fa == true">
						<span class="placeholder">2FA</span>
						<input class ="form" v-model="loginForm.twoFactorAuthenticationCode"
    	        		@keydown.enter="sendForm()"
						@change="check2FACode()"
    	        		type="text"
    	        		id="code2fa"
    	        		autocomplete="off"
    	        		placeholder="2fa code" />
						<p v-if="codeInvalid">2FA code should be 6 digits</p>
					</div>
    	        	<!--form // for 2fa auth-->
					<button class="button-3d" @click="sendForm()">Sign in</button>
				</div>
			</div>
			<!-- Sign up -->
			<div v-else class="sign-div">
				<div class="sign-buttons">
					<button class="sign-button" @click="toggleMode()">
						Sign in
					</button>
					<button class="sign-button-active">
						Sign up
					</button>
				</div>
				<div class="sign-forms">
					<div class="sign-form">
						<span class="placeholder">Email</span>
						<input class="form" v-model="loginForm.email"
    	        		@keydown.enter="sendForm()"
    	        		type="text"
    	        		placeholder="email" />
					</div>
					<div class="sign-form">
						<span class="placeholder">Username</span>
						<input class="form" v-model="loginForm.username"
    	        		@keydown.enter="sendForm()"
    	        		type="text"
    	        		id="username" 
    	        		autocomplete="off"
    	        		placeholder="username" />
					</div>
					<div class="sign-form">
						<span class="placeholder">Password</span>
						<input class="form" v-model="loginForm.password"
    	        		@keydown.enter="sendForm()"
    	        		type="password"
    	        		id="password"
    	        		autocomplete="off"
    	        		placeholder="password" />
					</div>
					<button class="button-3d" @click="sendForm()">Sign up</button>
				</div>
			</div>
		</div>
		<!-- alert popup -->
		<div v-if="showPopup" class="popup" :class="{ 'show': showPopup, 'slide-out': slideOut }">
      		{{ popupMessage }}
  		</div>

	</div>
</template>

<script lang="ts">
import { defineComponent } from 'vue';
import LoginForm from './LoginForm';
import { authToken } from '@/globalProperties';

export default defineComponent({
    name: 'LoginPanel',
    data() {
        return {
            toggleBtn: 'signup',
            mode: 'signin',
            loginForm: new LoginForm(),
            token: undefined as undefined | string,
            OAuthToken: null as null | string,
            is2fa: false,
            isWrong: false,
            credentialWrong: false,
			showPopup: false,
      		slideOut: false,
			popupMessage: '',
			codeInvalid: false,
        }
    },

    methods: {

		check2FACode() {
			this.codeInvalid = false;
			if (this.loginForm.twoFactorAuthenticationCode == null || this.loginForm.twoFactorAuthenticationCode.length === 0) {
				this.codeInvalid = false;
			}
			else {
				if (this.loginForm.twoFactorAuthenticationCode.length !== 6) {
				this.codeInvalid = true;
				}
				for (const c of this.loginForm.twoFactorAuthenticationCode) {
				if (!/\d/.test(c)) {
					this.codeInvalid = true;
				}
				}
			}
		},

        toggleMode() {
            this.mode = (this.mode === 'signin') ? 'signup' : 'signin';
            this.toggleBtn = (this.mode === 'signin') ? 'signup' : 'signin';
        },

        async sendForm() {
            if (this.is2fa == true)
            {
				if (this.codeInvalid) {
					return;
				}
                this.token = await this.loginForm.signin2fa();
                if (this.token != undefined) {
                    authToken.value = this.token;
                    sessionStorage.setItem('authToken', authToken.value)
                    this.$router.push({name: 'home'});
                    return ;
                }
                else
                {
                    this.mode = 'signin';
                }
                this.loginForm.reset();
                this.is2fa = false;
                // this.isWrong = true;
				this.displayPopup('Access Denied. Please try again');
                return ;
            }
            switch(this.mode) {
                case 'signin':
                    this.token = await this.loginForm.signin();
                    if (this.token === '2fa') {
                        this.is2fa = true;
                    }
                    else if (this.token != undefined) {
                        authToken.value = this.token;
                        sessionStorage.setItem('authToken', authToken.value)
                        this.$router.push({name: 'home'});
                    }
                    else
                    {
                        this.mode = 'signin';
                    }
                    if (this.is2fa != true)
                    {
                        this.loginForm.reset();
                        // this.isWrong = true;
						this.displayPopup('Access Denied. Please try again');
                    }
                    break;
                case 'signup':
                    if (await this.loginForm.signup() != 201) {
                        this.loginForm.reset();
                        // this.credentialWrong = true;
						this.displayPopup('Weak password or taken username. Password requires uppercase, lowercase, and digit/special character.');
                    }
                    else {
						this.displayPopup('Account created successfully !');
                        this.mode = 'signin';
						this.loginForm.reset();
                    }
                    break;
            }
        },
        schoolAuth() 
    	{
        window.location.href = 'http://localhost:3000/auth/school';
        },
		displayPopup(message : string) {
    		this.popupMessage = message;
      		this.showPopup = true;
      		this.slideOut = false;

      		setTimeout(() => {
      		  this.slideOut = true;
      		  setTimeout(() => {
      		    this.showPopup = false;
      		    this.slideOut = false;
      		  }, 300);
      		}, 5000);
    	},
    }
})
</script>

<style scoped>

.popup {
  position: fixed;
  top: 20px;
  padding: 12px 12px;
  box-shadow: 0px 0px 10px 0px #00B8F8;
  /* height: 40px; */
  border-radius: 10px;
  background: rgba(18, 18, 18, 0.704);
  transition: 0.3s right ease-in-out;
  color: white;
  display: flex;
  justify-content: center;
  align-items: center;
  font-size: 12px;
  font-weight: 500;
  max-width: 240px;
}

.popup.show {
  right: 20px;
}

.popup.slide-out {
  right: -300px;
}

.login {
	display: flex;
	flex-direction: column;
	align-items: center; /* Centre verticalement */
	justify-content: center; /* Centre horizontalement */
	padding-top: 6vh;
}

.login-header {
	display: flex;
	flex-direction: column;
	justify-content: center; /* Centre horizontalement */
	gap: 18px;
	margin-bottom: 40px;
}

.signin-signout-container {
	display: flex;
	flex-direction: column;
	gap: 24px;
	justify-content: center;
}

.ft-signin-div {
	display: flex;
	justify-content: center; /* Centre horizontalement le contenu */
	margin: 0 auto; /* Centre horizontalement la div */
}

.horizontal-div {
  	display: flex;
  	align-items: center;
  	margin: 0 auto; /* Centre horizontalement */
  	width: 340px;
}

.horizontal-line {
 	width: 200px; /*Largeur des traits*/
  	border: none;
  	border-top: 1px solid white;

}

.text {
 	margin: 0 10px;
}

.sign-div {
	display: flex;
	flex-direction: column;
	justify-content: center;
	align-items: center;
	gap: 24px;
}



.sign-buttons {
	display: inline-flex;
	border-radius: 10px;
	border: 1px solid #FFF;
	background: rgba(18, 18, 18, 0.50);
	padding: 6px;
	gap: 2px;
}

.sign-button {
	border-radius: 5px;
	border: none;
	background: none;
	padding: 10px 49px;
	cursor: pointer;
	color: white;
	font-family: poppins, sans-serif;
	font-weight: 500;
	font-size: 12px;
}

.sign-button-active {
	border-radius: 5px;
	border: none;
	background-color: #F800F8;
	color: white;
	padding: 10px 49px;
	font-family: poppins, sans-serif;
	font-weight: 500;
	font-size: 12px;

}

.sign-forms {
	display: flex;
	flex-direction: column;
	align-items: center;
	gap: 18px
}

/* .username-form {
	display: flex;
	flex-direction: column;
	gap: 6px;
} */

.sign-form {
	display: flex;
	flex-direction: column;
	gap: 6px;
	margin-bottom: 8px;
}

.placeholder {
	padding-left: 8px;;
}

.form {
	padding: 0 10px;
	width: 280px;
	height: 40px;
	border-radius: 10px;
	border: 1px solid #000;
	background: #FFF;
	box-shadow: 2px 4px 0px 0px #F30FF8;
	color: black;
}

.form:focus {
	outline: none;
}
.login-panel {
    margin: auto;
    display: flex;
    flex-direction: column;
    width: 300px;
    padding: 10px;
    background: #121212;
    color: #FFFFFF;
    font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
    justify-content: center;
    align-items: center;
    border-radius: 20px;
    border: solid 2px white;
}

.login-panel input {
    margin: 10px;
}

.login-panel button {
    margin: 10px;
    padding: 5px;
    width: 50%;
}
</style>