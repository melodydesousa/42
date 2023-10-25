import {ConnectedSocket, MessageBody, SubscribeMessage, WebSocketGateway, WebSocketServer} from "@nestjs/websockets";
import {MessagesService} from "./messages.service";
import {Server, Socket} from "socket.io";
import {CreateMessageDto} from "./dto/create-message.dto";
import {FullMessage, Message} from "./entities/message.entity";

@WebSocketGateway({
	serveClient: false,
	cors: {
		origin: "http://reactjs:3000",
		credentials: true,
	},
	path: "/messages",
})
export class MessagesGateway {
	@WebSocketServer()
	server: Server;
	constructor(private readonly messagesService: MessagesService) {}
	handleConnection(client: Socket) {
		// console.log("Chat client connected:", client.id);
	}
	handleDisconnect(client: Socket) {
		const id = this.messagesService.getClientByName(client.id)
		// console.log("Chat client disconnected:", client.id);
		this.messagesService.disconnect(client);
		this.server.emit("hasleft", {id: id})
	}


	@SubscribeMessage("allUsers")
	async allUsers(@ConnectedSocket() client: Socket) {
		return await this.messagesService.getAllUsers()
	}

	@SubscribeMessage("friends")
	async friends(@MessageBody('id') id: number,
				@ConnectedSocket() client: Socket) {
		return await this.messagesService.getFriends(id)
	}

	@SubscribeMessage("UpFriendsList")
	async UpFriendsList(@MessageBody('id') id: number)
	{
		if (id)
		{

			const friends = await this.messagesService.getFriends(id);
			let tmp = [];
			for (let i:number = 0; i < friends.length; i++)
			{
				tmp.push(friends[i]);
			}
			this.server.emit('RefreshFriendsList', tmp);
		}
		if (!id)
		{
			this.server.emit('RefreshFriendsList');
		}
	}

	@SubscribeMessage("identify")
	identify(
		@MessageBody("id") id: number,
		@ConnectedSocket() client: Socket) {
		try {
			//console.log(id)
			this.messagesService.identify(id, client);
			this.server.emit("IamOnline", {id: id, client: client.id})
			return "success"
		} catch (error) {
			console.error(error.message);
		}
	}

	@SubscribeMessage("kick")
	async kick (
		@MessageBody('id_to_kick') to_kick: number,
		@MessageBody('from') from: string,
		@MessageBody('is_admin') is_admin: boolean,
		@MessageBody ('is_owner') is_owner: boolean) {
		if (!is_admin && !is_owner)
			return ({success: false, message: "Not an admin"})
		const user_to_k = await this.messagesService.getUserToBK(to_kick, from)
		const message = await this.messagesService.kick(is_owner, user_to_k, user_to_k.nickname, from)
		if (message.success === true) {
			const SoIds = this.messagesService.getAllClients(user_to_k.id)
			const allConnectedSockets = this.server.sockets.sockets;
			for (let value in SoIds) {
				this.server.to(SoIds[value]).emit("mustclose", `chat close request`);
				allConnectedSockets.get(SoIds[value]).leave(from)
			}
		}
		return ({...message, kicked: `${to_kick}`})
	}

	@SubscribeMessage("mute")
	async mute (
	@MessageBody('id_to_mute') to_mute: number,
	@MessageBody('muted_from') from: string,
	@MessageBody('is_admin') is_admin: boolean,
	@MessageBody ('is_owner') is_owner: boolean) {
		if (!is_admin && !is_owner)
			return ({success: false, message: "You are not admin"})
		const user_to_m = await this.messagesService.getUserToBK(to_mute, from)
		const message = await this.messagesService.mute(is_owner, user_to_m, to_mute, from)
			return (message)
	}

	@SubscribeMessage("ban")
	async ban (
		@MessageBody('id_to_ban') to_ban: number,
		@MessageBody('from') from: string,
		@MessageBody('is_admin') is_admin: boolean,
		@MessageBody ('is_owner') is_owner: boolean) {
		if (!is_admin && !is_owner)
			return ({success: false, message: "Not an admin"})
		const user_to_ban = await this.messagesService.getUserToBK(to_ban, from)
		const message = await this.messagesService.ban(is_owner, user_to_ban, user_to_ban.nickname, from)
		if (message.success === true) {
			const SoIds = this.messagesService.getAllClients(user_to_ban.id)
			const allConnectedSockets = this.server.sockets.sockets;
			for (let value in SoIds) {
				this.server.to(SoIds[value]).emit("mustclose", `chat close request`);
				allConnectedSockets.get(SoIds[value]).leave(from)
			}
		}
		return ({...message, banned: `${to_ban}`})
	}

