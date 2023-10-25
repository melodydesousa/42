import axios from "axios";
import useAuth from "./useAuth";
import { UseAuthDto } from "../dto";

const useRefreshToken = () => {
	const { setAuth }: any = useAuth()
	const refresh = async (): Promise<any> => {
		await axios({
			method: "GET",
			url: "auth/refresh",
		}).then((res) => {
			setAuth((prev: UseAuthDto) => {
				return { ...prev,
					access_token: res.data.access_token,
					id: res.data.id,
					nickname: res.data.nickname
				}
			})
		}).catch((error) => {
			console.error(error);
			if (!error.response) {
				console.log('No response from server')
			} else {
				console.log(error.response?.data?.message)
			}
		})
	}
	return refresh
}

export default useRefreshToken
