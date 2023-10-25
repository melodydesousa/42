
export class Player
{
	x:number;
	y:number;
	height:number;
	width:number;
	color:string;
	v_y:number;
	lastKey:string;
	score:number;
	email:string;
	id:number;
	nickname:string;
	socket:string;
	keys: {
		w:boolean;
		s:boolean;
	}
	forfait:boolean = false;
	bonusCount:number = 0;
	result: string = '';
	constructor (x:number,	y:number, height:number, width:number, color:string, v_y:number, lastKey:string, score:number, keys: {
		w:boolean,	s:boolean})
	{
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.color = color;
		this.v_y = v_y;
		this.lastKey = lastKey;
		this.score = score;
		this.keys = keys;
	}
}

export class Ball
{
	x:number;
	y:number;
	dx:number;
	dy:number;
	rad:number;
	speed:number;
	direction:number;
	color:string;
	state:boolean;
	constructor(x:number, y:number, dx:number, dy:number, rad:number, speed:number, direction:number, color:string, state:boolean)
	{
		this.x = x;
		this.y = y;
		this.dx = dx;
		this.dy = dy;
		this.rad = rad;
		this.speed = speed;
		this.direction = direction;
		this.color = color;
		this.state = state;
	}

}

export class gamestate
{
	ball: Ball;
	powerup: Ball;
	player1: Player;
	player2: Player;
	end: boolean = false;
	StartGame = true;
	mode:string = '';
	room:string = '';
	constructor()
	{
		this.ball = new Ball(0.5, 0.5,0.01 ,  0.01 ,  0.01,0.01,  this.getRandomDirection(), "white", true);
		this.powerup = new Ball(0, 0,0,  0,  0,0,  0, "red", false);
		this.player1 = new Player(0.1, 0.2, 0.2,0.02, "white",0, "null",0,  {w:false ,s:false});
		this.player2 = new Player(0.88, 0.2, 0.2,0.02, "white",0, "null",0, {w:false ,s:false});
		this.ball.dx = 0.01 * Math.cos(this.ball.direction);
		this.ball.dy = 0.01 * Math.sin(this.ball.direction);
	}

	reset()
	{
		this.ball.direction = this.getRandomDirection();
		this.ball.x = 0.5;
		this.ball.y = 0.5;
		this.ball.dx = 0.01 * Math.cos(this.ball.direction);
		this.ball.dy = 0.01 * Math.sin(this.ball.direction);
		this.ball.speed = 0.01;
		this.powerup.state = false;
	}
	getRandomDirection()
	{
		const range = 0.70;
		let first = (Math.random() * range - range / 2) * Math.PI;
		let second = Math.random() * range - range / 2;
		second = (second + (1 - (range / 2)) * Math.sign(second)) * Math.PI ;
		return Math.random() > 0.5 ? first : second;
	}
	getData()
	{
		return (
		{
			ball: {
				x: this.ball.x,
				y: this.ball.y,
				rad: this.ball.rad,
				color: this.ball.color,
				state: this.ball.state,
				},

			powerUp: {
				x: this.powerup.x,
				y: this.powerup.y,
				rad: this.powerup.rad,
				color: this.powerup.color,
				state: this.powerup.state,
			},

			player1_x: this.player1.x,
			player1_y: this.player1.y,
			player1_height: this.player1.height,
			player1_width: this.player1.width,
			player1_score: this.player1.score,
			player1_forfait: this.player1.forfait,
			player1_nickname: this.player1.nickname,

			player2_x: this.player2.x,
			player2_y: this.player2.y,
			player2_height: this.player2.height,
			player2_width: this.player2.width,
			player2_score: this.player2.score,
			player2_forfait: this.player2.forfait,
			player2_nickname: this.player2.nickname,


			end: this.end,
			StartGame: this.StartGame,
			mode:this.mode,
		});
	}

	playerWall(player: Player)
	{
		if (player.y + player.height + player.v_y >= 1)
		{
			player.v_y = 0;
			player.y = 1 - player.height;
		}
		if (player.y + player.v_y <= 0)
		{
			player.v_y = 0;
			player.y = 0;
		}
	}

	circlevsRect(player: Player, ball:Ball)
	{
		let px:number = ball.x;
		let py:number = ball.y;
		px = Math.max(px, player.x);
		px = Math.min(px, player.x + player.width);
		py = Math.max(py, player.y);
		py = Math.min(py, player.y + player.height);
		return (Math.pow((ball.y - py), 2) + Math.pow(ball.x - px, 2) < Math.pow(ball.rad, 2));
	}

	moveBall(ball:Ball)
	{
		ball.x += ball.dx;
		ball.y += ball.dy;

	}

