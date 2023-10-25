import { useRef, useEffect, useState } from "react";
import useAuth from "../../hooks/useAuth";
import axios from "axios";
import { useCookies } from 'react-cookie';
import Login from "./Login";

function Register()
{
    const userRef = useRef<HTMLInputElement>(null);
    const [nickname, setNickname] = useState("");
    const [password, setPassword] = useState("");
    const [email, setEmail] = useState("");
    const [id, setId] = useState(0);
    const [access_token, setAccessToken] = useState("");
    const [success, setSuccess] = useState(false);
    // const [avatar, setAvatar] = useState("");

    const {auth, setAuth }: any = useAuth()
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
            setId(id);
        }, [id]);

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
                    email: email,
                    id: id,
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
                //console.log(access_token)
                const cookieValue = cookies['access_token'];
                // console.log("Cookie value:")
                // console.log(cookieValue)
                setAuth({user: email, access_token: res.data?.access_token, nickname: nickname, id:res.data.id})
                //console.log("Logged!");
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

                     {/* <div>
                        <Login/>
                    </div> */}
				</div>
			) :
            <>
            {showLogin ? (<><Login/></>) : (

            <div className="formContainer">
            <div className="formWrapper">
                <form onSubmit={handleSubmit}>
                    <label htmlFor="nickname">
                        <input type="text"
                        id="nickname"
                        ref={userRef}
                        onChange={(e) => setNickname(e.target.value)}
                        placeholder='nickname'/>
                    </label>
                    <label htmlFor="email">
                        <input type="text"
                        id="email"
                        ref={userRef}
                        onChange={(e) => setEmail(e.target.value)}
                        placeholder='email'/>
                    </label>
                    <label htmlFor="password">
                        <input type="password"
                        id="password"
                        ref={userRef}
                        onChange={(e) => setPassword(e.target.value)}
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
