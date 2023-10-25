import {useEffect, useRef, useState} from "react";
import useAuth from "../../../hooks/useAuth";
import "../../../styleChat.scss";
import chat_socket from "../../../sockets/chat.sockets";
import axios from "axios";
import ScrollToBottom from "react-scroll-to-bottom"
import moment from "moment-timezone";
import MembersOptions from "./MembersOptions";
import InviteUser from "./InviteUser";
import {toast} from "react-toastify";

export interface User {
	nickname: string;
	id: number;
}

interface Channel {
	createdAt: Date;
	id: number;
	name: string;
	privacy: string;
	channelOwnerId: number;
	isMP: boolean;
	adminId: number[];
	members: User[];
	muteList: number[];
	banlist: number[];
	admin: {
		id: number;
	}[];
	messages: {
		createdAt: Date;
		id: number;
	}[];
}


interface Message {
	id: number,
	createdAt: Date,
	content: string,
	senderId: number,
	chatId: number,
	nicknameSender: string
	blocklist: number[],
}

interface ChatProps{
	channels: Channel[];
	channel: Channel;
	isChannelClicked: boolean;
	selectedChannelId: number;
}

const Chat = ({channels, channel, isChannelClicked, selectedChannelId}: ChatProps) =>
{
	const { auth }: any = useAuth();
	const [channelName, setChannelName] = useState("");
	const [currentMessage, setCurrentMessage] = useState("")
	const [messageList, setMessageList] = useState<Message[]>([])
	const effectRun1 = useRef(false);
	const effectRun2 = useRef(false);
	const isChannelClickedRef = useRef(isChannelClicked);
	const selectedChannelIdRef = useRef(selectedChannelId);

	useEffect(() => {
		if (effectRun2.current || process.env.NODE_ENV !== 'development')
		{
			setMessageList([])
			if (!channel)
				return;
			chat_socket.emit("findAllMessages",
			{
				channel: channel.name,
				channelId: channel.id
			}, (res: any) =>
			{
				for (let i in res) {
					if (res[i].blocklist.includes(auth?.id))
						res[i].content = "BLOCKED"
				}
				setMessageList((messageList) => [...messageList, ...res])
			})
		}
		return () =>
		{
			effectRun2.current = true
		}
	}, [channel,  auth?.id])

	useEffect(() =>
	{
		if (effectRun1.current || process.env.NODE_ENV !== 'development')
		{
			chat_socket.on("message", (data: Message) =>
			{
					if (data.blocklist.includes(auth?.id))
					{
						data.content = "BLOCKED";
					}
					setMessageList((messageList) => [...messageList, data])
			})
		}
		return () => {
			effectRun1.current = true
		}
	}, [auth?.id])

	const send_message = async () =>
	{
		if (currentMessage !== "" && currentMessage.length <= 255)
		{
			const message = {
				sender: auth?.nickname,
				dto: {
					senderId: auth?.id,
					content: currentMessage,
					chatId: selectedChannelId,
				},
				channel: channel.name,
			};
			chat_socket.emit('createMessage', message, (res: any) => {
				if (res !== "sent")
					toast(`${res}`)
			});
		}
		else if (currentMessage.length > 255)
		{
			const chunkSize = 255;
			const messageLength = currentMessage.length;
			let start = 0;
			while (start < messageLength)
			{
				const chunk = currentMessage.slice(start, start + chunkSize);
				const message =
				{
					sender: auth?.nickname,
					dto: {
						senderId: auth?.id,
						content: chunk,
						chatId: selectedChannelId,
					},
					channel: channel.name,
				};
				chat_socket.emit('createMessage', message);
				start += chunkSize;
			}
		}
		else
		{
			return ;
		}
		setCurrentMessage("")
	};

	const handleKeyDown = (e: any) =>
	{
		if (e.code === "Enter")
		{
			send_message()
		}
	};

	useEffect(() => {
		if (channel && channel.isMP)
		{
			const adminTab: number[] = channel.adminId.filter((id: number) => id !== auth?.id);
			const getUser = async () => {
				await axios.get(`users/${adminTab[0]}`, {
					headers:
						{
							'Authorization': `Bearer ${auth?.access_token}`
						},
				})
					.then((res) => {
						setChannelName(res.data.nickname);
					})
					.catch((err) => {
						console.log(err);
					})
			}
			getUser();
		}
		else if (channel)
		{
			setChannelName(channel.name);
		}
	}, [channel, auth?.id, auth?.access_token]);


	useEffect(() =>
	{
		if (isChannelClickedRef.current)
		{
			isChannelClickedRef.current = false;
			selectedChannelIdRef.current = 0;
		}
	}, []);

	if (!channel || !channel.name) {
		return (
			<div className="chat">
				<div className="chatInfo">
					<div>Channel or name not available</div>
				</div>
			</div>
		)
	}


	else {
		return (
			<div className="chat">
				<div className="chatInfo">
					{channelName}
					<span>
						<MembersOptions
							key={selectedChannelId}
							channels={channels}
							channel={channels.find((channel) => channel.id === selectedChannelId) as Channel}
							isChannelClicked={isChannelClicked}
							selectedChannelId={selectedChannelId}
						/>
					</span>
					<div className="chatIcons">
						{channel.isMP === false ? (
    						<InviteUser
							key={selectedChannelId}
							channel={channels.find((channel) => channel.id === selectedChannelId) as Channel}
    						/>
  					) : null}
					</div>
				</div>

				<ScrollToBottom className="messages">
				{messageList.map((message, index) => (
					channel.id === message.chatId && (
					<div className={auth.id === message.senderId ? "message owner" : "message"} key={index}>
						<div className="messageInfo">
						<div>
							from: {message.nicknameSender}
							<br />
							{moment(message.createdAt).calendar()}
						</div>
						</div>
						<div className="messageContent">
						<p>{message.content}</p>
						</div>
					</div>
					)
				))}
				</ScrollToBottom>

				<div className="input">
					<input type="text"
						   value={currentMessage}
						   onKeyDown={handleKeyDown}
					       placeholder="Write something..."
					       onChange={
								(event) => {
						       setCurrentMessage(event.target.value)
								}
							}
					/>
					<button onClick={send_message}>&#9658;</button>
				</div>
			</div>
		);
	}
};

export default Chat;
