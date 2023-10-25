import {ForbiddenException, Injectable, NotFoundException} from "@nestjs/common";
import {PrismaService} from "../prisma/prisma.service";
import {CreateFriendDto, EditFriendsDto} from "./dto";
import {PrismaClientKnownRequestError} from "@prisma/client/runtime/library";
import * as _argon from "argon2";
import { Friends, User } from "@prisma/client";
import { _GetUser } from "src/auth/decorator";


@Injectable()
export class FriendService {
	constructor(private _prisma: PrismaService) {}

	async createFriend(_userId: number, _dto: CreateFriendDto) {
		try {
			const _friend: Friends = await this._prisma.friends.create({
				data: {
					nickname: _dto.nickname,
					friendId : _dto.friendId,
					user: {
						connect: {
							id: _userId
						}
					}
				}
			})
			return _friend
			
		} catch (_error) {
			if (_error instanceof PrismaClientKnownRequestError) {
				if (_error.code == 'P2002') {
					const field = (_error.meta.target as string)[0] + (_error.meta.target as string).slice(1);
					console.error(`Duplicate ${field}`);
					throw new ForbiddenException(`${field} is already in use`); //HTTP 403
				}
			}
			throw _error;
		}
	}

	async editFriends(_userId: number, _dto: EditFriendsDto): Promise<any> {
		try {
			const _updatedFriends: Friends = await this._prisma.friends.create({
				data: {
					nickname: _dto.nickname,
					friendId : _dto.friendId,
					user: {
						connect: {
							id: _userId
						}
					}
			}
		});
		return _updatedFriends
	} catch (_error) {
		if (_error instanceof PrismaClientKnownRequestError) {
			if (_error.code == 'P2002') {
				const field = (_error.meta.target as string)[0] + (_error.meta.target as string).slice(1);
				console.error(`Duplicate ${field}`);
				throw new ForbiddenException(`${field} is already in use`); //HTTP 403
			}
		}
		throw _error;
	}
	}

	async getMyFriends(_userId: number): Promise<any> {
		const Friends = await this._prisma.friends.findMany({
			where: {
				userId: _userId,
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
					isonline: true,
					email: true,
					avatar: true,
				}
			})
			return user;
		});
		const friendsList = await Promise.all(friendsListPromised);
		return friendsList;
	}

	async deleteFriend(_userId: number, _friendToDelete: number): Promise<any> {
		try {
			const friends = await this._prisma.friends.findMany({
				where: {
					userId: _userId,
				},
			});
			const friend = friends.find((friend) => friend.friendId === _friendToDelete);
			if (!friend) {
				throw new NotFoundException(`Friend with id ${_friendToDelete} not found`);
			}
			const _updatedFriends: Friends = await this._prisma.friends.delete({
				where: {
					id: friend.id,
				},
			});
			const friendsBis = await this._prisma.friends.findMany({
				where: {
					userId: friend.friendId,
					//les amis de celui qu'on vient de supp 
				},
			});
			const friendBis = friendsBis.find((friend) => friend.friendId === _userId);
			if (!friendBis) {
				throw new NotFoundException(`Friend with id ${friend.friendId} not found`);
			}
			const _updatedFriendsBis: Friends = await this._prisma.friends.delete({
				where: {
					id: friendBis.id,
				},
			});
			return _updatedFriends && _updatedFriendsBis;

		} catch (_error) {
			if (_error instanceof PrismaClientKnownRequestError) {
				if (_error.code == 'P2002') {
					const field = (_error.meta.target as string)[0] + (_error.meta.target as string).slice(1);
					console.error(`Duplicate ${field}`);
					throw new ForbiddenException(`${field} is already in use`); //HTTP 403
				}
			}
			throw _error;
		}
	}
	
}

