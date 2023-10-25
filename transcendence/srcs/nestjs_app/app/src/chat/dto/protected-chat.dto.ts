import { IsNotEmpty, IsNumber, IsString } from "class-validator";

export class ProtectedDto {
	@IsNumber()
	@IsNotEmpty()
	cred_to_look: number

	@IsString()
	@IsNotEmpty()
	password: string
}