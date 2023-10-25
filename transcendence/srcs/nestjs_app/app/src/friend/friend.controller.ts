import {Get, Delete, Body, Controller, HttpCode, HttpStatus, Patch, Post,Param,
	ParseIntPipe} from "@nestjs/common";
import { _GetUser } from "../auth/decorator";
import { CreateFriendDto, EditFriendsDto } from "./dto";
import { FriendService } from "./friend.service";

@Controller('friends')
export class FriendController {
	constructor(private _friendService: FriendService) {
	}

	@HttpCode(HttpStatus.OK)
	@Post('add')
    createFriend(
        @_GetUser('id') _userId: number,
        @Body() _dto: CreateFriendDto
    ) {
        return this._friendService.createFriend(_userId, _dto)
    }
	
	@HttpCode(HttpStatus.OK)
	@Post(':id')
	editFriends(@Param('id', ParseIntPipe) _userId: number, @Body() _dto: EditFriendsDto): Promise<any> {
		return this._friendService.editFriends(_userId, _dto)
	}

	@HttpCode(HttpStatus.OK)
    @Get()
	getMyFriends(@_GetUser('id') _userId: number): Promise<any> {
		return this._friendService.getMyFriends(_userId)
	}

	@HttpCode(HttpStatus.OK)
	@Delete('delete/:id')
	deleteFriend(@_GetUser('id') _myId, @Param('id', ParseIntPipe) _friendToDelete: number): Promise<any> {
		return this._friendService.deleteFriend(_myId, _friendToDelete)
	}

}
