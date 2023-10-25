import {Controller, Body, Post, Get, HttpCode, HttpStatus, Res, Param, ParseIntPipe, Patch} from "@nestjs/common";
import {_GetUser} from "../auth/decorator";
import {CreateChatDto, EditChatDto, ProtectedDto} from "./dto";
import {ChatService} from "./chat.service";
import { Response } from 'express';

@Controller('chat')
export class ChatController {
	constructor(private _chatService: ChatService) {}

    @Get('admin')
    getAdmined(
        @_GetUser('id') _userId: number
    ) {
        return this._chatService.getAdmined(_userId)
    } 

	@Patch('update/admin/:id')
    updateAdmin(@Param('id', ParseIntPipe) _channelId, @Body() _dto: EditChatDto) {
        return this._chatService.updateAdmin(_channelId, _dto)
    }
	
	@Patch('update/privacy/:id')
    updatePrivacyAndPassword(@Param('id', ParseIntPipe) _channelId, @Body() _dto: EditChatDto) {
        return this._chatService.updatePrivacyAndPassword(_channelId, _dto)
    } 

	@Get('mp/:id')
    getMP(@Param('id', ParseIntPipe) _userId: number) {
        return this._chatService.getMP(_userId)
    }

	@HttpCode(HttpStatus.OK)
	@Post('protected')
	accessProtected(@Body() _dto: ProtectedDto, @Res({ passthrough: true }) response: Response): Promise<any> {
		return this._chatService.accessProtected(_dto)
	}

	@Post('create')
	createchat(
		@_GetUser('id') _userId: number,
		@Body() _dto: CreateChatDto
	) {
		return this._chatService.createChat(_userId, _dto)
	}

	@Post('ban')
	bannuser(
		@_GetUser('id') _userId: number,
		@Body() _nickname: string,
		@Body() _chatname: string
	) {
		// this._chatService.banUser(_userId, _nickname, _chatname)
	}
}