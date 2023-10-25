import {Users} from "../Users"
import {useState, useEffect, useRef} from "react";
import { useNavigate, useLocation, useParams } from "react-router-dom";
import useAuth from "../../hooks/useAuth";
import axios from "axios";
axios.defaults.timeout = 5000;

function GameData({user}: {user: Users}){
    if (user.achievement && user.achievement.length === 0)
        return (
		    <>
		    {
			    <div className="flex">
                    <div className="item">No achievements yet</div>
                </div>
            }
            </>
        )       
    return (
		<>
		<div className="scrollable-container-profile" >
		{
            user.achievement && (
            user.achievement.map((achievement, index) => (
				<div className="bloc-game" key={index}>
                    <div className="item" >
					    <div className= "text">{achievement}</div>
			        </div>
            </div>
			)))
		}
		</div>
		</>

	)
}

export default function Achievements() {
	const [UserData, setUserData] = useState<Users>({} as Users);
    const { auth }: any = useAuth();
    const effectRun = useRef(false);
	const navigate = useNavigate();
	const location = useLocation();
    const {id} = useParams();

    useEffect(() => {
        let isMounted: boolean = true
        const controller: AbortController = new AbortController()

		if (effectRun.current || process.env.NODE_ENV !== 'development') {
			const host = process.env.REACT_APP_HOST
			const getUserData = async () => {
				await axios({
					method: 'GET',
					url: `http://${host}:3000/users/${id}`,
					headers: {
						'Authorization': `Bearer ${auth?.access_token}`
					},
				}).then((res: any) => {
                    setUserData(res.data);
				}).catch ((error: any) => {
					console.error(error.response?.data?.message);
					navigate('/login', { state: { from: location }, replace: true });
				})
			}
			getUserData()
		}
		return () => {
			isMounted = false
			controller.abort()
			effectRun.current = true
		}
	}, [])
    
    return (
		<div className="board">
                <h1 className='leaderboard'>Achievements</h1>
                <GameData user={UserData} />
			</div>
    )
}