	@SubscribeMessage("check_ban")
	check_ban (
		@MessageBody('id') id: number,
		@MessageBody('from') from: string) {
		return this.messagesService.isBanned(id, from)
	}

	@SubscribeMessage("createMessage")
	async create(
		@MessageBody("dto") createMessageDto: CreateMessageDto,
		@MessageBody('sender') sender: string,
		@ConnectedSocket() client: Socket,
		@MessageBody("channel") channel: string) {
		const senderId: number = this.messagesService.getClientByName(client.id)
		const ban = this.messagesService.isBanned(senderId, channel)
		const mute = this.messagesService.isMuted(senderId, channel)
		const kicked = this.messagesService.isKicked(senderId, channel)
		if (!ban && !mute && !kicked) {
			const message: FullMessage = await this.messagesService.create(channel,
				createMessageDto, sender, senderId);
			this.server.to(channel).emit("message", message);
			return "sent";
		}
		else if (!ban && !kicked) {
			return `You were muted on ${channel}`
		}
		else if (!ban)
			return `You were kicked from ${channel}`
		else {
			return `You were banned from ${channel}`
		}
	}

	@SubscribeMessage("findAllMessages")
	findAll(@MessageBody("channel") channel: string,
			@MessageBody("channelId") channelId: number) {
		return this.messagesService.findAll(channel, channelId);
	}

	@SubscribeMessage("join")
	async joiner(
		@ConnectedSocket() client: Socket,
		@MessageBody("channel") channel?: string) {
		const roomName: string[] = await this.messagesService.joiner(client, channel);
		if (roomName.length) {
			const id = this.messagesService.getClientByName(client.id)
			const SoIds = this.messagesService.getAllClients(id)
			const allConnectedSockets = this.server.sockets.sockets;
			for (let value in SoIds) {
				if (SoIds[value] != client.id)
					allConnectedSockets.get(SoIds[value]).join(roomName)
			}
			this.server.to(roomName).emit("joinNotification", `A new user has joined the channel(s): ${roomName}`);
			return true;
		} else {
			//this.server.emit("joinNotification", `No channel joined`);
			return true;
		}
	}

	@SubscribeMessage("invite")
	async invite (
		@ConnectedSocket() client: Socket,
		@MessageBody('id') id: number,
		@MessageBody('toast') toast: boolean,
		@MessageBody('channelId') channelId: number,
		@MessageBody('channel') channel: string) {
		if (this.messagesService.getClientByName(client.id)) {
			console.log("PARAM: ", id, toast, channelId, channel)
			const success = await this.messagesService.joinOnInvite(id, channel)
			console.log("SUCCES?", success)
			if (success === channel) {
				const SoIds = this.messagesService.getAllClients(id)
				console.log("SoId: ", SoIds)
				const allConnectedSockets = this.server.sockets.sockets;
				for (let value in SoIds) {
				{
						allConnectedSockets.get(SoIds[value]).join(channel)
						this.server.to(SoIds[value]).emit("joinNotification", `You have accepted invitation`);
				}
				}
				if (toast === true)
				{
					this.messagesService.addToRedirect(id, channelId);
					client.emit('NavigateRoom')
					client.emit('AlreadyOnChat');
				}
				//this.server.to(SoIds[value]).emit("NavigateRoom");
				return {success: true, message: "user invited"}
			}
			if (success === "banned") {
				return {success: false, message: "This user was banned from here"}
			}
			if (success === 'ismember')
			{
				this.messagesService.addToRedirect(id, channelId);
				client.emit('NavigateRoom')
				client.emit('AlreadyOnChat');
			}
		}
	}

