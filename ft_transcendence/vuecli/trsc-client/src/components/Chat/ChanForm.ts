import { authToken, hostname } from "@/globalProperties";

export interface IChan { name: string, status: string}

export default class ChanForm {
	name: string;
	status: string;
	password: string;
	creating: boolean;
	selecting: boolean;
	askPass: boolean;
	chanList: {[name: string]: string};

	constructor() {
		this.name = '';
		this.status = 'public';
		this.password = '';
		this.creating = false;
		this.selecting = false;
		this.askPass = false;
		this.chanList = {};
	}

	reset() {
		this.name = '';
		this.status = 'public';
		this.password = '';
		this.creating = false;
		this.selecting = false;
		this.askPass = false;
	}

	async updateChanList() {
		const newList = await this.getChanList();
		this.chanList = {};
		for (const chan of newList) {
			this.chanList[chan.name] = chan.status;
		}
	}

	async create(owner: string) {
		if (this.name[0] !== '#') {
			this.name = `#${this.name}`;
		}
		const requestOption = {
			method: 'POST',
			headers: {
				'Authorization': `Bearer ${authToken.value}`,
				'accept': 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({
				name: this.name,
				status: this.status,
				owner: owner,
				password: this.password
			})
		}
		return fetch(`${hostname.value}/chat/new-chan`, requestOption)
			.then(response => response.json())
			.then(data => {
				return data;
			})
			.catch(error => {
				// console.error(error);
			});
	}


	async join(): Promise<number> {
		try {
			const response =  await fetch(`${hostname.value}/chat/join/%23${this.name.slice(1)}`, {
				method: 'POST',
				headers: {
					'Authorization': `Bearer ${authToken.value}`,
					'accept': 'application/json',
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({chanPass: `${this.password}`})
			});
			return response.status;
		} catch (error) {
			// console.error(error);
			return 0;
		}
	}

	async chgtPass(): Promise<number> {
		try {
			const response =  await fetch(`${hostname.value}/chat/psswd/%23${this.name.slice(1)}/${this.password}`, {
				method: 'POST',
				headers: {
					'Authorization': `Bearer ${authToken.value}`,
					'accept': 'application/json',
				},
			});
			this.reset();
			this.updateChanList();
			return response.status;
		} catch (error) {
			// console.error(error);
			return 0;
		}
	}

	async chgtStatus(): Promise<number> {
		if (this.status === 'locked') {
			if (this.password !== '') {
				return this.chgtPass();
			}
			return 0;
		}
		try {
			const response =  await fetch(`${hostname.value}/chat/status/%23${this.name.slice(1)}/${this.status}`, {
				method: 'POST',
				headers: {
					'Authorization': `Bearer ${authToken.value}`,
					'accept': 'application/json',
				},
			});
			this.reset();
			this.updateChanList();
			return response.status;
		} catch (error) {
			// console.error(error);
			return 0;
		}
	}

	async getChanList(): Promise<IChan[]> {
		const requestOption = {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${authToken.value}`,
				'accept': 'application/json',
			},
		}
		return fetch(`${hostname.value}/chat/chan-list`, requestOption)
			.then(response => response.json())
			.then(data => {
				return data;
			})
			.catch(error => {
				// console.error(error);
			});
	}
	
	async getPvList(): Promise<string[]> {
		const requestOption = {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${authToken.value}`,
				'accept': 'application/json',
			},
		}
		return fetch(`${hostname.value}/chat/chatter-list`, requestOption)
			.then(response => response.json())
			.then(data => {
				return data;
			})
			.catch(error => {
				// console.error(error);
			});
	}

	async getChanIn(): Promise<string[]> {
		const requestOption = {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${authToken.value}`,
				'accept': 'application/json',
			},
		}
		return fetch(`${hostname.value}/chat/chan-in`, requestOption)
			.then(response => response.json())
			.then(data => {
				return data;
			})
			.catch(error => {
				// console.error(error);
			});
	}

	async mode(mode: string) {
		if (mode === 'creation') {
			this.creating = true;
			this.selecting = false;
			this.askPass = false;
		}
		else if (mode === 'selection') {
			this.creating = false;
			this.selecting = true;
			this.askPass = false;
		}
		else if (mode === 'login') {
			this.creating = false;
			this.selecting = false;
			this.askPass = true;
		}
		else {
			this.creating = false;
			this.selecting = false;
			this.askPass = false;
		}
	}
}
