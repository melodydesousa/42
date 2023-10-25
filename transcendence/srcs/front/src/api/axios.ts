import axios from 'axios'

axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';
axios.defaults.timeout = 5000;

export default axios.create({})
export const axiosPrivate = axios.create({
	headers: {
		'Content-Type': 'application/json'
	}
})