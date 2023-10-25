import {useEffect} from "react";
import useAuth from "../../hooks/useAuth";
import use42url from "../../hooks/use42url";
import Logo from "../../img/Logo.png";
import '../../style.scss'

const Login = () => {
	const oauth = use42url()
	const { persist, setPersist }: any = useAuth()

	const togglePersist = () => {
		setPersist((prev: boolean) => !prev)
	}

	useEffect(() => {
		localStorage.setItem("persist", persist)
	}, [persist])

	return (
		<div className="formContainer">
			<div className="formWrapper">
					<h1>Sign in with 42</h1>
					{/* <br /> */}
					<span className="line">
                    {/*put router link here*/}
						<a href={oauth()}>
							<img src={Logo}
							     alt="Login with 42"
							     style={{ width: '10 %', height: 'auto' }}/>
						</a>
                </span>
					<div className="persistCheck">
						<input
							type="checkbox"
							id="persist"
							onChange={togglePersist}
							checked={persist as boolean}
						/>
						<label htmlFor="persist">
							Trust this device
						</label>
					</div>
			</div>
		</div>
	)
}

export default Login;
