import {ForbiddenException, Injectable} from "@nestjs/common";
import {PrismaService} from "../prisma/prisma.service";
import { gamestate, Player } from "./class/gamestate";
import { StateHandlerContext } from "pactum/src/exports/handler";
import { Games, User } from "@prisma/client";

export interface PlayerInfo{
	mail: string,
	nickname: string,
	id: number,
	socket: string,
}

@Injectable()
export class GameService {
	constructor(private _prisma: PrismaService) {}



	state = new Map<string, gamestate>();
	user = new Map();
	LobbyNormal = new Map();
	LobbyQuadri = new Map();
	InvitLobby = new Map();

	GetIdBySocket(socket: string)
		{
			for (let [key, value] of this.user)
			{
				if (socket === key)
				{
					return value.id;
				}
			}
		}



	destroyRoom(room:string)
	{
		this.state.delete(room);
	}

	async CreatePrismaGame(_userId: number, _opponent:string, _outcome:string, _score:string) {
		const _game: Games = await this._prisma.games.create({
				data: {
					opponent: _opponent,
					outcome : _outcome,
					score: _score,
					user: {
						connect: {
							id: _userId
						}
					}
				}
			});


		}


		async UpdatePrismaAchievement(userId:number, achievement:string)
		{
			const user:User = await this._prisma.user.findUnique({
			where: {
				id: userId,
			},})
			const result = user.achievement.filter(word => word === achievement)
			if (result.length === 0)
			{
				user.achievement.push(achievement);
				await this._prisma.user.update({
				where: {
					id: userId,
				},
				data: {
					achievement: user.achievement,
				}
			});
			}
		}

		async AchievementManagment(player:Player, opposant:Player, mode:string)
		{
			let achievement:string = '';

			if (player.forfait)
			{
				achievement = 'coward';
				await this.UpdatePrismaAchievement(player.id, achievement);
			}
			if (opposant.forfait)
			{
				achievement = 'easy';
				await this.UpdatePrismaAchievement(player.id, achievement);
			}
			if (player.result === 'win' && mode === 'QuadriMode')
			{
				achievement = 'Quadricolor';
				await this.UpdatePrismaAchievement(player.id, achievement);
			}
			if (player.result === 'win')
			{
				achievement = 'winner';
				await this.UpdatePrismaAchievement(player.id, achievement);
			}
			if (player.score === 12 && opposant.score === 0)
			{
				achievement = 'fanny';
				await this.UpdatePrismaAchievement(player.id, achievement);
			}
		}



	async UpdatePrismaUser(_userId: number, state:boolean)
	{
		const user:User = await this._prisma.user.findUnique({
			where: {
				id: _userId,
			},})
		let won:number;
		let lost:number;
		let xp:number;
		if (state)
		{
			won = user.won + 1
			lost = user.lost
			xp = user.xp + 100;
		}
		else
		{
			won = user.won
			lost = user.lost + 1
			xp = user.xp + 20;
		}
		await this._prisma.user.update({
				where: {
					id: _userId,
				},
				data: {
					won: won,
					lost: lost,
					xp: xp,
				}
			});
			}


	async endGame(room:string): Promise<boolean>
	{

		const stateCurrent = this.state.get(room);


		const score = stateCurrent.player1.score.toString() + " | " + stateCurrent.player2.score.toString();

		if (stateCurrent.player1.result === 'win')
		{
			if (stateCurrent.player2.forfait)
			{
				this.CreatePrismaGame(stateCurrent.player1.id, stateCurrent.player2.nickname,"won" ,"won by forfeit")
				this.CreatePrismaGame(stateCurrent.player2.id, stateCurrent.player1.nickname, "lost","lost by forfeit")
			}
			else
			{
				this.CreatePrismaGame(stateCurrent.player1.id, stateCurrent.player2.nickname,"won", score)
				this.CreatePrismaGame(stateCurrent.player2.id, stateCurrent.player1.nickname,"lost", score)
			}
			this.UpdatePrismaUser(stateCurrent.player1.id, true);
			this.UpdatePrismaUser(stateCurrent.player2.id, false);
		}
		if (stateCurrent.player2.result === 'win')
		{
			if (stateCurrent.player1.forfait)
			{
				this.CreatePrismaGame(stateCurrent.player2.id, stateCurrent.player1.nickname,"won" ,"won by forfeit")
				this.CreatePrismaGame(stateCurrent.player1.id, stateCurrent.player2.nickname, "lost","lost by forfeit")
			}
			else
			{
				this.CreatePrismaGame(stateCurrent.player2.id, stateCurrent.player1.nickname,"won", score)
				this.CreatePrismaGame(stateCurrent.player1.id, stateCurrent.player2.nickname,"lost", score)
			}
			this.UpdatePrismaUser(stateCurrent.player2.id, true);
			this.UpdatePrismaUser(stateCurrent.player1.id, false);
		}
		await this.AchievementManagment(stateCurrent.player1, stateCurrent.player2, stateCurrent.mode);
		await this.AchievementManagment(stateCurrent.player2, stateCurrent.player1, stateCurrent.mode);


		this.destroyRoom(room);
		return true;
	}

	AllSocket(id:number)
	{
		const socket = new Array();
		for (let [key, value] of this.user)
		{
			if (id === value.id)
			{
				socket.push(key);
			}
		}
		return (socket);
	}

	IsinQueue(Lobby:Map<any, any>, id:number)
	{
		for (let [key, value] of Lobby)
		{
			if (id === value.id)
				return true;
		}
		return false;
	}

	startGame(Lobby:Map<any, any>, mode:string)
	{
		const iterator1 = Lobby.values();

		const Player1 = iterator1.next().value;
		const Player2 = iterator1.next().value;
		const NewState = new gamestate()

		NewState.player1.email = Player1.mail;
		NewState.player1.nickname = Player1.nickname;
		NewState.player1.socket = Player1.socket;

		NewState.player1.id = Player1.id;
		NewState.player2.id = Player2.id;

		NewState.player2.email = Player2.mail;
		NewState.player2.nickname = Player2.nickname;
		NewState.player2.socket = Player2.socket;
		NewState.mode = mode;

		NewState.room = Player1.socket + Player2.socket
		Lobby.clear();
		this.state.set(Player1.socket + Player2.socket, NewState);
		return ({P1: Player1.socket, P2:Player2.socket, room: NewState.room})
	}

	AllInGame()
	{
		const state = this.state;
		const AllClientInGame = new Array;
		for (let [key, value] of state)
		{
			AllClientInGame.push(value.player1.id);
			AllClientInGame.push(value.player2.id);
		}
		return AllClientInGame;
	}


	isInGame(id:number)
	{
		const state = this.state;

		for (let [key, value] of state)
		{
			if (id === value.player1.id)
				return ({Player:1, socket:value.player1.socket, room: value.room});
			if (id === value.player2.id)
				return ({Player:2, socket:value.player2.socket, room: value.room});
		}
		return false;
	}
}
