import { IsNotEmpty, IsString } from "class-validator";

export class SiAuthDto {
	@IsString()
	@IsNotEmpty()
	cred_to_look: string

	@IsString()
	@IsNotEmpty()
	password: string
}