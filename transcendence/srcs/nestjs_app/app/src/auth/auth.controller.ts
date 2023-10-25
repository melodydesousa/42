import {
	Body,
	Controller,
	HttpCode,
	HttpStatus,
	Post,
	UseGuards,
	Patch,
	Res,
	Req, Get, ForbiddenException
} from "@nestjs/common";
import { AuthService } from "./auth.service";
import { AuthDto, SiAuthDto, EditPasswordDto } from "./dto";
import { AfterRefreshTok, me42, qrcode, tempS2FA, Tokens } from "./types";
import {  _RtJwtGuard } from "./guard";
import { Public, _GetUser } from "./decorator";
import { Response, Request } from 'express';


// private is short for :
// export class AuthController {
//  _authService: AuthService
//   constructor(authService: AuthService) {
//      this._authService = authService
//   }
@Controller('auth')
export class AuthController {
	constructor(private authService: AuthService) {
	}

	@HttpCode(HttpStatus.OK)
	@Patch('disable2FA')
	async disble2FA(@_GetUser('id') _userId: number) {
		return await this.authService.disable2FA(_userId)
	}

	@Public()
	@HttpCode(HttpStatus.OK)
	@Post('check2FACode')
	async checkCodeAuth(@Body() data: {email: string, code: string},
	                    @Res({passthrough: true}) response: Response): Promise<Tokens> {
		return await this.authService.checkCodeAuth(data.email, data.code).then((meTokens: Tokens) => {
			response.cookie('refresh_token', meTokens.refresh_token, {
				path: '/',
				expires: new Date(Date.now() + 7 * 24 * 60 * 60 * 1000),
				sameSite: 'strict',
				httpOnly: true,
			});
			delete meTokens.refresh_token;
			return meTokens;
		});
	}

	@HttpCode(HttpStatus.OK)
	@Post('check2FA')
	async checkCode(@_GetUser('id') _userId: number, @Body() _code: tempS2FA) {
		return await this.authService.checkCode(_userId, _code.tempS2FA)
	}

	@HttpCode(HttpStatus.OK)
	@Get('qrc')
	async getQrCode(@_GetUser('id') _userId: number): Promise<qrcode> {
		return await this.authService.getQrc(_userId)
	}

	// this call starts the Authorization Code Flow, first we extract the code from the url
	// then we use it to request a token to 42 intra, then we use this token to access infos
	// from intra 42 and finally, we return a me42 object that contains user info and tokens
	// from which we deleted the refresh token as it is stored in a cookie inaccessible
	// to the front by JS code
	@Public()
	@HttpCode(HttpStatus.OK)
	@Get('oauth2/42')
	async oneclick(@Req() request: Request,
	         @Res({passthrough: true}) response: Response): Promise<me42> {
		const code = request.query.code as string
		const token42: {access_token: string} = await this.authService.get42OauthTokens({code})
		const me: { email: string; nickname: string, avatar: string } = await this.authService.useToken42(token42)
		return this.authService.oneclick(me)
			.then((meTokens: me42) => {
			response.cookie('refresh_token', meTokens.refresh_token, {
				path: '/',
				expires: new Date(Date.now() + 7 * 24 * 60 * 60 * 1000),
				sameSite: 'strict',
				httpOnly: true,
			});
			delete meTokens.refresh_token;
			return meTokens;
		});
	}

	@Public()
	@HttpCode(HttpStatus.CREATED)
	@Post('local/signup')
	signup(@Res({ passthrough: true}) response: Response, @Body() _dto: AuthDto): Promise<Tokens> {
		return this.authService.signup(_dto).then((tokens: Tokens) => {
			response.cookie('refresh_token', tokens.refresh_token, {
				path: '/',
				expires: new Date(Date.now() + 7 * 24 * 60 * 60 * 1000),
				sameSite: 'strict',
				httpOnly: true,
			});
			delete tokens.refresh_token
			return tokens;
		});
	}

	@Public()
	@HttpCode(HttpStatus.OK)
	@Post('local/signin')
	signin(@Body() _dto: SiAuthDto, @Res({ passthrough: true }) response: Response): Promise<Tokens> {
		return this.authService.signin(_dto).then((tokens: Tokens) => {
			response.cookie('refresh_token', tokens.refresh_token, {
				    path: '/',
				    expires: new Date(Date.now() + 7 * 24 * 60 * 60 * 1000),
				    sameSite: 'strict',
				    httpOnly: true,
				});
			delete tokens.refresh_token
			return tokens;
		});
	}

	// We access the cookie to get the refresh token, it is vaidated in the strategy
	// then we pass it by its cookie name as a parameter with @Req
	@Public()
	@UseGuards(_RtJwtGuard)
	@HttpCode(HttpStatus.OK)
	@Get('refresh')
	refreshTokens(@_GetUser('id') _userId: number,
		@_GetUser('nickname') nickname: string,
		@Req() request: Request,
		@Res({passthrough: true}) response: Response): Promise <AfterRefreshTok> {
		const _rt: string = request.cookies.refresh_token;
		return this.authService.refreshTokens(_userId, _rt).then((tokens: AfterRefreshTok) => {
			response.cookie('refresh_token', tokens.refresh_token, {
				path: '/',
				expires: new Date(Date.now() + 7 * 24 * 60 * 60 * 1000),
				sameSite: 'strict',
				httpOnly: true,
			});
			delete tokens.refresh_token
			tokens.nickname = nickname
			return tokens;
		});
	}

	// Code avec refresh_token dans le header
	//
	// @Public()
	// @UseGuards(_RtJwtGuard)
	// @HttpCode(HttpStatus.OK)
	// @Post('refresh')
	// refreshTokens(@_GetUser('id') _userId: number,
	// 			  @_GetUser('refreshToken') _rt: string, @Res({passthrough: true}) response: Response): Promise <Tokens> {
	// 	return this.authService.refreshTokens(_userId, _rt).then((tokens: Tokens) => {
	// 		response.cookie('refresh_token', tokens.refresh_token, {
	// 			path: '/',
	// 			expires: new Date(Date.now() + 7 * 24 * 60 * 60 * 1000), // Expires in 7 days
	// 			sameSite: 'strict', // Set the same-site policy
	// 			httpOnly: true, // Make the cookie inaccessible to JavaScript
	// 		});
	// 		return tokens;
	// 	});
	// }


	// Le Guard a été défini en Global dans le main et sera appliqué partout
	// donc on peut commenter le UseGuards
	//@UseGuards(_jwtGuard)
	@HttpCode(HttpStatus.OK)
	@Post('logout')
	logout(@_GetUser('id') _userId: number,
		   @Res({ passthrough: true }) response: Response) {
		this.authService.logout(_userId);
		response.clearCookie('refresh_token', {
			path: '/'
		})
	}

	@Public()
	@HttpCode(HttpStatus.OK)
	@Get('destroyrefresh')
	destroyrefresh(@Res({ passthrough: true }) response: Response) {
		response.clearCookie('refresh_token', {
			path: '/'
		})
	}

	@HttpCode(HttpStatus.OK)
	@Patch('passwordchange')
	passupdate(@_GetUser('id') _userId: number,
			   @Body() _dto: EditPasswordDto,): Promise <Tokens> {
		return this.authService.changePassword(_userId, _dto)
	}
}
