import {useState, useEffect} from "react";
import './style.css'
// import moment from 'moment-timezone';
import axios from "axios";
axios.defaults.timeout = 5000;

export interface User {
    nickname: string;
    xp: number;
    won: number;
	lost: number;
	achievement: string;
    avatar: string;
    games:
    {
        createdAt: Date;
        id: number;
        opponent: User;
        outcome: string;
        score: number;
    }[];
    opponentGames:
    {
        createdAt: Date;
        id: number;
        opponent: User;
        outcome: string;
        score: number;
    }[];
}

export interface Me {
    nickname: string;
    xp: number;
    won: number;
	lost: number;
	achievement: string;
    avatar: string;
    games:
    {
        createdAt: Date;
        id: number;
        opponent: User;
        outcome: string;
        score: number;
    }[];
    opponentGames:
    {
        createdAt: Date;
        id: number;
        opponent: User;
        outcome: string;
        score: number;
    }[];
}

export const getMyData = async ({access_token}: {access_token: string}): Promise<Me> => {
    const token = access_token;
    if (token)
    {
        const config = {
            headers: {
                Authorization: `Bearer ${token}`,
            },
        };
        const res = await axios.get('/users/me/games', config);
        console.log("Me:", res.data);
        return res.data;
    } 
    else
        return {} as Me;
}

function GameData({me}: {me: Me}){
    if (me.games && me.games.length === 0)
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
		{
            me.games && (
            me.games.map((game, index) => (
            <div>
                <div className="item-date" key={index}>
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
                <div className="game">
                    <div className="item">
				        <img src={game.opponent.avatar} alt=""/>
					    <div className= "text">{game.opponent.nickname}</div>
			        </div>
			    <div className="item">
				    <div className= "text">{game.score}</div> 
			    </div>
			</div>
            </div>
			)))
		}
		</>
	)
}

export default function MatchHistory({access_token}: {access_token: string}) {
    const [loading, setLoading] = useState(true);
    const [MyData, setMyData] = useState({} as Me);

    useEffect(() => {
        const updateMyData = async () => {
          const data = await getMyData({access_token});
          setMyData(data);
          setLoading(false);
        };
        updateMyData();
    }, [access_token]);

    useEffect(() => {
        if (!loading)
            console.log("Nickname:", MyData.nickname)
        // console.log("Game:", me.games[1].opponent)
    }, [MyData, loading])

    return (
        <div className="board">
                <h1 className='leaderboard'>Match History</h1>
                    {/* <div className="flex"> */}
                        {/* <div className="item">
                            <div className="info">
                                <h4 className='title'>Date</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Opponent</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Outcome</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Score</h4>
                            </div>
                        </div> */}
                    {/* </div> */}
                {loading ? (
                <p>Loading...</p>
                ) : (
                <GameData me={MyData} />)}
            </div>
    )
}
