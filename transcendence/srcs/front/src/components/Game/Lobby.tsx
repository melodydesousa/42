import './game.css';
import { useState } from 'react';
import '../../style.scss'
import WaitingRoom from './WaitingRoom';
import game_socket from '../../sockets/game.socket';

function Lobby()
{
	const [NormalMode, setNormalMode] = useState(false);
	const [QuadriMode, setQuadriMode] = useState(false);

	const handleNormalClick = () =>
	{
		game_socket.emit("addToLobby", 'normal', (res:any) =>
		{
			if (res === true)
				setNormalMode(true);
		})
			/*game_socket.emit('addToLobby', 'normal', (response:boolean) =>
			{
				if (response === true)
					setNormalMode(true);
			})*/
	}

	const handleQuadriClick = () =>
	{
		game_socket.emit('addToLobby', 'quadri', (res:any) =>
		{
			if (res)
			{
				setQuadriMode(true);
			}
		})
	}

	return(
		<>
		{NormalMode ? (<WaitingRoom gamemod={"NormalMode"}/>) :	QuadriMode ? (
		<>
		<WaitingRoom gamemod={"QuadriMode"}/>
		</>
		) :	(
			<div className='formContainer'>
				<button type="submit" onClick={handleNormalClick}>
        	            Normal Game
				</button>
				<button type="submit" onClick={handleQuadriClick}>
        	            Quadricolor mode
				</button>
			</div>
		)}
		</>
	)
}

export default Lobby;


