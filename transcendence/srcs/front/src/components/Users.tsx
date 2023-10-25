export interface Users {
    nickname: string;
    id: number;
    xp: number;
    won: number;
    lost: number;
    achievement: string[];
    avatar: string;
    games:
    {
        createdAt: Date;
        id: number;
        score: number;
        outcome: string;
        opponent: {
            nickname: string;
            avatar: string;
        };
    }[];
    friends: {
        user: {
            nickname: string;
            status: string;
            avatar: string;
        };
    }[];
}

export interface User {
    id: number;
    nickname: string;
}