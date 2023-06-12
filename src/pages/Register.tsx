import { useRef, useEffect, useState, useContext } from "react";
import Board from "../components/Leaderboard/Board";
import axios from "axios";
import MatchHistory from "../components/MatchHistory/MatchHistory";
import Login from "./Login";
import AuthContext from "./context/AuthProvider";
import { useCookies } from 'react-cookie';
// import ChatHome from "./ChatHome";
// const avatar = require("../img/Avatar.png");
axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';
axios.defaults.timeout = 5000;

function Register()
{
    const userRef = useRef<HTMLInputElement>(null);
    const [nickname, setNickname] = useState("");
    const [password, setPassword] = useState("");
    const [email, setEmail] = useState("");
    const [access_token, setAccessToken] = useState("");
    const [success, setSuccess] = useState(false);
    // const [avatar, setAvatar] = useState("");

    const {auth, setAuth }: any = useContext(AuthContext)
    const [cookies, setCookie] = useCookies(['access_token']);

    const [showLogin, setShowLogin] = useState(false);

    const handleSignInClick = () => {
        setShowLogin(true);
    };

    useEffect(() => {
        if (userRef.current)
            userRef.current.focus();
        }, []);
        
    useEffect(() => {
            setNickname(nickname);
        }, [nickname]);
        
    useEffect(() => {
            setPassword(password);
        }, [password]);
        
    useEffect(() => {
            setEmail(email);
        }, [email]);

    useEffect(() => {
        const { access_token } = auth;
        // console.log("Access Token:", access_token);
        if (access_token)
            setAccessToken(access_token);
          }, [auth, auth.access_token]);
        
    const handleSubmit = async (e: any): Promise<any> => {
            e.preventDefault()
            axios({
                method: 'POST',
                url: '/auth/local/signup',
                data: {
                    nickname: nickname,
                    password: password,
                    email: email
                }
            })
            .then((res) => {
                const access_token = res?.data?.access_token
                setCookie('access_token', access_token, {
                    path: '/',
                    expires: new Date(Date.now() + 15 * 60 * 1000),
                    sameSite: 'strict',
                    httpOnly: true,
                });
                console.log(access_token)
                const cookieValue = cookies['access_token'];
                // console.log("Cookie value:")
                // console.log(cookieValue)
                setAuth({nickname, password, email, access_token})
                console.log("Logged!");
                // Handle the response
                // console.log(res.data.access_token);
                    setSuccess(true);

                    })
            .catch((error) => {
                console.error(error);
            });
        }

    return (
        <>
            {success ? (
                <div className="container">
                    <Board access_token={access_token}/>
				    <MatchHistory access_token={access_token}/>
                    {/* <div>
                        <ChatHome/>
                    </div> */}
				</div>
			) : 
            <>
            {showLogin ? (<Login />) : (
                
            <div className="formContainer">
            <div className="formWrapper">
                <form onSubmit={handleSubmit}>
                    <label htmlFor="nickname">
                        <input type="text"
                        id="nickname"
                        ref={userRef}
                        onChange={(e) => setNickname(e.target.value)} required
                        placeholder='nickname'/>
                    </label>
                    <label htmlFor="email">
                        <input type="text"
                        id="email"
                        ref={userRef}
                        onChange={(e) => setEmail(e.target.value)} required
                        placeholder='email'/>
                    </label>
                    <label htmlFor="password">
                        <input type="password"
                        id="password"
                        ref={userRef}
                        onChange={(e) => setPassword(e.target.value)} required
                        placeholder='password'/>
                    </label>
                    {/* <input style={{display:"none"}} type="file" id="file" />
                    <label htmlFor="file">
                     <input type="file"
                        id="avatar"
                        ref={userRef}
                        onChange={(e) => setAvatar(e.target.value)} />
                    </label> */}
                    <button type="submit" value="Submit">Sign up</button>
                </form>
                <span className='p'>or</span>
                <button type="submit" onClick={handleSignInClick}>
                    Sign in
                </button>
            </div>
        </div>)}
        </>
      }
    </>
  )
}

export default Register;
