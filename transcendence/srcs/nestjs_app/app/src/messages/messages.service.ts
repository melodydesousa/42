import {ForbiddenException, Injectable} from "@nestjs/common";
import {FullMessage} from "./entities/message.entity";
import {CreateMessageDto} from "./dto/create-message.dto";
import {PrismaService} from "../prisma/prisma.service";
import {Socket} from "socket.io";
import * as _argon from "argon2";

@Injectable()
export class MessagesService {
	constructor(private _prisma: PrismaService) {}
	clientToUser: Map<string, number> = new Map<string, number>();
	muteList: Map<number, string[]> = new Map<number, string[]>();
	banList: Map<number, string[]> = new Map<number, string[]>();
	kickList: Map<number, string[]> = new Map<number, string[]>();
	Invite: Map<number, number> = new Map<number, number>();

	identify(id: number, client: Socket) {
		if (!id)
			throw new Error("No userId, user not identified");
		if (Array.from(this.clientToUser.values()).includes(id)) {
			console.log("Duplicate user:", id);
		}
		this.clientToUser.set(client.id, id);
		// console.log(this.clientToUser);
	}

	async getFriends(id: number) {
		const Friends = await this._prisma.friends.findMany({
			where: {
				userId: id,
			},
		});
		const friendsListPromised = Friends.map(async (friend) => {
			const user = await this._prisma.user.findUnique({
				where: {
					id: friend.friendId,
				},
				select: {
					nickname: true,
					id: true,
					email: true,
					avatar: true,
				}
			})
			return user;
		});
		const friendsList = await Promise.all(friendsListPromised);
		return friendsList;
	}

	async getAllUsers() {
	const allUsers = await this._prisma.user.findMany({
		select: {
			id: true,
			nickname: true,
			xp: true,
			email: true,
			games:
			{
				select: {
					createdAt: true,
					id: true,
				}
			},
			friends: {
				select: {
					user: {
						select: {
							nickname: true,
							avatar: true,
							isonline: true,
							email: true,
						}
					}
			}},
			adminOf: {
				select: {
					id: true,
					name: true,
					createdAt: true,
					privacy: true,
					messages: {
						select: {
							id: true,
							createdAt: true,
							content: true,
						}
					}
				}
			},
			isonline: true,
			won: true,
			lost: true,
			achievement: true,
			avatar: true

		}});
	return allUsers
  }

	async joiner(client: Socket, channel: string | undefined): Promise<string[]> {
		const id = this.clientToUser.get(client.id)
		let roomNames: string[] = []
		let muted_from: string[] = []
		let banned_from: string[] = []
		if (!id)
			return [];
		this.kickList.delete(id)
		if (!channel) {
			const to_join = await this._prisma.user.findUnique({
				where: {
					id: this.clientToUser.get(client.id),
				},
				select: {
					chatmember: {
						select: {
							id: true,
							createdAt: true,
							updateAt: true,
							name: true,
							channelOwnerId: true,
							muteList: true,
							banlist: true
						},
					},
				},
			});
			if (to_join) {
				for (let value of to_join.chatmember) {
					if (!value.banlist.includes(id))
						roomNames.push(value.name)
					else
						banned_from.push(value.name)
					if(value.muteList.includes(id))
						muted_from.push(value.name)
				}
				if (roomNames.length)
					client.join(roomNames)
				if (muted_from.length) {
					this.muteList.delete(id)
					this.muteList.set(id, muted_from)
				}
				if (banned_from.length) {
					this.banList.delete(id)
					this.banList.set(id, banned_from)
				}
			}
			return roomNames;
		}
		else {
			if (this.isBanned(id, channel))
				return []
			const isMember = await this._prisma.chat.findFirst({
				where: {
					name: channel,
					members: {
						some: {
							id: id,
						},
					},
				},
			});
			if (isMember) {
				client.join(channel);
				return [];
			}
			await this._prisma.chat.update({
				where: {
					name: channel
				},
				data: {
					members: {
						connect: [{id: this.clientToUser.get(client.id)}]
					}
				},
			});
			client.join(channel);
			return [channel];
		}
	}

