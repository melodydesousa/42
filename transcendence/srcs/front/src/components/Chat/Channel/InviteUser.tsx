import React, { useEffect, useRef, useState } from "react";
import useAuth from "../../../hooks/useAuth";
import "../../../styleChat.scss";
import chat_socket from "../../../sockets/chat.sockets";
import axios from "axios";
const Add = require('../../../img/add.png');

export interface Users {
    id: number;
    nickname: string;
}

interface Channel {
	createdAt: Date;
	id: number;
	name: string;
	privacy: string;
	channelOwnerId: number;
	isMP: boolean;
	adminId: number[];
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

interface InviteProps{
	channel: Channel;
}

const InviteUser = ({channel}: InviteProps) => {
    const { auth }: any = useAuth();
    const [selectedOption, setSelectedOption] = useState<string>("");
    const [allUsers, setAllUsers] = useState<Users[]>([]);
    const effectRun = useRef(false);
    const [showDropdown, setShowDropdown] = useState(false);

    const handleSearchUser = (event: React.MouseEvent<HTMLButtonElement, MouseEvent>) => 
    {
        setShowDropdown(true);
    };

    const handleSelectUserOnClick = (event: React.MouseEvent<HTMLSelectElement, MouseEvent>) =>
    {
        const selectedUserId = event.target;
        chat_socket.emit('inviteRoom', { data: Number(selectedUserId), channel: channel.name , channelId: channel.id});
        chat_socket.emit('allUsers', (res : any) =>
        {
            setAllUsers(res);
        })
        setSelectedOption("");
    }

    const handleSelectUser = (event: React.ChangeEvent<HTMLSelectElement>) => 
    {
        const selectedUserId = event.target.value;
        chat_socket.emit('inviteRoom', { data: Number(selectedUserId), channel: channel.name , channelId: channel.id});
        chat_socket.emit('allUsers', (res : any) =>
        {
            setAllUsers(res);
        })
        setSelectedOption("");
        setShowDropdown(false);
    };

    useEffect(() => 
    {
        const controller: AbortController = new AbortController();
        if (effectRun.current || process.env.NODE_ENV !== 'development') {
            const getAllData = async () => {
                try {
                    const response = await axios.get('users', {
                        headers: {
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

        return () => {
            controller.abort();
            effectRun.current = true;
        };
    }, [auth?.access_token]);

    return (
        <div>
            {showDropdown ? (

                <select value={selectedOption} onChange={handleSelectUser} onClick={handleSelectUserOnClick}>
                <option value="">--USERS--</option>
                    {allUsers.map((user) => (
                        auth.id !== user.id ? (
                            <option key={user.id} value={user.id} data-nickname={user.nickname}>
                                {user.nickname}
                            </option>
                        ) : null
                ))}
                </select>
            ) : (
                <button onClick={handleSearchUser}>
                    <img src={Add} alt="Add User" />
                </button>
            )}
        </div>
    );
};

export default InviteUser;