import { ForbiddenException, Injectable } from "@nestjs/common";
import { JwtService } from "@nestjs/jwt";
import { ConfigService } from "@nestjs/config";
import { User } from "@prisma/client";
import { PrismaClientKnownRequestError } from "@prisma/client/runtime/library";
import { PrismaService } from "../prisma/prisma.service";
import { AuthDto, EditPasswordDto, SiAuthDto } from "./dto";
import * as _argon from "argon2";
import { me42, qrcode, Tokens } from "./types";
import axios from "axios";
import { error } from "console";

@Injectable()
export class AuthService {
	// On instantie en 1er un objet de type PrismaService pour accéder
	// aux variables du modèle prisma
	// et un objet JwtService pour l'authentification
	constructor(
		private _prisma: PrismaService,
		private _config: ConfigService,
		private _jwtSer: JwtService
	) {}

	async disable2FA(_userId: number) {
		await this._prisma.user.update({
			where: {
				id: _userId,
			},
			data: {
				S2FA: null,
				tempS2FA: null,
				twoFA: false
			}
		})
	}

	async checkCode(_userId: number, _code: string) {
		let _user: User = await this._prisma.user.findUnique({
			where: {
				id: _userId,
			},
		});
		if (!_user)
			throw new ForbiddenException("No user with this email or nickname");
		const spksy = require('speakeasy')
		let success = spksy.totp.verify({
				secret: _user.tempS2FA,
				encoding: 'hex',
				token: _code
			})
		if (!success)
			return {success: success}
		else {
			await this._prisma.user.update({
				where: {
					id: _userId,
				},
				data: {
					S2FA: _user.tempS2FA,
					twoFA: true,
					tempS2FA: ""
				}
			})
			return {success: success}
		}
	}

	async checkCodeAuth(_userId: string, _code: string) {
		let _user: User = await this._prisma.user.findUnique({
			where: {
				email: _userId,
			},
		});
		if (!_user)
			throw new ForbiddenException("No user with this email or nickname");
		const spksy = require('speakeasy')
		let success = spksy.totp.verify({
				secret: _user.S2FA,
				encoding: 'hex',
				token: _code
			})
		if (!success)
			throw new ForbiddenException("Wrong 2 FA code")
		else {
			const _token: Tokens = await this.signToken(_user.id, _user.email);
			await this.updateRtHash(_user.id, _token.refresh_token);
			_token.id = _user.id
			return _token
		}
	}

	async getQrc(_userId: number): Promise<qrcode> {
		const spksy = require('speakeasy')
		const qrc = require('qrcode')
		let user = await this._prisma.user.findUnique({
				where: {
					id: _userId
				}
			})
		if (!user)
			throw new ForbiddenException("No user with this email or nickname");
		let secret = spksy.generateSecret({
			name: "Quadricolors"
		})
		const image = await new Promise<string>((resolve, reject) => {
			qrc.toDataURL(secret.otpauth_url, (error: any, data: any) => {
				if (error) {
					reject(error);
				} else {
					resolve(data);
				}
			});
		});
		await this._prisma.user.update({
			where: {
				id: _userId,
			},
			data: {
				tempS2FA: secret.hex,
			},
		});
		return ({
			success: true,
			image: image
		})
	}

	// this function finishes the Authorization Code Flow to get 42 user, first we get the
	// look for a user with the email or nickname, if found, we sign in and get tokens
	// if not found, we sign up and get tokens, the return is the tokens and the user
	async oneclick(me: { email: string; nickname: string, avatar: string }): Promise<me42> {
		let _me42: me42 = {nickname: "", access_token: "", refresh_token: "", email: "", twoFA: true, id: NaN}
		let _token: Tokens
		let _user: User = await this._prisma.user.findUnique({
			where: {
				email: me.email,
			},
		});
		if (!_user) {
			const _dto: AuthDto = {email: me.email,
				nickname: me.nickname,
				avatar: me.avatar,
				password: "Pass123!"}
			_token = await this.signup(_dto)
			_me42.email = _dto.email
			_me42.nickname = _dto.nickname
			_me42.twoFA = false
			_me42.id = _token.id
		}
		else if (_user.twoFA === false) {
			_token = await this.signToken(_user.id, _user.email);
			await this.updateRtHash(_user.id, _token.refresh_token);
			_me42.email = _user.email
			_me42.nickname = _user.nickname
			_me42.twoFA = _user.twoFA
			_me42.id = _user.id
		}
		else {
			_token = {access_token: "", refresh_token: "", id: NaN}
			_me42.email = _user.email
			_me42.nickname = ""
			_me42.twoFA = _user.twoFA
		}
		_me42.access_token = _token.access_token
		_me42.refresh_token = _token.refresh_token
		return _me42
	}

	// fonction async donc return promise
	// hasher le password avec argon2
	// https://docs.nestjs.com/security/encryption-and-hashing#hashing
	// sauvagarder le user dans la DB
	// si email est pas unique, prisma throw erreur P2002
	// email var in the prisma model
	// hash var in the prisma model
	// refresh token a initialiser aussi
	async signup(_dto: AuthDto): Promise<Tokens> {
		const _hash: string = await _argon.hash(_dto.password);
		try {
			const _user: User = await this._prisma.user.create({
				data: {
					email: _dto.email,
					nickname: _dto.nickname,
					hash: _hash,
					avatar: _dto.avatar
				},
			});
			const _token = await this.signToken(_user.id, _user.email);
			await this.updateRtHash(_user.id, _token.refresh_token);
			_token.id = _user.id
			return _token;
		} catch (_error) {
			if (_error instanceof PrismaClientKnownRequestError) {
				if (_error.code == "P2002") {
					const field =
						(_error.meta.target as string)[0] +
						(_error.meta.target as string).slice(1);
					console.error(`Duplicate ${field}`);
					throw new ForbiddenException(`${field} is already in use`); //HTTP 403
				}
			}
			throw _error;
		}
	}

