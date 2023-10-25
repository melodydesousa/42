import { ForbiddenException, Injectable } from '@nestjs/common';
import { CreateBmDto, EditBmDto } from "./dto";
import { PrismaService } from "../prisma/prisma.service";

@Injectable()
export class BookmarkService {
	constructor(private _prisma: PrismaService) { }

	getBookmarks(_userdId: number) {
		return this._prisma.bookmark.findMany({
			where: {
				userId: _userdId
			}
		})
	}

	getBookmarkById(_userId: number, _bmId: number) {
		return this._prisma.bookmark.findFirst({
			where: {
				userId: _userId,
				id: _bmId
			}
		})
	}

	async editBookmarkById(_userId: number, _dto: EditBmDto, _bmId: number) {
		const _bm = await this._prisma.bookmark.findUnique({
			where: {
				id: _bmId
			}
		})
		if (!_bm || _bm.userId !== _userId)
			throw new ForbiddenException('Access denied')
		else {
			return this._prisma.bookmark.update({
				where: {
					id: _bmId
				},
				data: {
					..._dto
				}
			})
		}
	}

	async deleteBookmarkById(_userId: number, _bmId: number) {
		const _bm = await this._prisma.bookmark.findUnique({
			where: {
				id: _bmId
			}
		})
		if (!_bm || _bm.userId !== _userId)
			throw new ForbiddenException('Deletion denied')
		else {
			await this._prisma.bookmark.delete({
				where: {
					id: _bmId
				}
			})
		}
	}

	async createBookmark(_userId: number, _dto: CreateBmDto) {
		const _bm = await this._prisma.bookmark.create({
			data: {
				// il est aussi possible de faire:
				// userId: _userId,
				// au lieu de prendre la donnee user et de la connect a l'id de l'user
				..._dto,
				user: {
					connect: {
						id: _userId
					}
				}
			}
		})
		return _bm
	}
}
