import React, {useEffect, useRef, useState} from "react";
import useAuth from "../../../hooks/useAuth";
import "../../../styleChat.scss";
import chat_socket from "../../../sockets/chat.sockets";
import {toast} from "react-toastify";
import useMute from "../../../hooks/useMute";

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

interface MembersProps{
	channels: Channel[];
	channel: Channel;
	isChannelClicked: boolean;
	selectedChannelId: number;
}

const MembersOptions = ({ channel, isChannelClicked, selectedChannelId }: MembersProps) => {
	const { auth }: any = useAuth();
	const [selectedMemberId, setSelectedMemberId] = useState<number>(0);
	const [selectedOption, setSelectedOption] = useState<string>("");
	const [membersList, setMembersList] = useState<User[]>([]);
	const effectRun = useRef(false);
	const Mute = useMute()

	useEffect(() =>
	{
	  	if (effectRun.current || process.env.NODE_ENV !== 'development')
		{
			chat_socket.emit('memberList', ({id: channel.id}),(res:User[]) =>{
			setMembersList(res);
			});
		}
		return (): void =>
		{
			effectRun.current = true
		}
	}, [membersList, channel.id]);

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
	}, []);


	const handleOptionChange = (event: React.ChangeEvent<HTMLSelectElement>) =>
	{
		setSelectedOption(event.target.value);
		const selectedOption = event.target.value;
		if (selectedOption === "kick")
		{
			handleKick(selectedMemberId);
		}
		else if (selectedOption === "ban")
		{
			handleBan(selectedMemberId, channel);
		}
		else if (selectedOption === "mute")
		{
			handleMute(selectedMemberId);
		}
		else if (selectedOption === "beadmin")
		{
			handleAdminAccess(selectedMemberId);
		}

		setSelectedOption("");
	};

	useEffect(() => {
		chat_socket.on("adminevent", (data) => {
			channel.adminId.push(auth?.id)
		})
	}, [auth?.id, channel.adminId])

	const handleKick = (memberId: number) =>
	{
		chat_socket.emit("kick",
		{
			from: channel.name,
			id_to_kick: memberId,
			is_admin: channel.adminId.includes(auth?.id),
			is_owner: channel.channelOwnerId === auth?.id
		}, (res: any) =>
		{
			if (res.success === true)
			{
				setMembersList((prevMembers) => prevMembers.filter((user) => user.id !== memberId));
			}
			toast(`${res.message}`);
		})
	};

	const handleBan = (memberId: number, channel: Channel) =>
	{
		chat_socket.emit("ban",
		{
			from: channel.name,
			id_to_ban: memberId,
			is_admin: channel.adminId.includes(auth?.id),
			is_owner: channel.channelOwnerId === auth?.id
		}, (res: any) =>
		{
			if (res.success === true)
			{
				channel.banlist.push(memberId);
			}
			toast(`${res.message}`);
		})
	};

	const handleMute = async (memberId: number) => {
		if (channel.muteList.includes(memberId))
			return
		const muted: boolean = await Mute(channel.name, memberId, channel.adminId.includes(auth?.id), channel.channelOwnerId === auth?.id)
		if (muted) {
			channel.muteList.push(memberId);
			setTimeout( async () => {
				const unmuted: boolean = await Mute(channel.name, memberId, channel.adminId.includes(auth?.id), channel.channelOwnerId === auth?.id)
				if (unmuted) {
					channel.muteList.splice(channel.muteList.indexOf(memberId), 1);
				}
			}, 5 * 60 * 1000, [channel.name, memberId, channel.adminId.includes(auth?.id), channel.channelOwnerId === auth?.id])
		}
	};

	const handleAdminAccess = (memberId: number) => {
		console.log(`Giving Admin Access to ${memberId}`);
		chat_socket.emit("admin", {
			from: channel.name,
			id_to_admin: memberId,
			is_admin: channel.adminId.includes(auth?.id),
			is_owner: channel.channelOwnerId === auth?.id}, (res: any) => {
			if (res.success === true) {
				channel.adminId.push(memberId);
			}
			toast(`${res.message}`);
		})
	};

	const filteredMembers = membersList && Array.isArray(membersList) ? membersList.filter((member) => member?.id !== auth?.id) : [];

	const renderMembers = (members: User[], channel: Channel) => {
	  if (channel.isMP === true) {
		return <div></div>;
	  } else if (!members || members.length === 0) {
		return <div>Aucun membre à afficher pour le moment.</div>;
	  }
	  return (
		<div className="memberList">
		  {filteredMembers.map((members) => (
			<div key={members.id}>
			  <span onClick={() => setSelectedMemberId(members.id)}>
				{members.nickname}
			  </span>
			  {selectedMemberId === members.id && (
				<div className="memberOptions">
					{channel.adminId.includes(auth?.id) && (
				  <select value={selectedOption} onChange={handleOptionChange}>
						<>
						<option value="">---</option>
						<option value="mute">Mute</option>
						<option value="kick">Kick</option>
						<option value="ban">Ban</option>
						<option value="beadmin">Admin Access</option>
					  </>
				  </select>
					)}
				</div>
			  )}
			</div>
		  ))}
		</div>
	  );
	};

	return (
	  <div>
		{renderMembers(membersList, channel)}
	  </div>
	);
  };

  export default MembersOptions;