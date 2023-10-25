const use42url = () => {
	const get42 = () => {
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
	return get42
}

export default use42url

// client_id       string 	Required. The client ID you received from 42 when you registered.
// redirect_uri 	string 	Required. The URL in your app where users will be sent after authorization. See details below about redirect urls.
// scope 	        string 	A space separated list of scopes. If not provided, scope defaults to an empty list of scopes for users that don't have a valid token for the app. For users who do already have a valid token for the app, the user won't be shown the OAuth authorization page with the list of scopes. Instead, this step of the flow will automatically complete with the same scopes that were used last time the user completed the flow.
// state 	        string 	An unguessable random string. It is used to protect against cross-site request forgery attacks.
// response_type 	string 	The response type. Ususally code.