	@SubscribeMessage("leave")
	async leaver(
		@ConnectedSocket() client: Socket,
		@MessageBody("channel") channel: string,
		@MessageBody ('is_owner') is_owner: boolean) {
		const message = await this.messagesService.leaver(client, channel)
		console.log(message);
		if (message.success === true) {
			const SoIds = this.messagesService.getAllClients(this.messagesService.getClientByName(client.id))
			const allConnectedSockets = this.server.sockets.sockets;
			for (let value in SoIds) {
				allConnectedSockets.get(SoIds[value]).leave(channel)
			}
		}
		if (message.new_admin !== false)
		{
			const SoIds = this.messagesService.getAllClients(message.new_admin as number);
			for (let value in SoIds) {
				this.server.to(SoIds[value]).emit("adminevent", `you are admin`);
			}
		}
		return message
	}

	@SubscribeMessage("admin")
	async adminer(
		@ConnectedSocket() client: Socket,
		@MessageBody("from") from: string,
		@MessageBody("id_to_admin") id_to_admin: number,
		@MessageBody('is_admin') is_admin: boolean,
		@MessageBody ('is_owner') is_owner: boolean) {
		if (!is_admin && !is_owner)
			return ({success: false, message: "Not an admin"})
		const user_to_admin = await this.messagesService.getUserToBK(id_to_admin, from)
		const message = await this.messagesService.adminer(is_owner, user_to_admin, user_to_admin.nickname, from)
		const SoIds = this.messagesService.getAllClients(id_to_admin)
		for (let value in SoIds) {
			this.server.to(SoIds[value]).emit("adminevent", `you are admin`);
		}
		return message
	}

	@SubscribeMessage("online")
	online(@MessageBody('id') id: number[],
	       @ConnectedSocket() client: Socket) {
		return this.messagesService.online(client, id)
	}

	@SubscribeMessage("channelMember")
	channelMember(@MessageBody('channel') channel: string)
	{
		return this.messagesService.getChannelUser(channel);
	}

	@SubscribeMessage("Redirect")
	async Redirect(@ConnectedSocket() client: Socket)
	{
		const value = this.messagesService.Invite.get(this.messagesService.getClientByName(client.id));
		if (value)
		{
			this.messagesService.Invite.delete(this.messagesService.getClientByName(client.id))
			return  ({state:true, channelId:value, channel: await this.messagesService.getAllChannel()});
		}
	}


	@SubscribeMessage("CreateChannel")
	async CreateChannel()
	{
		this.server.emit('RefreshChannelList', await this.messagesService.getAllChannel());
	}

	@SubscribeMessage("channelList")
	async channelList()
	{
		return await this.messagesService.getAllChannel();
	}
/////MEMBER LISTE

@SubscribeMessage("UpMemberList")
async UpMemberList(@MessageBody('id') id: number)
{

		const members = await this.messagesService.getAllMembers(id);
		let tmp = [];
		for (let i:number = 0; i < members.members.length; i++)
		{
			tmp.push(members.members[i]);
		}
		this.server.emit('RefreshMemberList', tmp);

}

@SubscribeMessage("memberList")
async memberList(@MessageBody('id') id: number)
{
	const members = await this.messagesService.getAllMembers(id);
	let tmp = [];
	for (let i:number = 0; i < members.members.length; i++)
	{
		tmp.push(members.members[i]);
	}

	return tmp;
}

////////////////////////////////////

@SubscribeMessage("verifyPassword")
verify(@MessageBody('mdp') mdp: string, @MessageBody('room') id: number)
{
	return this.messagesService.verify(mdp, id);
}

	@SubscribeMessage("typing")
	async typing(
		@MessageBody("isTyping") isTyping: boolean,
		@MessageBody("data") data: {nickname: string, channel: string},
		@ConnectedSocket() client: Socket) {
		client.broadcast.to(data.channel).emit("typing", data);
	}


	@SubscribeMessage("inviteRoom")
	inviteRoom(
		@MessageBody('data') data: number,
		@MessageBody('channel') channel: string,
		@MessageBody('channelId') channelId: number,
		@ConnectedSocket() client: Socket) :any
	{
		const SoIds = this.messagesService.getAllClients(data)
		if (SoIds)
		{
			for (let value in SoIds) {
				if (SoIds[value] != client.id)
				{
    				this.server.to(SoIds[value]).emit('AcceptInviteRoom', {channel :channel, id: data, channelId: channelId});
				}
			}
  		}
	}
}