	// find the user by email
	// if user does not exists throw exception
	// compare password
	// if hash not same throw exception
	// return a token object for that user using signToken function
	async signin(_dto: SiAuthDto): Promise<Tokens> {
		let _user: User = await this._prisma.user.findUnique({
			where: {
				email: _dto.cred_to_look,
			},
		});
		if (!_user) {
			_user = await this._prisma.user.findUnique({
				where: {
					nickname: _dto.cred_to_look,
				},
			});
		}
		if (!_user)
			throw new ForbiddenException("No user with this email or nickname");
		else {
			const _pw_match: boolean = await _argon.verify(_user.hash, _dto.password);
			if (!_pw_match) throw new ForbiddenException("Password not okay");
		}
		const _token = await this.signToken(_user.id, _user.email);
		await this.updateRtHash(_user.id, _token.refresh_token);
		_token.id = _user.id
		return _token;
	}


	// On utilise un Jason Web Token pour resté loggé dans le
	// browser for 15mn avant de devoir se relog
	// Le payload est utilisé comme token
	// return access_token, objet de type string
	async signToken(_userId: number, _email: string): Promise<Tokens> {
		const _payload: { sub: number; _email: string } = {
			sub: _userId,
			_email,
		};
		const _aTsecret: string = this._config.get("JWT_SECRET");
		const _rTsecret: string = this._config.get("RT_SECRET");
		const [_at, _rt]: string[] = await Promise.all([
			this._jwtSer.signAsync(_payload, {
				expiresIn: "15m",
				secret: _aTsecret,
			}),
			this._jwtSer.signAsync(_payload, {
				secret: _rTsecret,
				expiresIn: 60 * 60 * 24 * 7,
			}),
		]);
		return {
			access_token: _at,
			refresh_token: _rt,
			id: _userId
		};
	}

	async updateRtHash(_userid: number, _rt: string) {
		const _hashrt = await _argon.hash(_rt);
		await this._prisma.user.update({
			where: {
				id: _userid,
			},
			data: {
				hashRT: _hashrt,
			},
		});
	}

	async refreshTokens(_userId: number, _rt: string): Promise<Tokens> {
		const _user: User = await this._prisma.user.findUnique({
			where: {
				id: _userId,
			},
		});
		if (!_user || !_user.hashRT)
			throw new ForbiddenException("1:Access denied to refresh token");
		else if (!(await _argon.verify(_user.hashRT, _rt))) {
			throw new ForbiddenException("2:Access denied to refresh token");
		}
		const _token = await this.signToken(_user.id, _user.email);
		await this.updateRtHash(_user.id, _token.refresh_token);
		return _token;
	}

	async changePassword(
		_userID: number,
		_dto: EditPasswordDto
	): Promise<Tokens> {
		const _user: User = await this._prisma.user.findUnique({
			where: {
				id: _userID,
			},
		});
		if (!_user) throw new ForbiddenException("No such user");
		const _pw_match: boolean = await _argon.verify(
			_user.hash,
			_dto.OldPassword
		);
		if (!_pw_match) throw new ForbiddenException("Password not okay");
		const _newHash = await _argon.hash(_dto.password);
		await this._prisma.user.update({
			where: {
				id: _userID,
			},
			data: {
				hash: _newHash,
			},
		});
		const _token: Tokens = await this.signToken(_user.id, _user.email);
		await this.updateRtHash(_user.id, _token.refresh_token);
		return _token;
	}

	async logout(_userId: number): Promise<void> {
		await this._prisma.user.updateMany({
			where: {
				id: _userId,
				hashRT: {
					not: null,
				},
			},
			data: {
				hashRT: null,
				isonline: false,
			},
		});
	}

	async get42OauthTokens({ code }: { code: string }): Promise<any> {
		const url = "https://api.intra.42.fr/oauth/token";
		const params = new URLSearchParams();
		params.append("grant_type", "authorization_code");
		params.append("client_id", this._config.get("REACT_APP_UID"));
		params.append("client_secret", this._config.get("AUTH_SECRET"));
		params.append("code", code);
		params.append("redirect_uri", this._config.get("REACT_APP_REDIRECT_URL"));

		let token: {access_token: string}
		await axios({
			url: url,
			method: "POST",
			data: params.toString(),
		})
		.then((res: any) => {
			token = {
				access_token: res.data.access_token,
			};
		})
		.catch((error) => {
			console.error(error?.response?.data?.error_description);
		})
		return token
	}

	async useToken42(token: {access_token: string}): Promise <any> {
		//TODO
		const url = 'https://api.intra.42.fr/v2/me'
		let me: { email: string; nickname: string, avatar: string } = {
			email: "",
			nickname: "",
			avatar: ""
		};
		await axios({
			method: 'GET',
			url: url,
			headers: {
				'Authorization': `Bearer ${token.access_token}`
			}
		})
		.then((res) => {
			me.email = res.data.email
			me.nickname = res.data.login
			me.avatar = res.data.image.versions.medium
		})
		.catch((error) => {
			console.error("ERROR:")
			console.error(error?.response?.data?.error_description);
		})
		return me
	}
}
