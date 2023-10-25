export const get42 = () => {
	const rootUrl = 'https://api.intra.42.fr/oauth/authorize'
	const options = {
		redirect_uri: process.env.REACT_APP_REDIRECT_URL as string,
		client_id: process.env.REACT_APP_UID as string,
		response_type: 'code',
		scope: 'public',
		// state: 'secret'
	}
	const qs = new URLSearchParams(options)
	return `${rootUrl}?${qs.toString()}`
}