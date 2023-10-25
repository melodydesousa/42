import {useEffect,useRef, useState} from 'react';
import './game.css';
import {drawBall, drawCanvas, drawPlayer, drawScore, drawEnd, drawForfait} from "./Draw"
import game_socket from '../../sockets/game.socket'


function Game()
{
	const [background, setbackground]	=useState('url("https://upload.wikimedia.org/wikipedia/commons/thumb/c/c8/Very_Black_screen.jpg/2560px-Very_Black_screen.jpg")');
	const [state, setState] = useState(
	{
		ball: {
			x: 0,
			y: 0,
			rad: 0,
			color: '',
			state: true,
		},
		powerUp: {
			x: 0,
			y: 0,
			rad: 0,
			color: '',
			state: false,
		},

		player1_x: 0,
		player1_y: 0,
		player1_height: 0,
		player1_width: 0,
		player1_score: 0,
		player1_forfait: false,
		player1_nickname: '',

		player2_x: 0,
		player2_y: 0,
		player2_height: 0,
		player2_width: 0,
		player2_score: 0,
		player2_forfait: false,
		player2_nickname: '',
		end: false,
		startGame: false,
		mode: '',
	});

	const effectRun = useRef(false);
	const canvasRef = useRef<HTMLCanvasElement | null>(null);

	const handlebouton1 = () =>
	{

		setbackground('url("https://upload.wikimedia.org/wikipedia/commons/thumb/c/c8/Very_Black_screen.jpg/2560px-Very_Black_screen.jpg")');

	}
	const handlebouton2 = () =>
	{

		setbackground('url("https://img.freepik.com/premium-vector/alien-fantastic-landscape-seamless-space-background-separated-layers-game-design_592022-102.jpg")');

	}

	const handlebouton3 = () =>
	{

		setbackground('url("https://t3.ftcdn.net/jpg/01/14/47/12/360_F_114471205_0O1mMyKE100dWY4kqoDKBNYJDto53kkt.jpg")');

	}

	const handlebouton4 = () =>
	{

		setbackground('url("https://static.vecteezy.com/system/resources/previews/006/316/482/original/alien-planet-game-background-free-vector.jpg")');

	}

	useEffect(() =>
	{
		let isMounted: boolean = true
		if (effectRun.current || process.env.NODE_ENV !== 'development')
		{
			game_socket.on("gameState", (data) => {
				setState(data);
			});
			window.addEventListener("keydown", e =>
			{
				switch (e.key)
				{
					case 'w':
					game_socket.emit("move_up");
					break;
				case 's':
					game_socket.emit("move_down");
					break;
				}
			})
			window.addEventListener("keyup", e =>
			{
				switch(e.key)
				{
					case 'w':
						game_socket.emit("stop_up");
						break;
					case 's':
						game_socket.emit("stop_down")
						break;
				}
			})
		}
		return (): void =>
		{
			if (effectRun.current)
			{
				game_socket.emit("surrender");
			}
			isMounted = false
			effectRun.current = true

			//game_socket.emit("surrender")
		}
	}, []);

	useEffect(() =>
	{
		const canvas = canvasRef.current;
		if (!canvas)
			return;
		const context = canvas.getContext('2d');
			if (!context)
		return;
		const redrawCanvas = () => {
		drawCanvas(context);
		if (state.end === false)
		{
			drawBall(context, state.ball);
			drawBall(context, state.powerUp);
			drawBall(context, state.powerUp);
			drawScore(context, state);
			drawPlayer(context, canvas, state);

		}
		else if (state.end === true)
		{
			if (state.player1_forfait === true || state.player2_forfait === true)
			{
				drawForfait(context, state);
			}
			else
				drawEnd(context, state);
		}
		};
		const handleResize = () =>
		{
			const { current:canvas} = canvasRef;
			if (canvas)
			{
				const {width, height} = canvas.getBoundingClientRect()
				const newWidth = window.innerWidth;
				const newHeight = (newWidth * height) / width;
				if (newHeight > window.innerHeight)
				{
					const updateHeight = window.innerHeight;
					const updateWidth = (updateHeight * width) / height;
					canvas.height = updateHeight;
					canvas.width = updateWidth;
				}
				else
				{
					canvas.width = newWidth;
					canvas.height = newHeight;
				}
			}
				redrawCanvas();
		}
		if (canvas && context)
		{
			canvas.width = window.innerWidth;
			canvas.height = window.innerHeight;
			window.addEventListener("resize", handleResize);
			handleResize();
		}
			return () => window.removeEventListener("resize", handleResize);
	}, [state]);

	return (
		<>
		<div className='game'>
		<div className='button-wrapper'>
			<button className="button-game" type="submit" onClick={ handlebouton1}>
				map 1
			</button>
			<button className="button-game2" type="submit" onClick={ handlebouton2}>
				map 2
			</button>
			<button className="button-game3" type="submit" onClick={ handlebouton3}>
				map 3
			</button>
			<button className="button-game4" type="submit" onClick={ handlebouton4}>
				map 4
			</button>
		</div>
		<div className='canvas-wrapper'>
			<canvas
				id="canvas"
				ref={canvasRef}
				style={{backgroundImage: background, backgroundPosition: 'center'}}>
			</canvas>
		</div>
		</div>
		</>
	)
}

export default Game



