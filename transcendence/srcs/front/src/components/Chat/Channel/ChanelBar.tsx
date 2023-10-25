import axios from "axios";
import { useState, useEffect, useRef } from "react";
import useAuth from "../../../hooks/useAuth";
import ChanelData from "./ChanelData";
import "../../../styleChat.scss";
import chat_socket from "../../../sockets/chat.sockets";

axios.defaults.timeout = 5000;

export interface User {
	id: number;
	nickname: string;
}

export interface Users {
	id: number;
	nickname: string;
	adminOf: Channel[];
}

export interface Channel {
	createdAt: Date;
	id: number;
	name: string;
	members: User[];
	privacy: string;
	muteList: number[];
	banlist: number[];
	isMP: boolean;
	channelOwnerId: number;
	adminId: number[];
	admin: {
		id: number;
	}[];
	messages: {
		createdAt: Date;
		id: number;
	}[];
}

export interface ChanelBarProps {
	onChannelDataChange: (allchannels: Channel[], selectedChannelId: number, isChannelClicked: boolean) => void;
	channelCreated: boolean;
}

export default function ChanelBar({ onChannelDataChange }: ChanelBarProps) {
	const { auth }: any = useAuth();
	const [myData, setMyData] = useState({} as User);
	const [allUsers, setAllUsers] = useState<Users[]>([]);
	const [channels, setChannels] = useState<Channel[]>([]);
	const effectRun = useRef(false);
	const adm = useRef<Channel[]>([]);
	const all = useRef<Channel[]>([]);
	const [channelId, setChannelId] = useState<number>(0);
	const [isclicked, setisclicked] = useState<boolean>(false);
	const [forceReload, setforceReload] = useState<boolean>(false);

	useEffect(() => 
	{
		if (effectRun.current || process.env.NODE_ENV !== 'development') 
		{
			chat_socket.on('AlreadyOnChat', () => 
			{
				setforceReload(true);
			});
		}
		return (): void => 
		{
			effectRun.current = true
		}
	}, []);

	useEffect(() => 
	{
		if (effectRun.current || process.env.NODE_ENV !== 'development') 
		{
			chat_socket.emit('channelList', (res: Channel[]) => 
			{
				all.current = res;
				for (let value in res) 
				{
					if (res[value].adminId.includes(auth?.id)) 
					{
						adm.current.push(res[value]);
					}
				}
				setChannels(all.current);
			});
		}
		return (): void => 
		{
			effectRun.current = true
		}
	}, [auth?.id, adm]);

	useEffect(() => 
	{
		if (effectRun.current || process.env.NODE_ENV !== 'development') 
		{
			chat_socket.emit('Redirect', (res: any) => 
			{
				if (res.state === true)
				{
					setChannelId(res.channelId)
					setisclicked(true);
					setChannels(res.channel)
				}
			})
		}
		return (): void => 
		{
			effectRun.current = true
		}
	}, [channels, forceReload])

	useEffect(() => 
	{
		if (effectRun.current || process.env.NODE_ENV !== 'development') 
		{
			chat_socket.on('RefreshChannelList', (data: Channel[]) => 
			{
				setChannels(data);
			});
		}
		return (): void => 
		{
			effectRun.current = true
		}
	}, []);


	useEffect(() => 
	{
		if (effectRun.current || process.env.NODE_ENV !== 'development') 
		{
			if (isclicked === true) 
			{
				onChannelDataChange(channels, channelId, isclicked);
				chat_socket.emit("UpMemberList", { id: channelId }, (res: any) => {})
				setisclicked(false);
				setforceReload(false);
			}
			return (): void => 
			{
				effectRun.current = true
			}
		}
	}, [channels, isclicked, channelId, onChannelDataChange]);


	useEffect(() => 
	{
		const controller: AbortController = new AbortController();

		if (effectRun.current || process.env.NODE_ENV !== 'development') 
		{
			const getMyData = async () => 
			{
				try {
					const response = await axios.get('users/me/', 
					{
						headers: {
							Authorization: `Bearer ${auth?.access_token}`,
						},
					});
					setMyData(response.data);
				} catch (error) 
				{
					console.error(error);
				}
			};
			getMyData();
		}

		return () => 
		{
			controller.abort();
			effectRun.current = true;
		};
	}, [auth?.access_token]);


	useEffect(() => 
	{
		const controller: AbortController = new AbortController();

		if (effectRun.current || process.env.NODE_ENV !== 'development') 
		{
			const getAllData = async () => 
			{
				try {
					const response = await axios.get('users',
					{
						headers: 
						{
							Authorization: `Bearer ${auth?.access_token}`,
						},
					});
					setAllUsers(response.data);
				} catch (error) {
					console.error(error);
				}
			};
			getAllData();
		}

		return () => 
		{
			controller.abort();
			effectRun.current = true;
		};
	}, [auth?.access_token]);



	return (
		<div className="chat">
			<ChanelData channels={channels} myData={myData} allUsers={allUsers} onChannelDataChange={onChannelDataChange} />
			<hr style={{ color: 'grey' }} />
		</div>
	);
}