import { Body,
		Controller,
		Get,
		Post,
		Patch,
		UseGuards,
		UseInterceptors,
		UploadedFile,
		BadRequestException,
		InternalServerErrorException, 
		Param,
		ParseIntPipe} from "@nestjs/common";
import { _jwtGuard } from "../auth/guard";
import { Public, _GetUser } from "../auth/decorator";
import { Games, User, Chat } from "@prisma/client";
import { EditUserDto } from "./dto";
import { UserService } from "./user.service";
import * as path from "path";
import { FileInterceptor } from "@nestjs/platform-express";
import { diskStorage } from "multer";

// La variable _jwt est un objet de classe Strategy déclaré dans strategy/jwt.startegy.ts
// On la récupère pour dire au décorateur @UseGuards quelle strategie garde l'accès à @Get('me')
// Le payload de la jwt.strategy est envoyé par validate et appended au user de Request
// On peut passer en paramètre du décorateur @_GetUser un champ de la db ex: email:
// @_GetUser('email') _email: string)
//@UseGuards(_jwtGuard)
@Controller('users')
export class UserController {
	constructor(private _userService: UserService) { }
	@Get('me')
	getMe(@_GetUser() _user: User): User {
		return _user
	}

	@Get('me/games')
	getMyGames(@_GetUser('id') _userId: number): Promise<Games[]> {
		return this._userService.getMyGames(_userId)
	}
	
	@Get(':id')
	getUserById(@Param('id', ParseIntPipe) _userId: number): Promise<User> {
		return this._userService.getUserById(_userId)
	}

	@Get(':id/games')
	getUserGamesById(@Param('id', ParseIntPipe) _userId: number): Promise<Games[]> {
		return this._userService.getUserGamesById(_userId)
	}

	@Get()
	getAllUsers(): Promise<User[]> {
		return this._userService.getAllUsers()
	}

	@Post('blocked/:id')
	editBlockedList(@_GetUser('id') _myId: number, @Param('id', ParseIntPipe) _blockedId: number) {
		return this._userService.editBlockedList(_myId, _blockedId)
	}

	@Patch()
	editUser(@_GetUser('id') _userId: number, @Body() _dto: EditUserDto) {
		return this._userService.editUser(_userId, _dto)
	}

	@Post('/upload')
	@UseInterceptors(
		FileInterceptor(
			'image', {
				storage: diskStorage ({
					destination: './public/profile_picture',
					filename: (req, file, cb) => {
						const name = file.fieldname.substring(0, 15) + "_" + Date.now() + path.extname(file.originalname)
						cb(null,name);
					},
				}),
			}
		)
	)
	upload(@UploadedFile() file: Express.Multer.File, @_GetUser('id') _userId: number) {
		return this._userService.upload(file, _userId);
	}
}
