import { PassportStrategy } from "@nestjs/passport";
import { ExtractJwt, Strategy } from "passport-jwt";
import { Injectable } from "@nestjs/common";
import { ConfigService } from "@nestjs/config";
import { PrismaService } from "../../prisma/prisma.service";
import { User } from "@prisma/client";

// la var secretOrKey est la signature du token, permet de contrôller que le token
// qui est en train d'être validé par la strat vient bien de notre serveur et
// correspond à la var d'env JWT_SECRET
@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy, '_jwtStr') {
	constructor(_config: ConfigService, private _prisma: PrismaService) {
		super({
			jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
			ignoreExpiration: false,
			secretOrKey: _config.get('JWT_SECRET')
		});
	}
	async validate(_payload: { sub: number, _email: string }): Promise<User> {
		// console.log({
		//   payload
		// });
		const _user: User = await this._prisma.user.findUnique({
			where: {
				id: _payload.sub
			}
		})
		// On vire les informations sensibles avant de retourner le user
		delete _user.hash
		delete _user.hashRT
		delete _user.S2FA
		delete _user.tempS2FA
		return _user
	}
}