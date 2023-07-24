import { authToken, hostname } from '@/globalProperties';

interface IUsr { name: string, id: string, status: string}
interface IStatus { status: string }

export default class UsrList {
    usrList: IUsr[];
    owner: boolean;
    admin: boolean;
    chanName: string;
    invite: string;
    
    constructor() {
        this.usrList = [];
        this.owner = false;
        this.admin = false;
        this.chanName = '';
        this.invite = '';
    }

    isOp(name: string): boolean {
        const usr = this.usrList.find(usr => usr.name === name);
        return (usr?.status !== 'none');
    }

    isOw(name: string): boolean {
        const usr = this.usrList.find(usr => usr.name === name);
        return (usr?.status === 'owner');
    }


    async getOpStatus(): Promise<IStatus> {
        const requestOption = {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${authToken.value}`,
                'accept': 'application/json',
            },
        }
        return fetch(`${hostname.value}/chat/opstatus/%23${this.chanName.slice(1)}`, requestOption)
            .then(response => response.json())
            .then(data => {
                return data;
            })
            .catch(error => { 
                //console.error(error);
            });
    }
    
    async getUsrList(): Promise<IUsr[]> {
        const requestOption = {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${authToken.value}`,
                'accept': 'application/json',
            },
        }
        return fetch(`${hostname.value}/chat/usrlst/%23${this.chanName.slice(1)}`, requestOption)
            .then(response => response.json())
            .then(data => {
                return data;
            })
            .catch(error => {
                // console.error(error);
            });
    }

    async updateUsrList() {
        let usrList = await this.getUsrList();
        if (usrList.length > 1) {
            usrList = usrList.sort();
        }
        this.usrList = [];
        for (const usr of usrList) {
            this.usrList.push({ name: usr.name, status: usr.status, id: Math.random().toString(36).substring(2, 11) });
        }
    }

    async init(chanName: string) {
        this.chanName = chanName;
        const status = (await this.getOpStatus()).status;
        if (status === 'owner') {
            this.owner = true;
            this.admin = true;
        }
        else if (status === 'admin') {
            this.admin = true;
            this.owner = false;
        }
        else {
            this.admin = false;
            this.owner = false;
        }
        this.updateUsrList();
    }

    inviteToChan() {
        this.sendCmd('inv', this.invite);
        this.invite = '';
    }

    async sendCmd(cmd: string, target: string) {
        const response =  await fetch(`${hostname.value}/chat/${cmd}/%23${this.chanName.slice(1)}/${target}`, {
            method: 'POST',
            headers: {
                'Authorization': `Bearer ${authToken.value}`,
                'accept': 'application/json',
                'Content-Type': 'application/json'
            },
        });
        this.updateUsrList();
    }
}
