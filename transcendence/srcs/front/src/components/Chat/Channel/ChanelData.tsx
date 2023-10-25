import axios from "axios";
import React, {useState, useRef, useEffect} from "react";
import useAuth from "../../../hooks/useAuth";
import {FaTimes} from "react-icons/fa";
import "../../../styleChat.scss";
import chat_socket from "../../../sockets/chat.sockets";
import {toast} from "react-toastify";
import ChangeAttributeChannel from "./ChangeAttributeChannel";

const lock = require('../../../img/Lock.png');
const privateChat = require('../../../img/Private.png');
const publicChat = require('../../../img/Public.png');
const adminChat = require('../../../img/Admin.png');

axios.defaults.timeout = 5000;

export interface User {
	nickname: string;
	id: number;
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
	privacy: string;
	isMP: boolean;
	members: User[];
	muteList: number[];
	banlist: number[];
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
	onChannelDataChange: (channels: Channel [], selectedChannelId: number, isChannelClicked: boolean) => void;
	channelCreated: boolean;
}

export default function ChanelData({channels, myData, allUsers, onChannelDataChange }: {channels: Channel[] | null, myData: User, allUsers: Users[], onChannelDataChange: Function }) {
	const { auth }: any = useAuth();
	const otherUsersChannels :Channel[] = [];
	const newAllUsers = allUsers.filter((user: Users) => user.id !== myData.id);
	const [membersList, setMembersList] = useState<User[]>([]);

	const [showChangeAttributeForm, setShowChangeAttributeForm] = useState(false);
	const [selectedChannelId, setSelectedChannelId] = useState(0);
	const [selectedAttributeType, setSelectedAttributeType] = useState('');
	const [selectedChannel, setSelectedChannel] = useState<Channel>();
	const [showPasswordPopup, setShowPasswordPopup] = useState(false);
	const [password, setPassword] = useState("");
	const effectRun = useRef(false);


	useEffect(() => {
		chat_socket.on("mustclose", () => {
			const isChannelClicked = false;
			onChannelDataChange(channels, 0, isChannelClicked);
		})
	}, [channels, onChannelDataChange])

	newAllUsers.forEach((user: Users) =>
	{
		user.adminOf.forEach((channel: Channel) =>
		{
			if (channel.privacy !== 'private' && (channel.isMP === false || channel.isMP === undefined) )
				otherUsersChannels.push(channel);
		});
	});



	const handleLeaveChat = async (channelName: string, channelId: number) => {
		chat_socket.emit("leave", {channel: channelName}, (res: any) => {
			onChannelDataChange([], 0, false);
			if(res)
			{
				toast(`${res.message}`);
			}
			chat_socket.emit('memberList', ({id: channelId}),(res:User[]) =>
			{
				setMembersList(res);
			});
			chat_socket.emit("UpMemberList", {id: channelId}, (res: any) => {
			})
			chat_socket.emit('CreateChannel');
		})
	};

	useEffect(() =>
	{
		if (effectRun.current || process.env.NODE_ENV !== 'development')
		{
			chat_socket.on('RefreshMemberList', (data:User[]) =>
			{
				setMembersList(data);
			});
		}
		return (): void =>
		{
			effectRun.current = true
		}
	}, [membersList]);

	const openChangeAttributeForm = (channelId: number, attributeType: string) =>
	{
		setSelectedChannelId(channelId);
		setSelectedAttributeType(attributeType);
		setShowChangeAttributeForm(true);
		const channel = channels?.find((channel) => channel.id === channelId);
		if (channel)
		{
			setSelectedChannel(channel);
			setShowChangeAttributeForm(true);
		}
	};

	const handleCloseChangeAttributeForm = () =>
	{
		setShowChangeAttributeForm(false);
	};

	const handleCloseForm = () =>
	{
		setShowPasswordPopup(false);
	};

	const handleSubmitPass = async (e: React.FormEvent<HTMLFormElement>) =>
	{
		e.preventDefault();
		if (channels && selectedChannel)
		{
	  		try
			{
				const formElement = e.target as HTMLFormElement;
				const passwordInput = formElement.elements.namedItem("password") as HTMLInputElement;
				const enteredPassword = passwordInput?.value;

				chat_socket.emit("verifyPassword", {mdp: enteredPassword, room: selectedChannelId}, (res : any) =>
				{
					if(res.success === true)
					{
						handleJoinChannel(channels, selectedChannelId, selectedChannel, true);
						setShowPasswordPopup(false);
					}
					else
					{
						console.error("Error Comparing Password:");
						toast("Wrong Password. Retry Please.");
					}
				})
			}
			catch (error)
			{
				console.error("Error Comparing Password:");
				toast("Wrong Password. Retry Please.");
			}}
	};


	const handleJoinChannel = (channels: Channel[], channelId: number, channel: Channel, mdpVerif : boolean) =>
	{
		if (channel.privacy === "protected" && !mdpVerif)
		{
			setSelectedChannelId(channelId)
			setSelectedChannel(channel)
			setShowPasswordPopup(true);
		}
		else
		{
			chat_socket.emit("check_ban", { id: auth?.id, from: channel.name }, (is_ban: any) =>
			{
				if (!is_ban)
				{
			  		const isChannelClicked = true;
					  
					// setSelectedChannelId(channelId)
					// setSelectedChannel(channel)
			  		onChannelDataChange(channels, channelId, isChannelClicked);
			  		chat_socket.emit("join", { channel: channel.name }, (res: any) => {
						chat_socket.emit("UpMemberList", { id: channel.id }, (res: any) => {});
					});
				}
				else
				{
			  		toast(`You were banned from ${channel.name}`);
				}
			});
		}
	};

	if (!channels)
	{
			return (
			<div className="flex">
				<div className="item">No Rooms yet</div>
			</div>
		);
	}

	return (
		<>
			{channels.map((channel, index) => {

				const isPrivateOwnedChannel = channel.privacy === 'private' && myData.id !== channel.channelOwnerId && !channel.members.some(member => member.id === myData.id);
				const isAdmin = myData.id === channel.channelOwnerId;

				if (isPrivateOwnedChannel && !isAdmin) {
					return null;
				}

				return (
					<div className="userChat" key={index}>
						<div className="userChatInfo">
							<div className="joinButton">
								<span>{channel.name} </span>
								<button onClick={() => handleJoinChannel(channels, channel.id, channel, false)}>join</button>
								{showPasswordPopup && channel.privacy === "protected" && (
									<div className="popup">
										<button className="closeButton" onClick={handleCloseForm}>
											<span>&times;</span>
										</button>
										<form onSubmit={handleSubmitPass}>
											<label htmlFor="password">Password:</label>
											<input
												type="password"
												id={`password-${channel.id}`}
												name="password"
												value={password}
												onChange={(e) => setPassword(e.target.value)}
											/>
											<button type="submit">Submit</button>
										</form>
									</div>
								)}
								{(
									<FaTimes
										style={{ cursor: "pointer", color: "red", alignSelf: "flex-end", alignItems: "center" }}
										onClick={() => handleLeaveChat(channel.name, channel.id)}
									/>
								)}
							</div>
							{isAdmin && (
								<div className="adminIcon">
									{channel.privacy === 'protected' && (
										<button onClick={() => openChangeAttributeForm(channel.id, 'protected')}>
											<img src={lock} alt="" />
										</button>
									)}
									{channel.privacy === 'private' && (
										<button onClick={() => openChangeAttributeForm(channel.id, 'private')}>
											<img src={privateChat} alt="" />
										</button>
									)}
									{channel.privacy === 'public' && (
										<button onClick={() => openChangeAttributeForm(channel.id, 'public')}>
											<img src={publicChat} alt="" />
										</button>
									)}
									<img src={adminChat} alt="" />
								</div>
							)}
							{!isAdmin && (
								<div className="adminIcon">
									{channel.privacy === 'protected' && <img src={lock} alt="" />}
									{channel.privacy === 'private' && <img src={privateChat} alt="" />}
									{channel.privacy === 'public' && <img src={publicChat} alt="" />}
								</div>
							)}
						</div>
					</div>
				);
			})}
			{showChangeAttributeForm && selectedChannel && (
				<ChangeAttributeChannel
					channel={selectedChannel}
					channels={channels}
					channelId={selectedChannelId}
					attributeType={selectedAttributeType}
					onClose={handleCloseChangeAttributeForm}
				/>
			)}
		</>
	);
	}