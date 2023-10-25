import { useState, useEffect, useRef } from "react";
import { useNavigate, useLocation } from "react-router-dom";
import axios from "../../api/axios";
import Profiles from "./Profiles";
import './style.css'
import useAuth from "../../hooks/useAuth";
import MatchHistory from "../MatchHistory/MatchHistory";
import { Users } from "../Users";

export default function Board() {
    const [UsersData, setLeaderboardData] = useState<Users[]>([]);
    const { auth }: any = useAuth();
    const effectRun = useRef(false);
    const navigate = useNavigate();
    const location = useLocation()

    useEffect(() => {
        let isMounted: boolean = true
        const controller: AbortController = new AbortController()

        if (effectRun.current || process.env.NODE_ENV !== 'development') {
            const getUsers = async () => {
                await axios({
                    method: 'GET',
                    url: 'users',
                    headers: {
                        'Authorization': `Bearer ${auth?.access_token}`
                    },
                }).then((res) => {
                    setLeaderboardData(res.data);
                }).catch((error) => {
                    console.error(error.response?.data?.message);
                    navigate('/', { state: { from: location }, replace: true });
                })
            }
            getUsers();
        }
        return () => {
            isMounted = false
            controller.abort()
            effectRun.current = true
        }
    }, [])

    const data: Users[] = sort(UsersData);

    return (
        <div className="container-board">
            <div className="board">
                <h1 className='leaderboard'>Leaderboard</h1>
                <div className="scrollable-container">
                    <div className="flex">
                        <div className="item">
                        <div className="info">
                                <h4 className='title' style={{color: "white"}}>Ima</h4>
                            </div>
                            <div className="info">
                                <h4 className='title'> Player </h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'> Ranking </h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'> Victories </h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'> Defeats </h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'> Score </h4>
                            </div>
                        </div>
                        <div className="item">
                            <div className="info">
                                <h4 className='title'> Achievement </h4>
                            </div>
                        </div>
                    </div>
                    <div className="profiles-container">
                    </div>
                    <Profiles leaderboard={data} />
                </div>
            </div>
            <div className="container-board">
                    <MatchHistory />

            </div>
                </div>
    )
}


function sort(users: Users[]) {
    return users.sort((last, first) => {
        if (last.xp === first.xp) {
            return last.xp - first.xp;
        }
        else
            return first.xp - last.xp;
    })
}
