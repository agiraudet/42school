import { authToken, hostname } from "@/globalProperties";

interface ILadder {name: string, points: number}

export class LadderClass {
    ladder: ILadder[];

    constructor() {
        this.ladder = [];
    }
    
    async getLadder() {
        const requestOption = {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${authToken.value}`,
                'accept': 'application/json',
            }
        }
        return fetch(`${hostname.value}/game/ladder`, requestOption)
            .then(response => response.json())
            .then(data => this.ladder = data)
            .catch(error => { 
                //console.error(error);
            });
    }
}