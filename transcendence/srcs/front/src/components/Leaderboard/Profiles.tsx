import './style.css';

export default function Profiles({ leaderboard }: { leaderboard: {
	nickname: string;
	xp: number;
	avatar: string;
	achievement: string[];
	won: number;
	lost: number;
	games: {
		createdAt: Date;
		id: number;
	}[];
	}[]
		})
	{
		return (
			<div id="profile">
				{Item(leaderboard)}
			</div>
		)
}


function Item(data: {
	nickname: string;
	xp: number;
	won: number;
	lost: number;
	achievement: string[];
	avatar: string;
	games: {
		createdAt: Date;
		id: number;
	}[];
	}[]){
    return (
		<>
		{
			data.map((user,index) => (
				<div className="flex" key={index}>
						<img className="img-profile" src={user.avatar} alt="" />
					<div className="item">

						<div className="text" style={{overflow: 'hidden', whiteSpace: 'nowrap', textOverflow: 'ellipsis'}}>{user.nickname}</div>
					</div>

					<div className="item">
						<div className="text">{index + 1}</div>
					</div>
					<div className="item">
						<div className="text">{user.won}</div>
					</div>
					<div className="item">
						<div className="text">{user.lost}</div>
					</div>
					<div className="item">
						<div className="text">{user.xp}</div>
					</div>
					<div className="item">
						<div className="text">{user.achievement[user.achievement.length - 1]}</div>
					</div>
				</div>
			))
		}
		</>
	)
}
