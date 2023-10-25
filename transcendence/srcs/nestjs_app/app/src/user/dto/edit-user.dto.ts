import { IsEmail, IsOptional, IsString } from "class-validator";

export class EditUserDto {
	@IsOptional()
	@IsEmail()
	email?: string

	// @IsOptional()
	// @IsString()
	// firstname?: string

	// @IsOptional()
	// @IsString()
	// lastname?: string

	@IsOptional()
	@IsString()
	nickname?: string

	@IsOptional()
	@IsString()
	avatar?: string

	@IsOptional()
	@IsString()
	tempS2FA?: string	
}