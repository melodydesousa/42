import axios from "axios";
import useAuth from "./useAuth";

const useDestroy = () => {
	const { setAuth }: any = useAuth()
	const destroyRefresh = async (): Promise<any> => {
		await axios({
			method: "GET",
			url: "auth/destroyrefresh",
		})
		.then(() => {
			setAuth({})
		})
		.catch((error) => {
			console.error(error);
			if (!error.response) {
				console.log('No response from server')
			} else {
				console.log(error.response?.data?.message)
			}
		})
	}
	return destroyRefresh
}

export default useDestroy
