import axios from "axios";
axios.defaults.timeout = 5000;
axios.defaults.headers.get['Content-Type'] = 'application/x-www-form-urlencoded';

export interface Users {
    nickname: string;
    xp: number;
    won: number;
lost: number;
achievement: string;
    avatar: string;
    games:
    {
        createdAt: Date;
        id: number;
    }[];
}

export const getUsers = async ({access_token}: any): Promise<Users[]> => {
    const token = access_token;
    if (token)
    {
        // console.log("Access Token DB:", token);
        const config = {
            headers: {
                Authorization: `Bearer ${token}`,
            },
        };
        const res = await axios.get('/users', config);
        // console.log(res.data);
        return res.data;
    } 
    else
        return [];
}
