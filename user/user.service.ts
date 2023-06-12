import { Injectable } from '@nestjs/common';
import { PrismaService } from "../prisma/prisma.service";
import { EditUserDto } from "./dto";
import { User } from "@prisma/client";

@Injectable()
export class UserService {
	constructor(private _prisma: PrismaService) {
	}
	async editUser(_userId: number, _dto: EditUserDto) {
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
		return _user
	}

	async getAllUsers(): Promise<any> {
		const allUsers = await this._prisma.user.findMany({
			select: {
				nickname: true,
				xp: true,
				games:
				{
					select: {
						createdAt: true,
						id: true,
					}
				},
				won: true,
				lost: true,
				achievement: true,
				avatar: true
			}});
		return allUsers
	  }

	  async getMyGames(_userId: number): Promise<any> {
		const Games = await this._prisma.user.findUnique({
			where: {
				id: _userId,
			},
			select: {
				nickname: true,
				xp: true,
				games:
				{
					select: {
						createdAt: true,
						id: true,
						opponent: true,
						outcome: true,
						score: true,
					}
				},
				opponentGames:
				{
					select: {
						createdAt: true,
						id: true,
						opponent: true,
						outcome: true,
						score: true,
					}
				},
				avatar: true
			}});
		return Games
	  }
}