	ballBounce(player: Player, ball:Ball)
	{

		const collisionPoint =  this.ball.y - (player.y + player.height / 2);
		const normalizedCollisionPoint = collisionPoint / (player.height / 2);
		const adjustedAngle = normalizedCollisionPoint * Math.PI/4;
		this.ball.dy = Math.sin(adjustedAngle);

		const direction = (ball.x < 0.5) ? 1 : -1;
		ball.dx = direction * ball.speed * Math.cos(adjustedAngle);
		ball.dy = ball.speed * Math.sin(adjustedAngle);
		ball.speed += 0.005;
  	}

	PowerUp(player:Player, powerUp:Ball)
	{
		powerUp.x = 0.5;
		powerUp.y = 0.2;
		powerUp.dy = 0.00;
		powerUp.rad = 0.01;
		powerUp.direction = 0;
		powerUp.state = true;
		player.bonusCount++;
		if (player.id === this.player1.id)
			powerUp.dx = -0.01;
		else
			powerUp.dx = 0.01;
	}

	BallCollision(ball:Ball)
	{
		if (this.mode === 'QuadriMode')
		{
			if (this.player1.score - this.player2.score <= -3 && this.powerup.state === false && this.player1.bonusCount < 1)
			{
				this.PowerUp(this.player1, this.powerup);
			}
			else if (this.player2.score - this.player1.score <= -3 && this.powerup.state === false && this.player2.bonusCount < 1)
			{
				this.PowerUp(this.player2, this.powerup);
			}

		}
		if (this.player1.score >= 12)
		{
			this.player1.result = "win";
			this.end = true;
			return;
		}
		else if (this.player2.score >= 12)
		{
			this.player2.result = "win";
			this.end = true;
			return;
		}
		if ( ball.x + ball.rad >= 1 ||	ball.x - ball.rad <= 0)
		{
			if (ball.x - ball.rad<= 0)
			{
				if (this.player2.height === 0.4)
					this.player2.height = 0.2;
				this.player2.score++;
			}
			else
			{
				if (this.player1.height === 0.4)
					this.player1.height = 0.2;
				this.player1.score++;
			}
			this.reset();
		}
		if ( this.powerup.x + this.powerup.rad >= 1 ||	this.powerup.x - this.powerup.rad <= 0)
		{
			this.powerup.state = false;
		}
		if ( ball.y - ball.rad < 0 ||	ball.y + ball.rad > 1)
		{
			ball.dy *= -1;
		}
		if ( this.powerup.y - this.powerup.rad < 0 ||	this.powerup.y + this.powerup.rad > 1)
		{
			this.powerup.dy *= -1;
		}
		if (this.circlevsRect(this.player1, ball))
		{
			this.ballBounce(this.player1, ball);
		}
		else if (this.circlevsRect(this.player2, ball))
		{
			this.ballBounce(this.player2, ball);
		}

		if (this.circlevsRect(this.player1, this.powerup) && this.powerup.state)
		{
			this.powerup.state = false;
			this.player1.height = 0.4;
		}
		else if (this.circlevsRect(this.player2, this.powerup) && this.powerup.state)
		{
			this.powerup.state = false;
			this.player2.height = 0.4;
		}

	}
	update()
	{
		if (this.player1.lastKey === 's' && this.player1.keys.s === true)
		{
			this.player1.v_y = 0.015;
		}
		else if (this.player1.lastKey === 'w' && this.player1.keys.w === true)
		{
			this.player1.v_y = -0.015;
		}
		if (this.player2.lastKey === 's' && this.player2.keys.s === true)
		{
			this.player2.v_y = 0.015;
		}
		else if (this.player2.lastKey === 'w' && this.player2.keys.w === true)
		{
			this.player2.v_y = -0.015;
		}

		this.player1.y += this.player1.v_y;
		this.player2.y += this.player2.v_y;


		this.playerWall(this.player1);
		this.playerWall(this.player2);

		this.moveBall(this.ball);
		this.BallCollision(this.ball);

		if (this.powerup.state)
		{
			this.moveBall(this.powerup);
		}
	}
	movePlayerOneUp()
	{
		this.player1.lastKey = 'w';
		this.player1.keys.w = true;
	}

	movePlayerOneDown()
	{
		this.player1.lastKey = 's';
		this.player1.keys.s = true;
	}
	stopMovePlayerOneUp()
	{
		this.player1.v_y = 0;
		this.player1.keys.w = false;
	}
	stopMovePlayerOneDown()
	{
		this.player1.v_y = 0;
		this.player1.keys.s = false;
	}
	movePlayerTwoUp()
	{
		this.player2.lastKey = 'w';
		this.player2.keys.w = true;
	}

	movePlayerTwoDown()
	{
		this.player2.lastKey = 's';
		this.player2.keys.s = true;
	}
	stopMovePlayerTwoUp()
	{
		this.player2.v_y = 0;
		this.player2.keys.w = false;
	}
	stopMovePlayerTwoDown()
	{
		this.player2.v_y = 0;
		this.player2.keys.s = false;
	}


}

