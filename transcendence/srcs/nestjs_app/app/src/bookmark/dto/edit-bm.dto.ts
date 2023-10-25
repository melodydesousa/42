import { IsOptional, IsString } from "class-validator";

export class EditBmDto {
	@IsOptional()
	@IsString()
	title?: string

	@IsString()
	@IsOptional()
	description?: string

	@IsOptional()
	@IsString()
	link?: string
}