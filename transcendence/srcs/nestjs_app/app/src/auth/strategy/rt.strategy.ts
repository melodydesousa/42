import { PassportStrategy } from "@nestjs/passport";
import { ExtractJwt, Strategy } from "passport-jwt";
import {Injectable, UnauthorizedException} from "@nestjs/common";
import { ConfigService } from "@nestjs/config";
import { PrismaService } from "../../prisma/prisma.service";
import { User } from "@prisma/client";
import { Request } from "express";

// la var secretOrKey est la signature du token, permet de contrôller que le token
// qui est en train d'être validé par la strat vient bien de notre serveur et
// correspond à la var d'env RT_SECRET
// le token vient du cookie, si pas de cookie ou pas le bon token, 401
@Injectable()
export class RtStrategy extends PassportStrategy(Strategy, "_RtStr") {
	constructor(private configService: ConfigService, private prisma: PrismaService) {
		super({
			jwtFromRequest: (req) => req.cookies.refresh_token,
			ignoreExpiration: false,
			secretOrKey: configService.get("RT_SECRET"),
			passReqToCallback: true,
		});
	}

	async validate(req: Request, payload: { sub: number; _email: string }): Promise<any> {
		const refreshToken = req.cookies.refresh_token;
		if (!refreshToken) {
			throw new UnauthorizedException('Access Forbidden');
		}
		const user: User = await this.prisma.user.findUnique({
			where: {
				id: payload.sub,
			},
		});
		if (!user) {
			throw new UnauthorizedException('Access Forbidden');
		}
		delete user.hash;
		if (user.hashRT) delete user.hashRT;
		delete user.S2FA
		delete user.twoFA
		delete user.tempS2FA
		return {
			...user,
			refreshToken,
		};
	}
}


// Code avec refresh token dans le header de la requete
//
// @Injectable()
// export class RtStrategy extends PassportStrategy(Strategy, '_RtStr') {
// 	constructor(_config: ConfigService, private _prisma: PrismaService) {
// 		super({
// 			jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
// 			ignoreExpiration: false,
// 			secretOrKey: _config.get('RT_SECRET'),
// 			passReqToCallback: true
// 		});
// 	}
// 	async validate(_req: Request, _payload: { sub: number, _email: string }): Promise<any> {
// 		const user: User = await this._prisma.user.findUnique({
// 			where: {
// 				id: _payload.sub
// 			}
// 		})
// 		delete user.hash
// 		if (user.hashRT)
// 			delete user.hashRT
// 		const refreshToken = _req.get('authorization')
// 			.replace('Bearer', '')
// 			.trim()
// 		return {
// 			...user,
// 			refreshToken
// 		};
// 	}
// }