	async joinOnInvite (id: number, channel: string) {
		if (this.isBanned(id, channel))
			return "banned"
		const isMember = await this._prisma.chat.findFirst({
			where: {
				name: channel,
				members: {
					some: {
						id: id,
					},
				},
			},
		});
		if (isMember) {
			return "ismember";
		}
		await this._prisma.chat.update({
			where: {
				name: channel
			},
			data: {
				members: {
					connect: [{id: id}]
				}
			},
		});
		return channel
	}

	async leaver(client: Socket, channel: string) {
		const _id = this.clientToUser.get(client.id);
		let new_admin:number|boolean = false;
		const _chat = await this._prisma.chat.findUnique({
			where: {
				name: channel
			},
			select: {
				members: {
					select: {
						id: true,
					}},
				adminId: true,
				channelOwnerId: true,
			}
		})
		if (!_chat.members.find((members) => members.id === _id))
		{
			return {success: false, new_admin: false, message: "You are not a channel's member"};
		}
		else if (this.isBanned(_id, channel))
		{
			return {success: false, new_admin: false, message: "You are ban mother *******"};
		}
		if (_chat && _chat.members.length === 1)
		{
			return {success: false, new_admin: false, message: "You can't leave because you are the only member left"};
		}
		else if (_chat.members.length > 1 && !_chat.adminId.includes(_id) && _chat.channelOwnerId !== _id)
        {
            await this._prisma.chat.update({
                where: {
                    name: channel
                },
                data: {
                    members: {
                        disconnect: [{id: this.clientToUser.get(client.id)}]
                    }
                },
            });
            return {success: true, new_admin: new_admin,message: `You left ${channel}`}
        }
		if (_chat.channelOwnerId === _id)
		{
		//- si plusieurs adminId :  admin[index + 1] devient channel owner
		if (_chat && _chat.adminId.length > 1) {
			await this._prisma.chat.update({
				where: {
					name: channel
				},
				data: {
					channelOwnerId : _chat.adminId[1]
				},
			});
		}
		else if (_chat && _chat.members.length > 1) {
			await this._prisma.chat.update({
				where: {
					name: channel
				},
				data: {
					channelOwnerId : _chat.members[1].id
				},
			});
			new_admin = _chat.members[1].id;
		}

		const chat = await this._prisma.chat.findUnique({
			where: {
				name: channel
			},
			select: {
				adminId : true,
			},

		});
		let tmp = [];
		for (let i:number = 0; i < chat.adminId.length; i++)
		{
			tmp.push(chat.adminId[i]);
		}
		const index = tmp.indexOf(_id);
		tmp.splice(index, 1);
		if (new_admin)
		{
			tmp.push(new_admin);
		}
		await this._prisma.chat.update({
			where: {
				name: channel
			},
			data: {
				adminId : tmp,
			},
		});
		
		//- si pas d'admin : members[index + 1] devient channel owner
		await this._prisma.chat.update({
			where: {
				name: channel
			},
			data: {
				members: {
					disconnect: [{id: this.clientToUser.get(client.id)}]
				}
			},
		});
		return {success: true, new_admin: new_admin,message: `You left ${channel}`}
	}
}
	async mute(is_owner: boolean, user: any, id_mute: number, from: string) {
		if ((user.chatmember.length && user.chatmember[0].adminId.length
			&& user.chatmember[0].adminId.includes(user.id)
			&& !is_owner) || (user.chatmember.length && user.chatmember[0].channelOwnerId === user.id)) {
			return ({success: false, message: "It is not possible to mute an admin"})
		}
		let check: string[] = this.muteList.get(id_mute)
		if (check) {
			if (check.includes(from)) {
				const idx: number = this.muteList.get(id_mute).indexOf(from)
				if (idx !== -1) {
					this.muteList.get(id_mute).splice(idx, 1)
					const muted: {} = await this._prisma.chat.findUnique({
						where: {
							name: from
						},
						select: {
							muteList: true
						},
					});
					let muteArray: number[] = []
					for (let i in muted) {
						muteArray.push(...muted[i])
					}
					await this._prisma.chat.update({
						where: {
							name: from
						},
						data : {
							muteList: {
								set: muteArray.filter((id) => id !== id_mute)
							}
						}
					})
					return ({success: true, message: `${user.nickname} unmuted`})
				}
				else {
					return ({success: false, message: `problem in finding index`})
				}
			}
			else {
				this.muteList.get(id_mute).push(from)
			}
		}
		else {
			this.muteList.set(id_mute, [from])
		}
		await this._prisma.chat.update({
			where: {
				name: from
			},
			data : {
				muteList: id_mute
			}
		})
		return ({success: true, message:`${user.nickname} has been muted from ${from}`})
	}

