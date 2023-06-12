import { Body, Controller, Get, Patch, UseGuards } from "@nestjs/common";
import { _jwtGuard } from "../auth/guard";
import { Public, _GetUser } from "../auth/decorator";
import { User } from "@prisma/client";
import { EditUserDto } from "./dto";
import { UserService } from "./user.service";

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
	getMyGames(@_GetUser('id') _userId: number): Promise<User> {
		return this._userService.getMyGames(_userId)
	}
	
	@Get()
	getAllUsers(): Promise<User[]> {
		return this._userService.getAllUsers()
	}

	@Patch()
	editUser(@_GetUser('id') _userId: number, @Body() _dto: EditUserDto) {
		return this._userService.editUser(_userId, _dto)
	}
}
