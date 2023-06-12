import {useState, useEffect} from "react";
import Profiles from "./Profiles";
import {getUsers, Users} from "./Database";
import './style.css'
import moment from 'moment-timezone';

export default function Board({access_token}: {access_token: string}) {
    const [period, setPeriod] = useState(0);
    const [UsersData, setLeaderboardData] = useState<Users[]>([]);

    const handleClick = (e:any) => {
        setPeriod(e.target.dataset.id);
    }

    useEffect(() => {
        const updateLeaderboard = async () => {
        const data = await getUsers({access_token});
        setLeaderboardData(data);
        };
        updateLeaderboard()}, [access_token]);

    return (
        <div className="board">
                <h1 className='leaderboard'>Leaderboard</h1>
                <div className="duration">
                    <button onClick={handleClick} data-id='7'>7 days</button>
                    <button onClick={handleClick} data-id='30'>30 days</button>
                    <button onClick={handleClick} data-id='0'>All-Time</button>
                </div>
                    <div className="flex">
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Player</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Ranking</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Victories</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Defeats</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Score</h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'>Achievement</h4>
                            </div>
                        </div>
                    </div>
                <Profiles leaderboard={filter_period(UsersData, period)} />
            </div>
    )
}

function sort_by_xp(users: Users[]){
    return users.sort((last, first) => {
        if (last.xp === first.xp) {
            return last.xp - first.xp;
        }
        else
            return first.xp - last.xp;
    })
}

function filter_period(users: Users[], between:number){
    const todayCET = moment().tz('Europe/Paris');
    const previousCET = moment().tz('Europe/Paris');
    const today: Date = todayCET.toDate();

    const previous: Date = previousCET.toDate();
    previous.setDate(today.getDate() - (between + 1));

   let filter = users.filter(user => {
        if (user.games.length - 1 >= 0)
        {
            const lastGameDate: Date = new Date(user.games[user.games.length - 1].createdAt); //recup la date du dernier game
            if (Number(between) === 0)
                return user;
            else if (lastGameDate)
                return (previous <= lastGameDate && today >= lastGameDate)
        }
        return false;
    })
    return sort_by_xp(filter);
}