	async kick(is_owner: boolean, user: any, nick_ban: string, from: string) {
		if ((user.chatmember.length && user.chatmember[0].adminId.length
			&& user.chatmember[0].adminId.includes(user.id)
			&& !is_owner) || (user.chatmember.length && user.chatmember[0].channelOwnerId === user.id)) {
			return ({success: false, message: "It is not possible to kick an admin"})
		}
		let check: string[] = this.kickList.get(user.id)
		if (check) {
			if (check.includes(from))
				return {success: false, message: "Already kicked"}
			else {
				this.kickList.get(user.id).push(from)
			}
		}
		else {
			this.kickList.set(user.id, [from])
		}
		await this._prisma.user.update({
			where: {
				id: user.id,
			},
			data: {
				chatmember: {
					disconnect: [{name: from}],
				},
			},
		});
		return ({success: true, message: `${nick_ban} has been kicked`})
	}

	getUserToBK(id_ban: number, from: string) {
		return this._prisma.user.findUnique({
			where: {
				id: id_ban,
			},
			select: {
				id: true,
				nickname: true,
				chatmember: {
					where: {
						name: from
					},
					select: {
						banlist: true,
						adminId: true,
						channelOwnerId: true
					},
				},
			}
		});
	}

	async verify(mdp: string, id: number) {
		let _channel: any = await this._prisma.chat.findUnique({
			where: {
				id: id,
			},
			select: {
				mdpHash: true,
				name: true,
			},
		});
		if (!_channel)
			throw new ForbiddenException("No channel with this ID");

		else 
		{
			const _pw_match: boolean = await _argon.verify(_channel.mdpHash, mdp);
			if (!_pw_match)
			{
				throw new ForbiddenException("Password not okay");
			}
		}
		return {success: true, message:  `Joined ${_channel.name}`}
	}

	getChannelUser(channel: string) {
		return this._prisma.chat.findUnique({
			where: {
				name: channel,
			},

		});
	}

	addToRedirect(id:number, channelId:number)
	{
		this.Invite.set(id, channelId);
	}

	async getAllChannel() {
		try {
            const _All = await this._prisma.chat.findMany({
                select: {
                    name : true,
					id: true,
					channelOwnerId: true,
					adminId: true,
					privacy : true,
					createdAt: true,
					isMP: true,
					banlist: true,
					muteList: true,
					members: {
						select: {
							id: true,
							nickname: true,
							avatar: true,
							createdAt: true,
						}
					},
					messages:
					{
					select: {
						createdAt: true,
						id: true,
					}
				},
                }

            })
			const _AllnoMp = _All.filter((chat) => chat.isMP === false)
			return _AllnoMp
        } catch (_error) {
            console.log(_error)
            throw _error
        }
	}

	async getAllMembers(id: number) {
		try {
            const _All = await this._prisma.chat.findUnique({
				where:{
					id: id,
				},
                select: {
					members: {
						select: {
							nickname: true,
							id: true,
						}
					},
                }
            })
			return _All
        } catch (_error) {
            console.log(_error)
            throw _error
        }
	}

	async ban(is_owner: boolean, user: any, nick_ban: string, from: string) {
		if ((user.chatmember.length && user.chatmember[0].adminId.length
			&& user.chatmember[0].adminId.includes(user.id)
			&& !is_owner) || (user.chatmember.length && user.chatmember[0].channelOwnerId === user.id)) {
			return ({success: false, message: "It is not possible to ban an admin"})
		}
		if (user.chatmember.length && user.chatmember[0].banlist.length && user.chatmember[0].banlist.includes(user.id)) {
			const idx: number = this.banList.get(user.id).indexOf(from)
			if (idx !== -1) {
				this.banList.get(user.id).splice(idx, 1)
				const banned: {} = await this._prisma.chat.findUnique({
					where: {
						name: from
					},
					select: {
						banlist: true
					},
				});
				let banArray: number[] = []
				for (let i in banned) {
					banArray.push(...banned[i])
				}
				await this._prisma.chat.update({
					where: {
						name: from
					},
					data: {
						banlist: {
							set: banArray.filter((id) => id !== user.id)
						}
					}
				})
				return ({success: true, message: `${nick_ban} has been unbanned`})
			}
			return ({success: false, message: "504: issue in unban"})
		} else {
			await this._prisma.chat.update({
				where: {
					name: from
				},
				data: {
					banlist: user.id
				}
			})
			if (this.banList.get(user.id)) {
				this.banList.get(user.id).push(from)
			} else {
				this.banList.set(user.id, [from])
			}
		}
		return ({success: true, message: `${nick_ban} has been banned`})
	}

