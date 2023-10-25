import {ForbiddenException, Injectable} from "@nestjs/common";
import {PrismaService} from "../prisma/prisma.service";
import {CreateChatDto, EditChatDto, ProtectedDto} from "./dto";
import { Chat } from "@prisma/client";
import {PrismaClientKnownRequestError} from "@prisma/client/runtime/library";
import * as _argon from "argon2";


@Injectable()
export class ChatService {
	constructor(private _prisma: PrismaService) {}
	async createChat(_userId: number, _dto: CreateChatDto): Promise<Chat> {
		try {
			if (_dto.name.length > 20)
				throw new ForbiddenException('The name is too long, try 20 char max')
			let _hash: string | undefined;
			if(_dto.privacy === "protected")
			{
				_hash = await _argon.hash(_dto.mdpHash);
			}
			const _chat = await this._prisma.chat.create({
				data: {
					name: _dto.name,
					channelOwnerId: _userId,
					adminId: _userId,
					privacy: _dto.privacy,
					mdpHash: _hash,
					isMP: _dto.isMP,
					members: {
						connect: [{id: _userId}]
					}
				}
			})
			return _chat
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

	async getAdmined(_userId: number) {
        try {
            const _alladmined = await this._prisma.chat.findMany({
                where : {
					channelOwnerId : _userId
                },
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
			const _alladminedNoMP = _alladmined.filter((chat) => chat.isMP === false)
			return _alladminedNoMP
        } catch (_error) {
            console.log(_error)
            throw _error
        }
    }

	async updateAdmin(_channelId: number, _dto: EditChatDto) {
		try {
			const _chat: Chat = await this._prisma.chat.findUnique({
				where: {
					id: _channelId,
				},
			});
			_chat.adminId.push(_dto.adminId);
			await this._prisma.chat.update({
				where: {
					id: _channelId,
				},
				data: {
					adminId: _chat.adminId,
				}
			});
			return _chat;
		} catch (_error) {
			console.log(_error)
			throw _error
		}
	}


	// UPDATE MOT DE PASSE HASH

	async updatePrivacyAndPassword(_channelId: number, _dto) 
	{
		try {
			const _chat: Chat = await this._prisma.chat.findUnique({
				where: {
					id: _channelId,
				},
			});
			if(_chat.privacy === 'protected' && _dto.privacy !== 'protected')
			{
				await this._prisma.chat.update({
					where: {
						id: _channelId,
					},
					data: {
						mdpHash: null,
						privacy: _dto.privacy,
					}
				});
			}
			else if (_chat.privacy === 'protected' && _dto.privacy === 'protected')
			{
				let _hash: string | undefined;
				_hash = await _argon.hash(_dto.mdpHash);
				await this._prisma.chat.update({
					where: {
						id: _channelId,
					},
					data: {
						mdpHash: _hash,
					}
				});
			}
			else if(_chat.privacy !== 'protected' && _dto.privacy === 'protected')
			{
				let _hash: string | undefined;
				_hash = await _argon.hash(_dto.mdpHash);
				await this._prisma.chat.update({
					where: {
						id: _channelId,
					},
					data: {
						mdpHash: _hash,
						privacy: _dto.privacy,
					}
				});
			}
			else
			{
				await this._prisma.chat.update({
					where: {
						id: _channelId,
					},
					data: {
						mdpHash: null,
						privacy: _dto.privacy,
					}
				});
			}
			return _chat;
		} catch (_error) {
			console.log(_error)
			throw _error
		}
	}

	async getMP(_userId: number) {
        try {
            const _all = await this._prisma.chat.findMany({
                where : {
					channelOwnerId : _userId
                },
                select: {
                    name : true,
					id: true,
					channelOwnerId: true,
					adminId: true,
					privacy : true,
					createdAt: true,
					isMP: true,
					banlist: true,
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
			const _allMP = _all.filter((chat) => chat.isMP === true)
			return _allMP
        } catch (_error) {
            console.log(_error)
            throw _error
        }
    }


	async accessProtected(_dto: ProtectedDto): Promise<any> {
		let _channel: Chat = await this._prisma.chat.findUnique({
			where: {
				id: _dto.cred_to_look,
			},
		});
		if (!_channel)
			throw new ForbiddenException("No channel with this name");
		else {
			const _pw_match: boolean = await _argon.verify(_channel.mdpHash, _dto.password);
			if (!_pw_match) throw new ForbiddenException("Password not okay");
		}
	}

}
