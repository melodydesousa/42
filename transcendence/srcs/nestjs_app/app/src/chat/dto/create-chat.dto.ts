import {IsBoolean, IsNotEmpty, IsNumber, IsOptional, IsString} from "class-validator";
import {Type} from "class-transformer";

export class CreateChatDto {
	@IsString()
	@IsNotEmpty()
	name: string

	@IsString()
	@IsNotEmpty()
	privacy: string

	@IsOptional()
	@IsString()
	mdpHash: string

	@IsBoolean()
	@IsOptional()
	@Type(() => Boolean)
	isMP: boolean

	// @IsNumber()
	// @IsNotEmpty()
	// @Transform(({ value }) => parseInt(value))
	// memberid: number
}