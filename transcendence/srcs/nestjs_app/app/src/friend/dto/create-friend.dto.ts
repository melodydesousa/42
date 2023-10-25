import {IsNotEmpty, IsNumber, IsOptional, IsString} from "class-validator";
import {Type} from "class-transformer";

export class CreateFriendDto {
	@IsNumber()
	@IsNotEmpty()
	@Type(() => Number)
	friendId: number

	@IsString()
	@IsNotEmpty()
	nickname: string

}