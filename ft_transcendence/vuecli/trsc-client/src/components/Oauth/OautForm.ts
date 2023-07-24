import { hostname } from '@/globalProperties'; 

interface IAuth {authToken: string}

export default class OauthForm{
    twoFactorAuthenticationCode: string;

    constructor() {
        this.twoFactorAuthenticationCode = '';
    }

    reset() {
        this.twoFactorAuthenticationCode = '';
    }

    async signin(code : string | null): Promise<string> {
        const requestOption = {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ code }),
        }
        return fetch(`${hostname.value}/auth/school/callback`, requestOption)
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
                //console.error(error); 
            });
    }

    async signin2fa(code : string | null): Promise<string>
    {
        const requestOption = {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                code: code,
                twoFactorAuthenticationCode: this.twoFactorAuthenticationCode,
            })
        }
        return fetch(`${hostname.value}/auth/school/callback2fa`, requestOption)
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
