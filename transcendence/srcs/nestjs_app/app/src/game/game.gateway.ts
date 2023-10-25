import { MessageBody, SubscribeMessage, WebSocketGateway,  WebSocketServer, ConnectedSocket} from "@nestjs/websockets";
import {  gamestate, Player } from "./class/gamestate";
import { Server, Socket } from "socket.io";
import { Injectable, Logger } from "@nestjs/common";
import { clearInterval } from "timers";
import { _GetUser } from "src/auth/decorator";
import { PrismaService } from "src/prisma/prisma.service";
import { Games, User } from "@prisma/client";
import { GameService } from "./game.service";
import { PlayerInfo } from "./game.service";


@WebSocketGateway(
	{
		serveClient: false,
		cors: {
			origin: `http://reactjs:3000`,
			credentials: true
		},
		path: "/game",
	})
	@Injectable()
	export class GameGateway{
		constructor(private _prisma: PrismaService, private GameService: GameService) {
		}


		@WebSocketServer()
		server: Server;


		updateGamestate(room:string)
		{
			const stateCurrent = this.GameService.state.get(room);
			const interval = setInterval(() =>
			{
				if (stateCurrent)
				{
					stateCurrent.update();
					if (stateCurrent.player1.forfait)
					{
						stateCurrent.player2.result = "win";
						stateCurrent.end = true;
					}
					else if (stateCurrent.player2.forfait)
					{
						stateCurrent.player1.result = "win";
						stateCurrent.end = true;
					}
					this.server.to(stateCurrent.room).emit("gameState", stateCurrent.getData());
					if (stateCurrent.end === true)
					{
						clearInterval(interval);
						this.server.socketsLeave(stateCurrent.room)
						//this.server.in(room.toString()).disconnectSockets(true);
						const promise1 = new Promise((resolve, reject) =>{
							resolve(this.GameService.endGame(room));
						})
						promise1.then((value) =>
						{
							this.server.emit('IsinGame', this.GameService.AllInGame());
						})
						//this.GameService.endGame(room) =;
					}
				}
			}, 20);
		}


	createGame(Lobby:Map<any, any>, mode:string)
	{
		const game = this.GameService.startGame(Lobby, mode);
		this.server.in(game.P1).socketsJoin(game.room);
		this.server.in(game.P2).socketsJoin(game.room);
		this.server.to(game.room).emit("start-game");
		this.server.emit('IsinGame', this.GameService.AllInGame());
		this.updateGamestate(game.room);
	}

	@SubscribeMessage("addToLobby")
	addToLobby(@MessageBody() args: string,
	@ConnectedSocket() client: Socket)
	{
		if (this.GameService.isInGame(client.data.id) != false)
		{
			client.emit('AlreadyInGame');
			return false;
		}

		const LobbyNormal = this.GameService.LobbyNormal;
		const LobbyQuadri = this.GameService.LobbyQuadri;
		const user = this.GameService.user;
		if (user.has(client.id))
		{
			if(this.GameService.IsinQueue(LobbyNormal, client.data.id))
				LobbyNormal.clear();
			if(this.GameService.IsinQueue(LobbyQuadri, client.data.id))
				LobbyQuadri.clear();
			if (args === 'normal')
				LobbyNormal.set(client.id ,user.get(client.id));
			if (args === 'quadri')
				LobbyQuadri.set(client.id ,user.get(client.id));


			if (LobbyNormal.size === 2)
				this.createGame(LobbyNormal, 'NormalMode');
			if (LobbyQuadri.size === 2)
				this.createGame(LobbyQuadri, 'QuadriMode');
		}
		return true;
	}

	@SubscribeMessage("handleAuth")
	handleAuth(client: Socket, args:any) :any
	{
		if (args.id)
		{
			const userInfo: PlayerInfo = {
				mail: args.mail,
				nickname: args.nick,
				id: args.id,
				socket: client.id,
			}
			//console.log('Game authentified', userInfo);
			client.data.email = args.mail;
			client.data.id = args.id;
			client.data.nickname = args.nick;
			this.GameService.user.set(client.id, userInfo);
		}

	}

	async handleConnection(client:Socket, args:any )
	{
		// console.log("Game connected : ", client.id);
	}

	async handleDisconnect(client:Socket)
	{
		const state = this.GameService.state;

		// console.log("Game disconnected : ", client.id);
		this.GameService.user.delete(client.id);
		this.GameService.LobbyNormal.delete(client.id);
		this.GameService.LobbyQuadri.delete(client.id);
		if (client.data.id)
		{
			const res = this.GameService.isInGame(client.data.id);
			if (res && !state.get(res.room).end)
			{
				if (res.Player === 1 && res.socket === client.id)
					state.get(res.room).player1.forfait = true;
				if (res.Player === 2 && res.socket === client.id)
					state.get(res.room).player2.forfait = true;
			}
		}

	}


	@SubscribeMessage("move_up")
	move_up(client: Socket) :any
	{
		const state = this.GameService.state;
		if (client.data.id)
		{
			const res = this.GameService.isInGame(client.data.id);
			if (res && res.Player === 1)
				state.get(res.room).movePlayerOneUp();
			if (res && res.Player === 2)
				state.get(res.room).movePlayerTwoUp();
		}
	}

	@SubscribeMessage("move_down")
	move_down(client: Socket ): any
	{
		const state = this.GameService.state;
		if (client.data.id)
		{
			const res = this.GameService.isInGame(client.data.id);
			if (res && res.Player === 1)
				state.get(res.room).movePlayerOneDown();
			if (res && res.Player === 2)
				state.get(res.room).movePlayerTwoDown();
		}
	}

	@SubscribeMessage("stop_up")
	stop_up(client: Socket ): any
	{
		const state = this.GameService.state;
		if (client.data.id)
		{
			const res = this.GameService.isInGame(client.data.id);
			if (res && res.Player === 1)
				state.get(res.room).stopMovePlayerOneUp();
			if (res && res.Player === 2)
				state.get(res.room).stopMovePlayerTwoUp();
		}

	}

	@SubscribeMessage("stop_down")
	stop_down(client: Socket ): any
	{
		const state = this.GameService.state;
		if (client.data.id)
		{
			const res = this.GameService.isInGame(client.data.id);
			if (res && res.Player === 1)
				state.get(res.room).stopMovePlayerOneDown();
			if (res && res.Player === 2)
				state.get(res.room).stopMovePlayerTwoDown();
		}
	}


	@SubscribeMessage("surrender")
	surrender(client: Socket) :any
	{
		const state = this.GameService.state;
		if (client.data.id)
		{
			const res = this.GameService.isInGame(client.data.id);
			if (res)
			{
				if (res && res.Player === 1 && !state.get(res.room).end && res.socket === client.id)
					state.get(res.room).player1.forfait = true;
				if (res && res.Player === 2 && !state.get(res.room).end && res.socket === client.id)
					state.get(res.room).player2.forfait = true;
			}
		}
	}

	@SubscribeMessage("inviteGame")
	inviteGame(
		@MessageBody('data') data: number,
		@MessageBody('mode') mode: string,
		@ConnectedSocket() client: Socket) :any
	{
		if (this.GameService.isInGame(client.data.id) != false || this.GameService.isInGame(data) != false)
		{
			client.emit('AlreadyInGame');
			return;
		}
			if (this.GameService.IsinQueue(this.GameService.LobbyNormal,data ) || this.GameService.IsinQueue(this.GameService.LobbyNormal,client.data.id ))
				this.GameService.LobbyNormal.clear();
			if (this.GameService.IsinQueue(this.GameService.LobbyQuadri,data ) || this.GameService.IsinQueue(this.GameService.LobbyQuadri,client.data.id ))
				this.GameService.LobbyQuadri.clear();
			const sock = this.GameService.AllSocket(data)
			sock.forEach(element => this.server.to(element).emit('sendGameInvitation', {friend: client.id, mode: mode}));

	}



	@SubscribeMessage("InGameOrNot")
	InGameOrNot(
		@ConnectedSocket() client: Socket) :any
	{
		return (this.GameService.AllInGame());
	}

	@SubscribeMessage("acceptGameInvitation")
	acceptGameInvitation(
		@MessageBody('friend') friend: string,
		@MessageBody('mode') mode: string,
		@ConnectedSocket() client: Socket) :any
	{
		const IdFriend = this.GameService.GetIdBySocket(friend);
		if (!this.GameService.user.has(client.id) || !this.GameService.user.has(friend))
		{
			client.emit('OpponentHasLeft');
			return;
		}

		if (this.GameService.isInGame(client.data.id) != false || this.GameService.isInGame(IdFriend) != false)
		{
			client.emit('AlreadyInGame');
			return;
		}
		if (this.GameService.IsinQueue(this.GameService.LobbyNormal, IdFriend ) || this.GameService.IsinQueue(this.GameService.LobbyNormal,client.data.id ))
			this.GameService.LobbyNormal.clear();
		if (this.GameService.IsinQueue(this.GameService.LobbyQuadri,IdFriend ) || this.GameService.IsinQueue(this.GameService.LobbyQuadri,client.data.id ))
			this.GameService.LobbyQuadri.clear();
		this.GameService.InvitLobby.set(client.id, this.GameService.user.get(client.id));
		this.GameService.InvitLobby.set(friend, this.GameService.user.get(friend));
		this.createGame(this.GameService.InvitLobby, mode)
	}
}