	isBanned(senderId: number, channel: string): boolean {
		const bannedChannels = this.banList.get(senderId);
		return !!bannedChannels?.includes(channel);
	}

	disconnect(client: Socket) {
		this.clientToUser.delete(client.id);
		// console.log(this.clientToUser);
	}

	getClientByName(clientId: string) {
		return this.clientToUser.get(clientId);
	}

	getAllClients(userId:number ) {
		let keys: string[] = []
		for (let [key, value] of this.clientToUser.entries()) {
			if (value === userId)
				keys.push(key);
		}
		return (keys)
	}

	getClientByValue(userId:number ) {
		for (let [key, value] of this.clientToUser.entries()) {
		  if (value === userId)
			return key;
		}
		return false
	}

	isMuted (senderId: number, channel: string): boolean {
		const mutedChannels = this.muteList.get(senderId);
		return !!mutedChannels?.includes(channel);
	}

	isKicked (senderId: number, channel: string): boolean {
	const kickedChannels = this.kickList.get(senderId);
	return !!kickedChannels?.includes(channel);
}

	async create(channel: string, createMessageDto: CreateMessageDto, sender: string, senderId: number) {
		const message = await this._prisma.messages.create({
			data: {
				content: createMessageDto.content,
				sender: {
					connect: {
						id: createMessageDto.senderId,
					},
				},
				chat: {
					connect: {
						id: createMessageDto.chatId,
					},
				},
			},
		});

		const blocklist = await this._prisma.user.findUnique({
			where: {
				id: senderId,

			},
			select :{
				blockList: true
			},
		})
		let tmp = [];
		for (let i:number = 0; i < blocklist.blockList.length; i++)
		{
			tmp.push(blocklist.blockList[i]);
		}

		const msg: FullMessage = {
			nicknameSender: sender,
			senderId: senderId,
			createdAt: message.createdAt,
			chatId: message.chatId,
			content: message.content,
			blocklist: tmp,
		};
		return msg;
	}

	async blockedBy(id: number): Promise<number[]> {
		const blockedBy = await this._prisma.user.findUnique({
			where: {
				id: id
			},
			select: {
				blockList: true
			}
		})
		let ret: number[] = []
		for (let i in blockedBy) {
			ret.push(...blockedBy[i])
		}
		return ret
	}

	async findAll(channel: string, channelId: number) {
		const all_msg = await this._prisma.messages.findMany({
			where: {
				chatId: channelId
			},
			select: {
				sender: {
					select: {
						nickname: true
					}
				},
				chatId: true,
				content: true,
				createdAt: true,
				senderId: true,
			}
		});
		return await Promise.all(all_msg.map(async (msg) => {
			const blocklist = await this.blockedBy(msg.senderId);
			return {
				...msg,
				nicknameSender: msg.sender?.nickname,
				blocklist: blocklist
			};
		}));
	}

	online(client: Socket, id: number[]) {
		let onlinepeople: number[] = []
		for (let i in id) {
			let isOnline: string | boolean = this.getClientByValue(id[i])
			if (isOnline !== false)
				onlinepeople.push(id[i])
		}
		return onlinepeople
	}

	async adminer(is_owner: boolean, user_to_admin: any, nickname: string, from: string) {
		const _chat = await this._prisma.chat.findUnique({
			where: {
				name: from,
			},
			select: {
				adminId: true,
			}
		})
		const newAdminId: number[] = _chat.adminId
		console.log("New admin", newAdminId)
		console.log("user_to_admin", user_to_admin.id)

		if (!newAdminId.includes(user_to_admin.id)) {
			newAdminId.push(user_to_admin.id)
			await this._prisma.chat.update({
				where: {
					name: from,
				},
				data: {
					adminId: newAdminId
				}
			})
			return { success: true, message: `${nickname} is now an admin` }
		}
		else
			return { success: false, message: `${nickname} is already an admin` }
	}
}
