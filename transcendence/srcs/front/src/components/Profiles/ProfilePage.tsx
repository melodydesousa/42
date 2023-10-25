import './profile.css'
import { useState, useEffect, useRef } from "react";
import { useParams } from "react-router-dom";
import MatchHistoryProfile from "./MatchHistoryProfile";
import axios from "axios";
import useAuth from "../../hooks/useAuth";
import { Users } from "../Users"
import Achievements from "./Achievements";
import {toast} from "react-toastify";

const ProfilePage = () => {
    const { auth }: any = useAuth();
    const [user, setUser] = useState<Users>({} as Users);
    const effectRun = useRef(false);
    // const navigate = useNavigate();
    const { id } = useParams();

    useEffect(() => {
        let isMounted: boolean = true
        const controller: AbortController = new AbortController()
        const userId = Number(id);

        if (effectRun.current || process.env.NODE_ENV !== 'development') {
			const host = process.env.REACT_APP_HOST
            const getUser = async (userId: number) => {
                await axios({
                    method: 'GET',
                    url: `http://${host}:3000/users/${userId}`,
                    headers: {
                        'Authorization': `Bearer ${auth?.access_token}`
                    },
                }).then((res) => {
                    if (isMounted)
                        setUser(res.data);
                }).catch((error) => {
                    console.error(error.response?.data?.message);
                })
            }
            getUser(userId);
        }
        return () => {
            isMounted = false
            controller.abort()
            effectRun.current = true
        }
    }, [id])

    const handleBlock = async () => {
        const response = await axios.post(`/users/blocked/${id}`, {
            id: id,
        }, {
            headers: {
                Authorization: `Bearer ${auth?.access_token}`,
            },
        });
        toast(response.data.message)
    }

    return (
        <div className="profile">
            <h1 className="title">Profile</h1>
            <div className="item">
                <img className="img" height="75" width="75" style={{ objectFit: 'cover', marginBottom: 10 }} src={user.avatar} alt="avatar" />
                <div className="text-profile">{user.nickname}</div>
            </div>
            {auth.id !== user.id ?
                <div className="text-profile">
                    <div className="btn-block" onClick={() => handleBlock()}>Block this user</div>
                </div>
                : null}
            <hr style={{ color: 'grey' }} />
            <MatchHistoryProfile />
            <hr style={{ color: 'white' }} />
            <Achievements />
        </div>
    )
}

export default ProfilePage;

