import { Outlet } from "react-router-dom";
import { useEffect, useRef, useState } from "react";
import useRefreshToken from "../../hooks/useRefreshToken";
import useAuth from "../../hooks/useAuth";
import { stopRefreshTimer, startRefreshTimer } from "../../api/refresh-timer";
import useDestroy from "../../hooks/useDestroy";
import chat_socket from "../../sockets/chat.sockets";
import {toast} from "react-toastify";
import 'react-toastify/dist/ReactToastify.css';
import game_socket from "../../sockets/game.socket";

const PersistentLog = () => {
	const [isLoading, setIsloading] = useState(true)
	const refresh = useRefreshToken()
	const { auth, persist }: any = useAuth()
	const effectRun = useRef(false);
	const destroy = useDestroy()

	const doTheSocketStuff = () => {
		chat_socket.connect()
		game_socket.connect()
		game_socket.emit('handleAuth', {mail: auth?.user, id: auth?.id, nick: auth?.nickname})
		chat_socket.emit("identify", {
				id: auth?.id
		}, (res: any) => {
			toast("Aww!! Welcome back !!")
			chat_socket.emit("join", (res: any) => {
			})
		})
	}

	useEffect(() => {
		let isMounted: boolean = true
		if (effectRun.current || process.env.NODE_ENV !== 'development') {
			const verifyRefreshToken = async () => {
				try {
					if (persist === "true" || persist === true) {
						await refresh()
						startRefreshTimer(refresh)
					}
					else if (persist === "false" || persist === false) {
						// chat_socket.disconnect()
						// game_socket.disconnect()
						await destroy()
					}
				} catch (error: any) {
					console.log(error)
					if (!error.response) {
						stopRefreshTimer()
						chat_socket.disconnect()
						game_socket.disconnect()
					}
				} finally {
					isMounted && setIsloading(false)
				}
			}
			!auth.access_token ? verifyRefreshToken() : setIsloading(false)
			doTheSocketStuff()
			effectRun.current = false
		}
		return () => {
			effectRun.current = true
			isMounted = false
		}
	}, [])

	useEffect(() => {
	}, [isLoading])

	return (
		<>
			{!persist
				? <Outlet/>
				: isLoading
					? <p>Loading...</p>
					: <Outlet />
			}
		</>
	)
}

export default PersistentLog
