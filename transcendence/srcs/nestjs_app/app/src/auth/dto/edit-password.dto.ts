import { IsNotEmpty, IsString } from "class-validator";

export class EditPasswordDto {
	@IsNotEmpty()
	@IsString()
	OldPassword: string

	@IsNotEmpty()
	@IsString()
	password: string
}