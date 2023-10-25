
export	function drawPlayer(context:CanvasRenderingContext2D, canvas:HTMLCanvasElement, gamestate:any)
	{
			context.beginPath();
			context.rect(context.canvas.width * gamestate.player1_x, context.canvas.height *gamestate.player1_y, context.canvas.width *gamestate.player1_width, context.canvas.height *gamestate.player1_height);
			context.fillStyle = gamestate.color;
			context.strokeStyle = "white";
			context.lineWidth = 1;
			context.shadowBlur = 0;
			context.shadowColor = "blue";
			context.strokeRect(context.canvas.width * gamestate.player1_x, context.canvas.height *gamestate.player1_y, context.canvas.width *gamestate.player1_width, context.canvas.height *gamestate.player1_height);
			context.fill();

			context.beginPath();
			context.rect(context.canvas.width * gamestate.player2_x, context.canvas.height *gamestate.player2_y, context.canvas.width *gamestate.player2_width, context.canvas.height *gamestate.player2_height);
			context.fillStyle = gamestate.color;
			context.strokeStyle = "white";
			context.lineWidth = 1;
			context.shadowBlur = 0;
			context.shadowColor = "blue";
			context.strokeRect(context.canvas.width * gamestate.player2_x, context.canvas.height *gamestate.player2_y, context.canvas.width *gamestate.player2_width, context.canvas.height *gamestate.player2_height);
			context.fill();
	}

export function drawBall(context:CanvasRenderingContext2D, ball:any)
	{
		if (ball.state)
		{
			context.beginPath();
			context.arc( context.canvas.width * ball.x , context.canvas.height * ball.y, ball.rad * ((context.canvas.width + context.canvas.height )/2),0, 2*Math.PI);
			context.strokeStyle =ball.color;
			context.stroke();
			context.fillStyle = ball.color;
			context.lineWidth =4;
			context.fill();
		}


	}

export function drawCanvas(context:CanvasRenderingContext2D)
{
	context.clearRect(0,0, context.canvas.width, context.canvas.height);
	context.beginPath();



}

export function drawScore(ctx:CanvasRenderingContext2D, gamestate:any)
{
	let pixel:number = 2 * ctx.canvas.width/100;
	ctx.beginPath();
	ctx.font = `${pixel}px Arial`;
	ctx.fillStyle = "white";
	ctx.fillText(`${gamestate.player1_nickname} :  ${gamestate.player1_score}`, ctx.canvas.width/5 , ctx.canvas.height/7);
	ctx.fillText(`${gamestate.player2_nickname} :  ${gamestate.player2_score}`, 3 * ctx.canvas.width/4 , ctx.canvas.height/7);
}


export function drawEnd(ctx:CanvasRenderingContext2D, gamestate:any)
{
	ctx.beginPath();
	let pixel:number = 3 * ctx.canvas.width/100;

	ctx.font = `${pixel}px Arial`;
	ctx.fillStyle = "white";
	if (gamestate.player1_score > gamestate.player2_score)
		ctx.fillText(`${gamestate.player1_nickname} win !!!`, 0.4 * ctx.canvas.width ,ctx.canvas.height/2);
	else
		ctx.fillText(`${gamestate.player2_nickname} win !!!`, 0.4 *ctx.canvas.width , ctx.canvas.height/2);
}

export function drawForfait(ctx:CanvasRenderingContext2D, gamestate:any)
{
	ctx.beginPath();
	let pixel:number = 3 * ctx.canvas.width/100;
	ctx.font = `${pixel}px Arial`;
	ctx.fillStyle = "white";
	if (gamestate.player1_forfait === true)
	{
		ctx.fillText(`${gamestate.player2_nickname} win !!!`, 0.4 * ctx.canvas.width , ctx.canvas.height/2);
	}
	if (gamestate.player2_forfait === true)
	{
		ctx.fillText(`${gamestate.player1_nickname} win !!!`,0.4 * ctx.canvas.width , ctx.canvas.height/2);
	}
}
