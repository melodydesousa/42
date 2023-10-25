import {useRef, useState, useEffect, ChangeEvent } from "react";
import useAuth from "../../hooks/useAuth";


import axios from "axios";
import { useCookies } from 'react-cookie';

const Login = () => {
    const {auth, setAuth }: any = useAuth()

    const [cookies, setCookie] = useCookies(['access_token']);

    const userRef = useRef<any>()
    const errRef = useRef<any>()

    const [access_token, setAccessToken] = useState("");
    const [user, setUser] = useState('')
    const [pwd, setPwd] = useState('')
    const [errMsg, setErrMsg] = useState('')
    const [success, setSuccess] = useState(false)

    useEffect(() => {
        if (userRef.current)
            userRef.current.focus()
    }, [])

    useEffect( () => {
        setErrMsg('')
    }, [user, pwd])

    useEffect(() => {
        const { access_token } = auth;
        // console.log("Access Token:", access_token);
        if (access_token)
            setAccessToken(access_token);
          }, [auth.access_token, auth]);
    
    const handleSubmit = async (e: any): Promise<any> => {
        e.preventDefault()
        setUser('')
        setPwd('')
        axios({
            method: 'POST',
            url: 'auth/local/signin',
            data: {
                cred_to_look: user,
                password: pwd,
            }
        })
        .then((res) => {
            const access_token = res?.data?.access_token
            const nickname = res?.data?.nickname
            const id = res?.data?.id
            setCookie('access_token', access_token, {
                path: '/',
                expires: new Date(Date.now() + 15 * 60 * 1000),
                sameSite: 'strict',
                httpOnly: true,
            });
            // console.log(access_token)
            const cookieValue = cookies['access_token'];
            // console.log("Cookie value:")
            // console.log(cookieValue)
            setAuth({user, pwd, access_token, nickname, id})
            setSuccess(true)
        })
        .catch((error) => {
            // Handle the error
            console.error(error);
            if (!error.response) {
                setErrMsg('No response from server')
            } else if (error.response.status === 403
                || error.response.status === 400
                || error.response.status === 401) {
                setErrMsg(error.response?.data?.message)
            } else {
                setErrMsg('Sign in failed')
            }
            errRef.current.focus()
        });
    }

    return (
        <>
            {success ? (
                <div className="container">
                   {/* <div>
                    <ChatHome/>
                </div> */}
            </div>
                ) : (
            <div className="formContainer">
            <div className="formWrapper">
            <p ref={errRef} className={errMsg ? "errmsg" : "offscreen"} aria-live="assertive">{errMsg}</p>
            {/* <h1>Sign in</h1> */}
            <form onSubmit={handleSubmit}>
                <label htmlFor="cred_to_look">Nickname or email</label>
                <input type="text"
                       id="cred_to_look"
                       ref={userRef}
                       autoComplete="on"
                       onChange={(e:ChangeEvent<HTMLInputElement>) => setUser(e.target.value)}
                       value={user}
                       required
                />
                <label htmlFor="password">Password</label>
                <input type="password"
                       id="password"
                       onChange={(e:ChangeEvent<HTMLInputElement>) => setPwd(e.target.value)}
                       value={pwd}
                       required
                />
                <button>Sign in</button>
            </form>
        </div>
        </div>
            )}
        </>
    )
}

export default Login
