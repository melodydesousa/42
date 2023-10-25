import React, { useRef, useEffect, useState } from "react";
import axios from "axios";
import { useNavigate, useLocation } from "react-router-dom";
import useAuth from "../../hooks/useAuth";
import useRefreshToken from "../../hooks/useRefreshToken";
import { startRefreshTimer } from "../../api/refresh-timer";

const Callback = () => {
	const { setAuth }: any = useAuth()
	const { auth }: any = useAuth()
	const refresh = useRefreshToken();
	const navigate = useNavigate()
	const location = useLocation()
	const from = location.state?.from?.pathname || "/"
	const effectRun = useRef(false);
	const [isLoading, setIsloading] = useState(true)
	const [expectCode, setExpectCode] = useState(false)
	const [twoFA, set2FA] = useState("");

	const handleSet = async () => {
		if (!twoFA)
		{
			return 
		}
		try {
			const res = await axios({
				method: "POST",
				url: '/auth/check2FACode',
				data: {
					code: twoFA,
					email: auth.user
				},
			})
			startRefreshTimer(refresh);
			setAuth({
				user: res.data?.email,
				access_token: res.data?.access_token,
				nickname: res.data?.nickname,
				id: res.data?.id
			});
			navigate(from);
			setExpectCode(false)
			} catch (error: any) {
			console.error(error.message);
			alert("wrong code")
			setAuth({
				user: "",
				nickname: ""
			})
			navigate("/login");
		}
	};

	useEffect(() => {
		set2FA(twoFA);
	}, [twoFA]);

	useEffect( () => {
		let isMounted: boolean = true
		if (effectRun.current || process.env.NODE_ENV !== 'development') {
		const doStuff = async (): Promise<void> => {
			const params = new URLSearchParams(location.search);
			const code = params.get('code');
			const host = process.env.REACT_APP_HOST
			const urlBack = `http://${host}:3000/auth/oauth2/42?code=${code}`
			try {
				if (code === "" || code === null) {
					const error_description = params.get('error_description') as string
					throw new Error(error_description)
				}
				const res = await axios({
					method: 'GET',
					url: urlBack
				})
				if (res.data?.twoFA === true) {
					setAuth({
						user: res.data?.email
					})
					setExpectCode(true)
					console.log("expecting code")
				}
				else {
					setExpectCode(false)
					startRefreshTimer(refresh);
					isMounted && setAuth({
						user: res.data?.email,
						access_token: res.data?.access_token,
						nickname: res.data?.nickname,
						id: res.data?.id
					});
					navigate(from);
				}
			} catch(error: any) {
				console.error(error.message);
				navigate("/login");
			} finally {
				isMounted && setIsloading(false)
			}
		}
		doStuff().then()
	}
		return (): void => {
			isMounted = false
			effectRun.current = true
		}
	}, []);

	return (
		<>
		{isLoading ? (
		  <p>Loading...</p>
		) : expectCode ? (
		  <>
		  	<div className="formContainer">
				<div className="formWrapper">
					<input
					type="password"
					name="code"
					placeholder="2 FA Code"
					onChange={(e) => set2FA(e.target.value)}
					/>
					<br />
					<button onClick={handleSet} type="button">
					Use code
					</button>
				</div>
			</div>
		  </>
		) : (
		  <>Success!</>
		)}
	  </>
	)
}

export default Callback
