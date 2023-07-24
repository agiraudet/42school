import { hostname } from '@/globalProperties'; 

interface IAuth {authToken: string}

export default class LoginForm {
    username: string;
    password: string;
    email: string;
    twoFactorAuthenticationCode: string;

    constructor() {
        this.username = '';
        this.password = '';
        this.email = '';
        this.twoFactorAuthenticationCode = '';
    }

    reset() {
        this.username = '';
        this.password = '';
        this.email = '';
        this.twoFactorAuthenticationCode = '';
    }

    async signin(): Promise<string> {
        const requestOption = {
            method: 'POST',
            headers: {
	        'accept': 'application/json',
		'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                username: this.username,
                password: this.password,
                email: this.email
            })
        }
        return fetch(`${hostname.value}/auth/signin`, requestOption)
            .then(response => {
                if (response.status === 503)
                {
                    return ({accessToken: "2fa"});
                }
                else {
                    return response.json();
                }
            })
            .then(data => {
                return (data.accessToken);
            })
            .catch(error => { 
                // console.error(error);
            });
    }

    async signup(): Promise<number> {
        try {
            const requestOption = {
                method: 'POST',
                headers: {
                    'accept': 'application/json',
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    username: this.username,
                    password: this.password,
                    email: this.email
                })
            }
            const response = await fetch(`${hostname.value}/auth/signup`, requestOption);
            return response.status;
        } catch (error) {
            // console.error(error);
            return 0;
        }
    }

    async signin2fa(): Promise<any>
    {
        const requestOption = {
            method: 'POST',
            headers: {
	        'accept': 'application/json',
		'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                username: this.username,
                password: this.password,
                twoFactorAuthenticationCode: this.twoFactorAuthenticationCode,
            })
        }
        return fetch(`${hostname.value}/auth/2fa/signin`, requestOption)
            .then(response => {
                    return response.json();
            })
            .then(data => {
                return (data.accessToken);
            })
            .catch(error => { 
                // console.error(error);
            });
    }
}
