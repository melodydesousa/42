import {IsNotEmpty, IsNumber, IsOptional, IsString} from "class-validator";
import {Type} from "class-transformer";

export class EditFriendsDto {
	@IsNumber()
	@IsNotEmpty()
	@Type(() => Number)
	friendId: number

	@IsString()
	@IsOptional()
	nickname: string

}