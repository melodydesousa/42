import {Games} from "../MatchHistory/MatchHistory"
import {useState, useEffect, useRef} from "react";
import { useNavigate, useLocation, useParams } from "react-router-dom";
import useAuth from "../../hooks/useAuth";
import axios from "axios";
axios.defaults.timeout = 5000;

function GameData({games}: {games: Games[]}){
    if (games && games.length === 0)
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
		<div className="scrollable-container-profile">
		{
            games && (
            games.map((game, index) => (
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
                    <div className="item-game">
					    <div className= "text">against <b>{game.opponent}</b></div>
			    <div className="item-game">
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

export default function MatchHistoryProfile() {
    const [loading, setLoading] = useState(true);
    const [Games, setGames] = useState([] as Games[]);
    const { auth }: any = useAuth();
    const effectRun = useRef(false);
	const navigate = useNavigate();
	const location = useLocation();
    const {id} = useParams();

    useEffect(() => {
        let isMounted: boolean = true
        const controller: AbortController = new AbortController()

		if (effectRun.current || process.env.NODE_ENV !== 'development') {
			const getGames = async () => {
			const host = process.env.REACT_APP_HOST
			await axios({
					method: 'GET',
					url: `http://${host}:3000/users/${id}/games`,
					headers: {
						'Authorization': `Bearer ${auth?.access_token}`
					},
				}).then((res) => {
                    setGames(res.data);
					setLoading(false);
				}).catch ((error) => {
					console.error(error.response?.data?.message);
					navigate('/login', { state: { from: location }, replace: true });
				})
			}
			getGames()
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
                <GameData games={Games} />)}
            </div>
    )
}
