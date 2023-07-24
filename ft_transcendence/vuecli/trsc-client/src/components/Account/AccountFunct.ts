import { authToken, hostname  } from '@/globalProperties';

interface IAuth {authToken: string}


export default class AccountFunc {
    twoFactorAuthenticationCode: string;
    qrcode: string;
    is2fa: boolean;
    
    constructor()
    {
        this.twoFactorAuthenticationCode = '';
        this.qrcode = '';
        this.is2fa = false;
    }

    reset()
    {
        this.twoFactorAuthenticationCode = '';
        this.qrcode = '';
        this.is2fa = false;
    }

    async generateQrCode() : Promise<any>
    {
            const token = authToken.value;
        const requestOption = {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${token}`,
                'Content-Type' : 'application/json',
            },
        }
        const response = await fetch(`${hostname.value}/auth/2fa/generate`, requestOption);
        const data = await response.text();
        return data;
    }

    isValidCode(code: string): boolean {
        if (code.length !== 6) {
            return false;
        }
        for (const char of code) {
            if (!/\d/.test(char)) {
                return false;
            }
        }
        return true;
    }


    async turnOn2fa(twoFactorAuthenticationCode: string, isErrorCode: boolean)
    {
        if (!this.isValidCode(twoFactorAuthenticationCode)) {
            return -1;
        }
        const token = authToken.value;
        const requestOption = {
            method: 'POST',
            headers: {
                'Authorization': `Bearer ${token}`,
                'Content-Type' : 'application/json',
            },
            body: JSON.stringify({
                twoFactorAuthenticationCode: twoFactorAuthenticationCode,
            })
        }
        try {
            const response = await fetch(`${hostname.value}/auth/2fa/turn-on`, requestOption);
            if (response.status === 401)
            {
                return -1;
            }
            return 1;
        } catch (error)
        {
            // console.error(error);
            return 0;
        }
    }
    async deactivate2fa()
    {
        const token = authToken.value;
        const requestOption = {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${token}`,
                'Content-Type' : 'application/json',
            },
        }
        try {
            const reponse = await fetch(`${hostname.value}/auth/deactivate-2fa`, requestOption);
        } catch (error)
        {
            // console.error(error);
            return false;
        }
        return true;
    }
    async is2faActivated(is2fa: Boolean)
    {
        const token = authToken.value;
        const requestOption = {
            method: 'GET',
            headers: {
                'Authorization' : `Bearer ${token}`,
                'Content-Type' : 'application/json', 
            },
        }
        const response = await fetch(`${hostname.value}/auth/is2fa`, requestOption);
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
    
        const data = await response.json();
        const booleanValue = data; // replace with your key
        return booleanValue;
    }
/* 
POST generateQrCode [bearer token/] (return QR code)
POST turnOn2fa  [bearer token/ authenticationCode] (return void/or error msg/) 
*/
}