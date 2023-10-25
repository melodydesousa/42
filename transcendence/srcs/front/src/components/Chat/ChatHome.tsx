import Sidebar from "./Sidebar";
import Chat from "./Channel/Chat";
import '../../styleChat.scss'
import axios from "axios";
import { useState, useEffect } from "react";


axios.defaults.timeout = 5000;

export interface User {
	id: number;
	nickname: string;
}

export interface Channel {
	createdAt: Date;
	members: User[];
	id: number;
	name: string;
	privacy: string;
	isMP: boolean;
	muteList: number[];
	banlist: number[];
	channelOwnerId : number;
	adminId: number[];
	admin: {
	id: number;
	}[]
	messages: {
	createdAt: Date;
	id: number;
	}[];
}

const ChatHome = () => {

  const [selectedChannelId, setSelectedChannelId] = useState<number>(0);
  const [isChannelClicked, setIsChannelClicked] = useState<boolean>(false);
  const [channelList, setChannelList] = useState([] as Channel[]);
  
  	const handleChannelDataChange = (channelList: Channel[], selectedChannelId: number, isChannelClicked: boolean) => 
  	{
	  setSelectedChannelId(selectedChannelId || 0);
	  setIsChannelClicked(isChannelClicked);
	  setChannelList(channelList);
	};
	

useEffect(() =>
{
	setIsChannelClicked(false);
}, [selectedChannelId]);

		return (
			<div className='homeChat'>
				<div className="containerChat">
					<Sidebar onChannelDataChange={handleChannelDataChange}/>
						{channelList.length > 0 ? (
							<Chat
								channels={channelList}
								channel={channelList.find((channel) => channel.id === selectedChannelId) as Channel}
								isChannelClicked={isChannelClicked}
								selectedChannelId={selectedChannelId}
						/>
						) : (
				<div>No Channel Yet</div>)}
							</div>
						</div>
		)
	}

export default ChatHome

