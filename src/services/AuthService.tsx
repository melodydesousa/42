import axios from 'axios';
import Register from '../pages/Register';

axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';
axios.defaults.timeout = 5000;
const Register_URL: string = '/auth/local/signup';

class AuthService {
	
	async loginNewUser(nickname: string, password:string, email:string) {
		const headers = {
			'Content-Type': 'application/x-www-form-urlencoded',
		  };
		const params = new URLSearchParams({ nickname: nickname, password: password, email: email}).toString();
		try {
			const response = await axios.post("auth/local/signin", params, { headers });
			// Handle the response
			// console.log(response.data);
			return response.data;
		  }

		catch(error) {
			// Handle the error
			console.error(error);
			return null;
		  }
	}

}

export default new AuthService();