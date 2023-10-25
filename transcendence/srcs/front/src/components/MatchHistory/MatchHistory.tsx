import {useState, useEffect, useRef} from "react";
import { useNavigate, useLocation } from "react-router-dom";
import useAuth from "../../hooks/useAuth";
import './match.css'
import axios from "axios";
axios.defaults.timeout = 5000;

export interface Games {
    createdAt: Date;
    id: number;
    opponent: string;
    outcome: string;
    score: number;
}

function GameData({MyGames}: {MyGames: Games[]}){
    if (MyGames && MyGames.length === 0)
        return (
		    <>
		    {
			    <div className="flex">
                    <div className="item">No games played yet</div>
                </div>
            }
            </>
        )
    return (
		<>
        <div className="scrollable-container">
		{
            MyGames && (
            MyGames.map((game, index) => (
            <div className="bloc-game" key={index}>
                <div className="item-date">
				    <div className= "text">{new Date(game.createdAt).toISOString().split('T')[0]}</div>
                </div>
                <div className="item-date">
			        {
                        game.outcome === "won" ? (
                            <div className= "text" style={{ color: "green", fontWeight: "bold"}} >VICTORY</div>
                        ) : (
                            <div className= "text" style={{ color: "red", fontWeight: "bold"}}>DEFEAT</div>
                        )}
                </div>
                    <div className="item">
					    <div className= "text">against <b>{game.opponent}</b></div>
			    <div className="item">
				    <div className= "text"><em>{game.score}</em></div>
			    </div>
			</div>
            </div>
			)))
		}
        </div>
		</>
	)
}

export default function MatchHistory() {
    const [loading, setLoading] = useState(true);
    const [MyGames, setMyGames] = useState([] as Games[]);
    const { auth }: any = useAuth();
    const effectRun = useRef(false);
	const navigate = useNavigate();
	const location = useLocation();

    useEffect(() => {
        let isMounted: boolean = true
        const controller: AbortController = new AbortController()

		if (effectRun.current || process.env.NODE_ENV !== 'development') {
			const getMyGames = async () => {
				await axios({
					method: 'GET',
					url: 'users/me/games',
					headers: {
						'Authorization': `Bearer ${auth?.access_token}`
					},
				}).then((res) => {
                    setMyGames(res.data);
					setLoading(false);
				}).catch ((error) => {
					console.error(error.response?.data?.message);
					navigate('/login', { state: { from: location }, replace: true });
				})
			}
			getMyGames()
		}
		return () => {
			isMounted = false
			controller.abort()
			effectRun.current = true
		}
	}, [])

    return (
                <div className="board">
                <h1 className='leaderboard'>Match History</h1>
                {loading ? (
                <p>Loading...</p>
                ) : (
                <GameData MyGames={MyGames} />)}
                </div>
    )
}
