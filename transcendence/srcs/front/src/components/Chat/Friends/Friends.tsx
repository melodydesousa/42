import { useState, useEffect, useRef } from "react";
import { useNavigate } from "react-router-dom";
import axios from "../../../api/axios";
import useAuth from "../../../hooks/useAuth";
import "./friends.css";
import { AllUsers } from "./AllUsers";
import { FaTimes } from "react-icons/fa";
import game_socket from "../../../sockets/game.socket";
import chat_socket from "../../../sockets/chat.sockets";
import { toast } from "react-toastify";

export interface UserFriend {
    id: number;
    email: string;
    avatar: string;
    nickname: string;
    isonline: boolean;
    adminOf: Channel[];
}

export interface Channel {
    createdAt: Date;
    id: number;
    name: string;
    privacy: string;
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

const Friends = ({ onChannelDataChange }: { onChannelDataChange: Function }) => {
    const [myMP, setMyMP] = useState([] as Channel[]);
    const [mpCreated, setMpCreated] = useState(true);
    const [friendMP, setFriendMP] = useState([] as Channel[]);
    const [friends, setFriends] = useState([] as UserFriend[]);
    const [selectedId, setSelectedId] = useState(0);
    const { auth }: any = useAuth();
    const effectRun = useRef(false);
    const [showPopUp, setPopUp] = useState(false);
    const [deleted, setDeleted] = useState(false);
    const [success, setSuccess] = useState(false);
    const [allSet, setAllSet] = useState(false);
    const [playingId, setPlayingId] = useState([] as number[]);
    const [onlineId, setOnlineId] = useState([] as number[]);
    const [tabBoolPlaying, setBoolPlaying] = useState([] as boolean[]);
    const [tabBoolOnline, setBoolOnline] = useState([] as boolean[]);
    const navigate = useNavigate()
    const [channels, setChannels] = useState([] as Channel[]);
    const [channelId, setChannelId] = useState<number>(0);
    const [friendId, setFriendId] = useState<number>(0);
    const [channelSelected, setChannelSelected] = useState<boolean>(false);

    const handleBlock = async (id: number) => {
        const response = await axios.post(`/users/blocked/${id}`, {
            id: id,
        }, {
            headers: {
                Authorization: `Bearer ${auth?.access_token}`,
            },
        });
        toast(response.data.message)
    }

    const handlePopUp = (friendId: number) => {
        setPopUp((prev: boolean) => !prev);
        setSelectedId(friendId);
    }

    const handleProfile = (id: number) => {
        navigate(`/profile/${id}`)
        setPopUp(false);
    }

    const handleNormalPlay = (id: number) => {
        setPopUp(false);
        game_socket.emit('inviteGame', { data: id, mode: 'NormalMode' })
    }

    const handleQuadriPlay = (id: number) => {
        setPopUp(false);
        game_socket.emit('inviteGame', { data: id, mode: 'QuadriMode' })
    }

    useEffect(() => {
        //console.log("channels", channels);
        // console.log("channel id", channelId);
        //console.log("channel selected ?", channelSelected);

        onChannelDataChange(channels, channelId, channelSelected);
    }, [channels])

    const handleMP = async (id: number) => {
       // console.log('HandleMP');
        let nameMP: string = "";
        if (auth.id > id) {
            nameMP = `mp_${auth.id}_${id}`;
        }
        else {
            nameMP = `mp_${id}_${auth.id}`;
        }
        const MyChannel = myMP.find((channel: Channel) => channel.name === nameMP);
        const FriendChannel = friendMP.find((channel: Channel) => channel.name === nameMP);
        if (MyChannel) {
            setChannels(myMP);
            setChannelId(MyChannel.id);
            setChannelSelected(true);
        }
        else if (FriendChannel) {
            setChannels(friendMP);
            setChannelId(FriendChannel.id);
            setChannelSelected(true);
        }
        else {
            const response = await axios.post("/chat/create", {
                name: nameMP,
                privacy: "public",
                isMP: true,
            }, {
                headers: {
                    Authorization: `Bearer ${auth?.access_token}`,
                },
            });
            await axios.patch(`/chat/update/admin/${response.data.id}`, {
                adminId: id,
            }, {
                headers: {
                    Authorization: `Bearer ${auth?.access_token}`,
                },
            })
                .then((res: any) => {
                    setMpCreated(true);
                    const tmp = [] as Channel[];
                    tmp.push(res.data);
                    setChannels(tmp);
                    setChannelId(res.data.id);
                    setChannelSelected(true);
                    chat_socket.emit('invite', {id: id, channelId: id, toast: false, channel: res.data.name});
                    chat_socket.emit("join", {channel: res.data.name}, (res: any) => {
				    })
                    // chat_socket.emit("join", { channel: res.data.name }, (res: any) => {
                    //     console.log("PARAM INVITE:", res.data.name, id, res.data.id)
                    //     chat_socket.emit("invite", {channel: res.data.name, id: id, toast: true, channelId: res.data.id}, (res: any) => {
                    //         console.log("INVITE OK", res)
                    //     })
                    // })
                })
                .catch((err: any) => {
                    console.log(err);
                })
        }
        setPopUp(false);

    };

    useEffect(() => { //  a la connection
        let friendsId: number[] = friends.map(friend => friend.id);
        chat_socket.emit('online', { id: friendsId }, (res: any) => {
            setOnlineId(res);
        })

    }, [friends])

    useEffect(() => {
        chat_socket.on("IamOnline", (data) => {
            setOnlineId((onlineId) => [...onlineId, data.id])
        })
    }, [])

    useEffect(() => {
        chat_socket.on("hasleft", (data) => {
            setOnlineId((onlineId) => onlineId.filter((id) => id !== data.id))
        })
    }, [])

    useEffect(() => {
        let tabBoolOnline: boolean[] = [];
        for (let i: number = 0; i < onlineId.length; i++) {
            for (let j: number = 0; j < friends.length; j++) {
                if (onlineId[i] === friends[j].id) {
                    tabBoolOnline[j] = true;
                }
            }
        }
        setBoolOnline(tabBoolOnline);
        if (onlineId)
            setAllSet(true);
    }, [friends, onlineId])

    useEffect(() => { // catch event
        game_socket.on('IsinGame', (data) => {
            setPlayingId(data);
        })
    }, [])

    useEffect(() => {
        game_socket.emit('InGameOrNot', (res: any) => {
            setPlayingId(res);
        })
    }, [])

    useEffect(() => {
        let tabBoolPlaying: boolean[] = [];
        for (let i: number = 0; i < playingId.length; i++) {
            for (let j: number = 0; j < friends.length; j++) {
                if (playingId[i] === friends[j].id) {
                    tabBoolPlaying[j] = true;
                }
            }
        }
        setBoolPlaying(tabBoolPlaying);
        if (playingId)
            setAllSet(true);
    }, [friends, playingId])

    const getMyMP = async () => {
        try {
            const response = await axios({
                method: 'GET',
                url: `chat/mp/${auth.id}`,
                headers: {
                    'Authorization': `Bearer ${auth?.access_token}`
                },
            })
                .then((response) => {
                    setMyMP(response.data);
                })
        } catch (error: any) {
            console.error(error.response?.data?.message);
        }
    };

    useEffect(() => {
        try {
            if (auth.id) {
                getMyMP();
            }
            const getFriendMP = async () => {
                try {
                    const res = await axios({
                        method: 'GET',
                        url: `chat/mp/${selectedId}`,
                        headers: {
                            'Authorization': `Bearer ${auth?.access_token}`
                        },
                    });
                    setFriendMP(res.data);
                } catch (error: any) {
                    console.error(error.response?.data?.message);
                }
            };
            if (selectedId !== 0) {
                getFriendMP();
            }
        } catch (error) {
            console.error("Error getting channel:", error);
        }
    }, [mpCreated, selectedId, onChannelDataChange]);

    const handleDeleteClick = async (friend: UserFriend) => {
        const id: number = friend.id;

        await axios.delete(`friends/delete/${id}`, {
            headers: {
                'Authorization': `Bearer ${auth?.access_token}`
            },
        }).then(() => {
            setFriends(friends.filter((friend) => friend.id !== id));
            setFriendId(friend.id);
            setDeleted(true);
            chat_socket.emit("UpFriendsList");
        })
            .catch((error: any) => {
                console.error(error.response?.data?.message);
            })
    }

    useEffect(() => {
        chat_socket.on("IamOnline", (data) => {
            chat_socket.emit('friends', { id: auth.id }, (res: any) => {
                if (res) {
                    setSuccess(true);
                    setFriends(res);
                }
            })
        })
    }, [auth.id])

    useEffect(() => {
        chat_socket.emit('friends', { id: auth.id }, (res: any) => {
            if (res) {
                setSuccess(true);
                setFriends(res);
            }
        })
    }, [auth.id, chat_socket])

    /*useEffect(() => {
        chat_socket.emit('UpFriendsList', { id: auth.id }, (res: any) => {
        })
        if (friendId > 0)
            chat_socket.emit('UpFriendsList', { id: friendId }, (res: any) => {
            })
    }, [deleted])*/

    useEffect(() => {
        let isMounted: boolean = true
        if (effectRun.current || process.env.NODE_ENV !== 'development') {
            chat_socket.on('RefreshFriendsList', (data: UserFriend[]) => {
                chat_socket.emit('friends', { id: auth.id }, (res: any) => {
                    if (res) {
                        setSuccess(true);
                        setFriends(res);
                    }
                })
            });

        }
        return (): void => {
            isMounted = false
            effectRun.current = true
        }
    }, []);

    return (
        allSet === true ?
            (
                <>
                    <div className="chat">
                        <h2>Friends</h2>
                        {friends.length === 0 ?
                            (<div className="item">
                                No friends yet
                            </div>)
                            : <>
                                {
                                    friends && friends.map((friend, index) => (
                                        <div className="user-friends" key={index}>
                                            <div className="user-info-container">
                                                <img className="img-avatar" src={friend.avatar} alt="avatar" />
                                                <div className={tabBoolOnline[index] === true ? 'cercle-green' : 'cercle-grey'}></div>
                                            </div>
                                            <div className="user-info">
                                                <a onClick={() => handlePopUp(friend.id)}>{friend.nickname} {tabBoolPlaying[index]}</a>
                                                {
                                                    tabBoolPlaying[index] === true ?
                                                        (<div className="text-ingame">is now playing</div>)
                                                        :
                                                        <></>
                                                }
                                                <>
                                                    {showPopUp && selectedId === friend.id &&
                                                        <div className="user-popup">
                                                            <div className="user-popup-inner">
                                                                <div className="btn-add" onClick={() => handleNormalPlay(friend.id)}>Invite to play: Normal mode</div>
                                                                <div className="btn-add" onClick={() => handleQuadriPlay(friend.id)}>Invite to play: <span style={{ color: 'red' }}>Qua</span><span style={{ color: 'yellow' }}>dri</span><span style={{ color: 'green' }}>col</span><span style={{ color: 'blue' }}>or</span> mode</div>
                                                                <div className="btn-add" onClick={() => handleProfile(friend.id)}>View profile</div>
                                                                <div className="btn-add" onClick={() => handleMP(friend.id)} >Send a message</div>
                                                                <div className="btn-add" onClick={() => handleBlock(friend.id)}>Block</div>

                                                            </div>
                                                        </div>
                                                    }
                                                </>
                                            </div>
                                            <FaTimes style={{ cursor: "pointer", float: "right", color: "red", alignSelf: "flex-end", alignItems: "center" }}
                                                onClick={() => handleDeleteClick(friend)} />
                                        </div>
                                    ))
                                }
                            </>
                        }
                    </div>
                    <hr style={{ color: "white" }} />
                    {success ?
                        < AllUsers friends={friends} setFriends={setFriends} deleted={deleted} onChannelDataChange={onChannelDataChange} />
                        : <></>
                    }

                </>
            )
            :
            <></>
    )
}

export default Friends;