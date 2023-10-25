import './game.css';
import { useState, useRef, useEffect} from 'react';
import '../../style.scss'
import MoonLoader from 'react-spinners/MoonLoader';
import { checkInvite } from './Invite';

function WaitingRoom(props:{gamemod:string})
{
	const effectRun = useRef(false);
	const [loading, setLoading] = useState(true);
	const [AlreadyLog, setAlreadyLog] = useState(false);
	const Invite:boolean = checkInvite();


		useEffect(() =>
		   {
			   let isMounted: boolean = true
			   if (effectRun.current || process.env.NODE_ENV !== 'development')
			   {
				   setLoading(true);
			   }
			   return (): void => {
				isMounted = false
				effectRun.current = true
			}
		}, []);

	return (
		<>
		{AlreadyLog ? (
		<div className='formContainer'>
			<p> You are already in a game little punk !</p>
		</div>)
		: (
			<div className='formContainer'>
			<MoonLoader
			loading={loading}
			size={300}
			color="white"/>
			</div>)}
		</>)
}


/*"#36d7b7" */


export default WaitingRoom;
