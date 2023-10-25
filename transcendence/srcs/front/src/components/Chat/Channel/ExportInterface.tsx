export interface User {
	id: number;
	nickname: string;
}

export interface Channel {
	createdAt: Date;
	members: User[];
	id: number;
	name: string;
	privacy: string;
	isMP: boolean;
	muteList: number[];
	banlist: number[];
	channelOwnerId : number;
	adminId: number[];
	admin: {
	id: number;
	}[]
	messages: {
	createdAt: Date;
	id: number;
	}[];
}

export interface ChanelBarProps { channels: Channel[], selectedChannelId: number, isChannelClicked: boolean}