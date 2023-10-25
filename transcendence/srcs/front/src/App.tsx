import { Routes, Route, useNavigate  } from "react-router-dom";
import './App.css';
import './style.scss'
import Parallaxer from './components/Parallaxer';
import Layout from "./Layout";
import PersistentLog from "./components/Auth/PersistentLog";
import RequireAuth from "./components/Auth/RequireAuth";
import Unauthorized from "./components/Unauthorized";
import Missing from "./components/Missing";
import Callback from "./components/Auth/Callback";
import Login from "./components/Auth/Login";
import MatchHistory from "./components/MatchHistory/MatchHistory";
import Board from "./components/Leaderboard/Board";
import ChatHome from "./components/Chat/ChatHome";
import Navbar from "./components/Navbar/Navbar";
import Settings from "./components/Settings/Settings";
import useAuth from "./hooks/useAuth";
import Game from "./components/Game/Game";
import Lobby from "./components/Game/Lobby"
import Register from "./components/Settings/Register-old";
import Profiles from "./components/Profiles/Profiles";
import ProfilePage from "./components/Profiles/ProfilePage";
import { useEffect, useRef  } from "react";
import chat_socket from "./sockets/chat.sockets";
import game_socket from "./sockets/game.socket";
import {ToastContainer} from "react-toastify";
import 'react-toastify/dist/ReactToastify.css';

function App() {

	const navigate = useNavigate();
	const effectRun = useRef(false);


	useEffect(() =>
	{
		let isMounted: boolean = true
		if (effectRun.current || process.env.NODE_ENV !== 'development')
		{
			game_socket.on('start-game', () =>
			{
				navigate('/game')
			})

		chat_socket.on('NavigateRoom', () =>
		{
			navigate('/chat');
		})

		}
		return (): void =>
		{
			if (effectRun.current)
			{
				game_socket.emit("surrender");
			}
				isMounted = false
				effectRun.current = true
		}
	}, [])

	const { auth }: any = useAuth();
	useEffect(() => {
		const handleBeforeUnload = (event: any) => {
			chat_socket.disconnect()
			game_socket.disconnect()
		};
		window.addEventListener('beforeunload', handleBeforeUnload);
		return () => {
			window.removeEventListener('beforeunload', handleBeforeUnload);
		};
	}, []);

	return (
		<div>
			{ auth.access_token ? (
			<>
			<ToastContainer />
			<header>
					<Navbar />
			</header>
				<Parallaxer />
				<div className='container'>
					<Routes>
						<Route path="/" element={<Layout />}>
							{/* Put all the public routes here */}
							<Route path="login" element={<Login/>} />
							<Route path="unauthorized" element={<Unauthorized/>} />
							<Route path="callback" element={<Callback/>} />
							<Route path="Register" element={<Register/>} />
							{/* Put all the protected routes here */}
							<Route element={<PersistentLog />} >
								<Route element={<RequireAuth/>} >
									<Route path="/" element={<Board/>} />
									{/* <Route path="/welcome" element={<Welcome/>} /> */}
									<Route path="match_history" element={<MatchHistory/>} />
									<Route path="board" element={<Board/>} />
									<Route path="chat" element={<ChatHome/>} />
									<Route path="lobby" element={<Lobby/>} />
									<Route path="game" element={<Game/>} />
									<Route path="settings" element={<Settings/>} />
									<Route path="profile" element={<Profiles />} />
									<Route path="profile/:id" element={<ProfilePage />} />
									{/*<Route path="matchhistory" element={<MatchHistory/>} />*/}
								</Route>
							</Route>
							{/* If not found, send to Missing component */}
							<Route path="*" element={<Missing/>} />
						</Route>
					</Routes>
				</div>
			</>) : (
			<>
			<ToastContainer />
			<Parallaxer />
			<div className='container'>
				<Routes>
					<Route path="/" element={<Layout />}>
						{/* Put all the public routes here */}
						<Route path="login" element={<Login/>} />
						<Route path="unauthorized" element={<Unauthorized/>} />
						<Route path="callback" element={<Callback/>} />
						<Route path="Register" element={<Register/>} />
						{/* Put all the protected routes here */}
						<Route element={<PersistentLog />} >
							<Route element={<RequireAuth/>} >
								<Route path="/" element={<Board/>} />
								{/* <Route path="/welcome" element={<Welcome/>} /> */}
								<Route path="match_history" element={<MatchHistory/>} />
								<Route path="lobby" element={<Lobby/>} />
								<Route path="game" element={<Game/>} />
								<Route path="settings" element={<Settings/>} />
								<Route path="profile" element={<Profiles />} />
								<Route path="profile/:id" element={<ProfilePage />} />
								<Route path="chat" element={<ChatHome/>} />
								{/*<Route path="matchhistory" element={<MatchHistory/>} />*/}
							</Route>
						</Route>
						{/* If not found, send to Missing component */}
						<Route path="*" element={<Missing/>} />
					</Route>
				</Routes>
			</div>
			</>
			)}
		</div>
	);
}

export default App
