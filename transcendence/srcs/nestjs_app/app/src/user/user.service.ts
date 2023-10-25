import {
	Injectable,
	BadRequestException,
	InternalServerErrorException, ForbiddenException
} from '@nestjs/common';
import { PrismaService } from "../prisma/prisma.service";
import { EditUserDto } from "./dto";
import { User, Games, Chat } from "@prisma/client";
import { promises as fsPromises } from 'fs';
import {PrismaClientKnownRequestError} from "@prisma/client/runtime/library";

const { unlink } = fsPromises;

@Injectable()
export class UserService {
	constructor(private _prisma: PrismaService) {}

	async upload(file: any, _userId: number) {
		const fileExt = file.originalname.match(/\.(jpg|jpeg|png|gif)$/);
		const allowedMimeTypes = ['image/jpg','image/jpeg', 'image/png', 'image/gif'];
		if (!fileExt || !allowedMimeTypes.includes(file.mimetype)) {
			await unlink(file.path)
			throw new BadRequestException('File is not an image')
		} else if (file.size > 2 * 1024 * 1024) {
			await unlink(file.path)
			throw new BadRequestException('File is too big, max 2MB')
		}
		const host = process.env.REACT_APP_HOST
		const _user: User = await this._prisma.user.update({
			where: {
				id: _userId,
			},
			data: {
				avatar: `http://${host}:3000/profile_picture/` + file.filename
			}
		});
		return _user.avatar
	}

	async editBlockedList(_myId: number, _blockedId: number) {
		let message: string = ""
		const _blocked = await this._prisma.user.findUnique({
			where: {
				id: _blockedId,
			},
			select: {
				blockList: true,
			}
		})
		if (!_blocked.blockList.includes(_myId)) {
			_blocked.blockList.push(_myId)
			await this._prisma.user.update({
				where: {
					id: _blockedId,
				},
				data: {
					blockList: _blocked.blockList,
				}})
				message = "User has been blocked"
			} 
		else if (_blocked.blockList.includes(_myId)) {
			const index = _blocked.blockList.indexOf(_myId)
			_blocked.blockList.splice(index, 1)
			await this._prisma.user.update({
				where: {
					id: _blockedId,
				},
				data: {
					blockList: _blocked.blockList,
				}})
				message = "User has been unblocked"
		}	
		const blockList = _blocked.blockList
		return ({message, blockList})
	}

	async editUser(_userId: number, _dto: EditUserDto) {
		try {
			const _user: User = await this._prisma.user.update({
				where: {
					id: _userId,
				},
				data: {
					..._dto
				}
			});
			delete _user.hashRT
			delete _user.hash
			delete _user.S2FA
			delete _user.twoFA
			delete _user.tempS2FA
			return _user
		} catch (_error) {
			if (_error instanceof PrismaClientKnownRequestError) {
				if (_error.code == "P2002") {
					const field =
						(_error.meta.target as string)[0] +
						(_error.meta.target as string).slice(1);
					console.error(`Duplicate ${field}`);
					throw new ForbiddenException(`${field} is already in use`); //HTTP 403
				}
			}
			throw _error;
		}
	}

	async getAllUsers(): Promise<any> {
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

	  async getUserById(_userId: number): Promise<any> {
		const _user = await this._prisma.user.findUnique({
			where: {
				id: _userId,
			}
		})
		return _user
	}

	async getUserGamesById(_userId: number): Promise<Games[]> {
		const _games: Games[] = await this._prisma.games.findMany({
			where: {
				userId: _userId,
			},
		})
		return _games;
	}

	  async getMyGames(_userId: number): Promise<Games[]> {
		const _games: Games[] = await this._prisma.games.findMany({
			where: {
				userId: _userId,
			},
		})
		return _games;
	}

	async getMyMP(_userId: number): Promise<any> {
		const _channels = await this._prisma.chat.findMany({
			where: {
				channelOwnerId: _userId,
			},
			select: {
				id: true,
				name: true,
				createdAt: true,
				privacy: true,
				isMP: true,
				messages: {
					select: {
						id: true,
						createdAt: true,
						content: true,
					}
				}
			}
		})
		const _mp = _channels.filter((channel) => channel.isMP === true)
		//console.log("my mp", _mp)
		return _mp;
	}

}
