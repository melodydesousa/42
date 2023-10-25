import axios from "../api/axios";
import useAuth from "./useAuth";

const useQrc = () => {
	const { auth }: any = useAuth();

	const getQrc = async () => {
		let qrcode: {
			success: boolean,
			image: string
		} = {success: false, image: ""}
        await axios({
			method: 'GET',
			url: 'auth/qrc',
			headers: {
				'Authorization': `Bearer ${auth?.access_token}`
			},
		})
		.then((res) => {
            qrcode = res?.data
            return qrcode
		})
		.catch((error) => {
			if (!error.response) {
				console.log('No response from server')
			}
			else {
				console.log(error.response?.data?.message)
			}
		})
        return qrcode
	}
	return getQrc
}

export default useQrc