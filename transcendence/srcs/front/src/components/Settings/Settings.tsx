import { useState, useEffect, useRef } from "react";
import useAuth from "../../hooks/useAuth";
import useQrc from "../../hooks/useQrc";
import './style.css'
import axios from "axios";

export interface User {
	nickname: string;
	xp: number;
	won: number;
	lost: number;
	email: string;
	hash: string;
	achievement: string[];
	avatar: string;
	games:
	{
		createdAt: Date;
		id: number;
		opponent: User;
		outcome: string;
		score: number;
	}[];
}

const USER_REGEX = /^[A-z][A-z0-9-_]{3,23}$/;

const Settings = () => {
	const [nickname, setNickname] = useState("");
	const [two, setTwo] = useState(false);
	const [validNick, setValidNick] = useState(false);
	const [avatar, setAvatar] = useState("");
	const [twoFA, set2FA] = useState("");
	const [errMsg, setErrMsg] = useState('');
	const [doneMsg, setDoneMsg] = useState('');
	const [qrc, setQrc] = useState("")
	const [MyData, setMyData] = useState({} as User);
	const [inputValue, setInputValue] = useState("");
	const [InputValueAvatar, setInputValueAvatar] = useState("");
	const [isActive, setIsActive] = useState(false);
	const [isButtonDisabled, setIsButtonDisabled] = useState(false);
	const userRef = useRef<HTMLInputElement>(null);
	const errRef = useRef<HTMLParagraphElement>(null);
	const doneRef = useRef<HTMLParagraphElement>(null);
	const effectRun = useRef(false);
	const { auth }: any = useAuth();
	const { setAuth }: any = useAuth();
	const getqrc = useQrc()

	const handleClick = async () => {
		setQrc((await getqrc()).image)
		setIsActive(true);
	};

	const handleCancel = () => {
		setIsActive(false);
		setErrMsg('')
		setDoneMsg('')
		set2FA("")
	};

	const handleFile = (e: any) => {
		setAvatar(e.target.files[0])
	}

	const handleClickD = async () => {
		if (!two) {
			setErrMsg("two FA already disabled")
			return
		}
		await axios({
			method: "PATCH",
			url: '/auth/disable2FA',
			headers: {
				'Authorization': `Bearer ${auth?.access_token}`
			},
		}).then(() => {
			setDoneMsg("2FA deactivated")
			setTwo(false)
		})
		.catch((error) => {
			console.error(error.response?.data?.message);
		})
	}

	const handleSet = async () => {
		if (!twoFA)
		{
			return
		}
		await axios({
			method: "POST",
			url: '/auth/check2FA',
			data: {
				tempS2FA: twoFA,
			},
			headers: {
				'Authorization': `Bearer ${auth?.access_token}`
			},
		}).then((res: any) => {
			if (res.data?.success === true) {
				setIsActive(false)
				setDoneMsg("2FA active")
				setTwo(true)
			}
			else {
				setErrMsg("Invalid code")
			}
		})
		.catch((error: any) => {
			console.error(error.response?.data?.message);
		})
		set2FA("")
	};

	useEffect(() => {
		setValidNick(USER_REGEX.test(nickname))
	}, [nickname])

	useEffect(() => {
		setErrMsg('');
	}, [nickname, twoFA, avatar])

	useEffect(() => {
		if (userRef.current)
			userRef.current.focus();
	}, []);

	useEffect(() => {
		setNickname(nickname);
		if (validNick)
			setIsButtonDisabled(false)
	}, [nickname, validNick]);

	useEffect(() => {
		set2FA(twoFA);
	}, [twoFA]);

	useEffect(() => {
		if (effectRun.current || process.env.NODE_ENV !== 'development') {
			const getMyData = async () => {
				axios({
					method: 'PATCH',
					url: '/users',
					data: {
						tempS2FA: null,
					},
					headers: {
						'Authorization': `Bearer ${auth?.access_token}`
					},
				})
				.catch((error) => {
					console.error(error.response?.data?.message);
				})
				await axios({
					method: 'GET',
					url: 'users/me',
					headers: {
						'Authorization': `Bearer ${auth?.access_token}`
					},
				}).then((res) => {
					setMyData(res.data);
					setInputValue(res.data.nickname)
					setNickname(res.data.nickname)
					setInputValueAvatar(res.data.avatar)
					setAvatar(res.data.avatar)
					setTwo(res.data.twoFA)
				}).catch((error) => {
					console.error(error.response?.data?.message);
				})
			}
			getMyData()
		}
		return () => {
			effectRun.current = true
		}
	}, [auth?.access_token])

	const handleSubmit = async (e: any): Promise<any> => {
		e.preventDefault()
		if (e){
			const valid = USER_REGEX.test(nickname)
			if (nickname === inputValue) {
				setErrMsg("Nickname: no change")
				return
			} else if (!valid) {
				setErrMsg("Invalid, must be between 4 and 23 long a-Z 0-9 -_")
				return
			}
			axios({
				method: 'PATCH',
				url: '/users',
				data: {
					nickname: nickname,
				},
				headers: {
					'Authorization': `Bearer ${auth?.access_token}`
				},
			})
			.then(() => {
				setAuth({ nickname })
				setDoneMsg("Nickname updated")
			})
			.catch((error) => {
				setErrMsg(error.response?.data?.message)
				console.error(error.response?.data?.message);
			});
		}
	}

	const handleAvatar = async (e: any): Promise<any> => {
		e.preventDefault()
		if (e){
			if (avatar === InputValueAvatar) {
				setErrMsg("Avatar: no change")
				return
			}
			const formdata = new FormData()
			formdata.append('image', avatar)
			axios({
				method: 'POST',
				url: '/users/upload',
				headers: {
					'Authorization': `Bearer ${auth?.access_token}`
				},
				data: formdata
			})
			.then((res) => {
				setAvatar(res.data)
				setInputValueAvatar(res.data)
				MyData.avatar = res.data
				setDoneMsg("Avatar updated")
			})
			.catch((error) => {
				console.error(error.response?.data?.message);
				setErrMsg(error.response?.data?.message)
			});}
	}

	return (
		<div className="settings">
			<h1 className='title'>
				Settings
			</h1>
			<div className="scrollable-contain">
			<p ref={errRef} className={errMsg ? "errmsg" : "offscreen"}>{errMsg}</p>
			<p ref={doneRef} className={doneMsg ? "ok" : "offscreen"}>{doneMsg}</p>
			<div className="formWrapper">
				<form onSubmit={handleSubmit}>
					<div className="text">Nickname:
						<div className="item">
							<label htmlFor="nickname">
								<input type="text"
									id="nickname"
									ref={userRef}
									placeholder={nickname}
									onChange={(e) => setNickname(e.target.value)} />
							</label>
						</div>
					</div>
					<button
						id="Savenickname"
						className="save"
						type="submit"
						value="Submit"
						disabled={isButtonDisabled}>
						Save nickname
					</button>
				</form>
				<form onSubmit={handleAvatar}>
					<div className="text">Avatar: <div className="item" style={{ alignItems: "right" }}>
						<img alt="avatar" src={MyData.avatar} height="75" width="75" style={{ objectFit: 'cover' }}></img></div>
						<label htmlFor="avatar">
							<input type="file"
								id="avatar"
								ref={userRef}
								onChange={handleFile} />
						</label>
					</div>
					<button
						id="SaveAvatar"
						className="save"
						type="submit"
						value="Submit"
						disabled={isButtonDisabled}>
						Save new avatar
					</button>
				</form>
				<br />
				<div className="text">2 Factor Authentication:</div>
				<div id="Box2FA" className={isActive ? "ready" : ""}>
					<button type="button" onClick={handleClickD} id="disable2FAButton" className={two ? "btn" : "offscreen"}>
						Deactivate 2FA
					</button>
					<button type="button" onClick={handleClick} id="enable2FAButton" className={!two ? "btn" : "offscreen"}>
						Activate 2FA
					</button>
					<div id="twoFAFormHolder" className="FAformHolder">
						<img alt="" src={isActive ? qrc : ""} id="qrImage" height="150" width="150" />
						<div id="twoFAUpdateForm">
							<input
								value={twoFA}
								type="password"
								name="code"
								placeholder="2 FA Code"
								onChange={(e) => set2FA(e.target.value)} />
							<br />
							<button className="btnset" onClick={handleSet} type="button">Set</button>
							<span>     </span>
							<button type="button" onClick={handleCancel} className="btn-cancel">
								Cancel
							</button>
						</div>
					</div>
				</div>
			</div>
			</div>
		</div>
	);
}

export default Settings;