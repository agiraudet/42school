interface ITabMsgItem { id: string, from: string, body: string};

export default class ChatTabs {
    tabs: string[];
    tabCur: number;
    tabMsg: {[name: string]: ITabMsgItem[] };
	notif: string[];
	globalNotif: boolean;

	constructor() {
		this.tabs = [];
		this.tabCur = -1;
		this.tabMsg = {};
		this.notif = [];
		this.globalNotif = false;
	}

	switchTab(index: number) {
		this.tabCur = index;
		const i = this.notif.indexOf(this.tabs[this.tabCur]);
		if (i > -1) {
			this.notif.splice(i, 1);
		}
	}

	addNotif(conv: string) {
		if (this.tabs[this.tabCur] !== conv) {
			this.notif.push(conv);
		}
	}

	addConv(tabName: string) {
		if (!this.tabs.includes(tabName)) {
			this.tabs.push(tabName);
		}
		if (this.tabMsg[tabName] === undefined) {
			this.tabMsg[tabName] = [];
		}
	}

	updateConvList(convList: string[]) {
		this.tabs = convList;
		for (const name in this.tabMsg) {
			if (!this.tabs.includes(name)) {
				delete this.tabMsg[name];
			}
		}
	}

	getMsgList() {
		return this.tabMsg[this.tabs[this.tabCur]];
	}

	getMsgTarget() {
		return this.tabs[this.tabCur];
	}
}