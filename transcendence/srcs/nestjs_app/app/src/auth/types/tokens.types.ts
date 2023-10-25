export type Tokens = {
	access_token: string,
	refresh_token: string,
	id: number
}

export type AfterRefreshTok = {
	access_token: string,
	refresh_token: string,
	id: number,
	nickname: string
}

export type me42 = {
	access_token: string,
	nickname: string,
	email: string,
	refresh_token: string,
	twoFA: boolean,
	id: number
}

export type qrcode = {
	success: boolean,
	image: string
}

export type tempS2FA = {
	tempS2FA: string
}
