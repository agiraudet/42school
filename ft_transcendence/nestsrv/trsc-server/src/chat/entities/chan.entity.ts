export class Chan {
    name: string;
    owner: string;
    admins: string[];
    invited: string[];
    banned: string[];
    muted: Record<string, number>;
    members: string[];
    status: string;
    password: string;

    constructor(chanName: string, chanStatus: string, chanOwner: string, chanPassword: string) {
        this.name = chanName;
        this.owner = chanOwner;
        this.admins = [];
        this.invited = [];
        this.banned = [];
        this.muted = {};
        this.members = [];
        this.status = chanStatus;
        this.password = chanPassword;
    }
}
