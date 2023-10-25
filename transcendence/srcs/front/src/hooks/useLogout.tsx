import axios from "../api/axios";
import useAuth from "./useAuth";
import { stopRefreshTimer } from "../api/refresh-timer";
import { useContext } from "react";
import AuthContext from "../context/AuthProvider";
import chat_socket from "../sockets/chat.sockets";
import game_socket from "../sockets/game.socket";

const useLogout = () => {
	const { setAuth }: any = useContext(AuthContext);
	const { auth }: any = useAuth();

	const logout = async () => {
		await axios({
			method: 'POST',
			url: '/auth/logout',
			headers: {
				'Authorization': `Bearer ${auth?.access_token}`
			},
		})
		.then(() => {
		setAuth({});
		stopRefreshTimer();
		chat_socket.disconnect()
		game_socket.disconnect()
		})
		.catch((error) => {
			if (!error.response) {
				console.log('No response from server')
			}
			else {
				console.log(error.response?.data?.message)
			}
		})
	}
	return logout
}

export default useLogout
