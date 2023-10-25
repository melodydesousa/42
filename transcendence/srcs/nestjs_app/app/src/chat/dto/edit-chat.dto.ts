import {IsNotEmpty, IsNumber, IsOptional, IsString} from "class-validator";

export class EditChatDto {
	@IsString()
	@IsOptional()
	name?: string

	@IsNumber()
	@IsOptional()
	channelOwnerId?: number

	@IsString()
	@IsOptional()
	privacy?: string

	@IsString()
	@IsOptional()
	mdpHash?: string

	@IsNumber()
	@IsOptional()
	memberid: number

	@IsNumber()
	@IsOptional()
	adminId: number

}