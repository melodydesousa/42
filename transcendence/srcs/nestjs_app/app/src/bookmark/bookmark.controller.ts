import {
	Controller,
	Body,
	Get,
	Patch,
	Delete,
	Post,
	UseGuards,
	Param,
	ParseIntPipe,
	HttpStatus,
	HttpCode
} from '@nestjs/common';
import { _jwtGuard } from "../auth/guard";
import { BookmarkService } from "./bookmark.service";
import { _GetUser } from "../auth/decorator";
import { CreateBmDto, EditBmDto } from "./dto";

//@UseGuards(_jwtGuard)
@Controller('bookmarks')
export class BookmarkController {
	constructor(private _bookmarkService: BookmarkService) { }
	@Get()
	getBookmarks(@_GetUser('id') _userId: number) {
		return this._bookmarkService.getBookmarks(_userId)
	}

	@Get(':bookId')
	getBookmarkById(
		@_GetUser('id') _userId: number,
		@Param('bookId', ParseIntPipe) _bookmarkId: number
	) {
		return this._bookmarkService.getBookmarkById(_userId, _bookmarkId)
	}

	@Post('create')
	createBookmark(
		@_GetUser('id') _userId: number,
		@Body() _dto: CreateBmDto
	) {
		return this._bookmarkService.createBookmark(_userId, _dto)
	}

	@Patch(':bookId')
	editBookmarkById(
		@_GetUser('id') _userId: number,
		@Body() _dto: EditBmDto,
		@Param('bookId', ParseIntPipe) _bookmarkId: number
	) {
		return this._bookmarkService.editBookmarkById(_userId, _dto, _bookmarkId)
	}

	@HttpCode(HttpStatus.NO_CONTENT)
	@Delete(':bookId')
	deleteBookmarkById(
		@_GetUser('id') _userId: number,
		@Param('bookId', ParseIntPipe) _bookmarkId: number
	) {
		return this._bookmarkService.deleteBookmarkById(_userId, _bookmarkId)
	}
}
