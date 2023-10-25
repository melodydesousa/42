import axios from "../../../api/axios";
import { useEffect, useState, useRef } from "react";
import { useNavigate } from "react-router-dom";
import useAuth from "../../../hooks/useAuth";
import "./friends.css";
import { UserFriend } from "./Friends";
import { Channel } from "../Channel/ChanelBar";
import chat_socket from '../../../sockets/chat.sockets';
import game_socket from "../../../sockets/game.socket";
import { toast } from "react-toastify";

export const Options = ({ setSuccess, friend, friends, users, setFriends, setUsers, me, onChannelDataChange }: { setSuccess: Function, friend: UserFriend, friends: UserFriend[], users: UserFriend[], setFriends: Function, setUsers: Function, me: UserFriend, onChannelDataChange: Function }) => {
    const { auth }: any = useAuth();
    const [showPopup, setShowPopup] = useState(true);
    const [mpCreated, setMpCreated] = useState(true);
    const [myMP, setMyMP] = useState([] as Channel[]);
    const [friendMP, setFriendMP] = useState([] as Channel[]);
    const [channels, setChannels] = useState([] as Channel[]);
    const [channelId, setChannelId] = useState<number>(0);
    const [channelSelected, setChannelSelected] = useState<boolean>(false);
    const effectRun = useRef(false);
    const navigate = useNavigate();

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

    const handleAdd = async () => {
        await axios.post("friends/add", {
            friendId: friend.id,
            nickname: friend.nickname,
            user: {
                userId: auth?.id,
            }
        },
        {
            headers: {
                'Authorization': `Bearer ${auth?.access_token}`
            },
        })
        .then((res: any) => {
            setShowPopup(false);
            const updateDataFriend = async () => {
                await axios.get(`users/${res.data.friendId}`, {
                    headers:
                    {
                        'Authorization': `Bearer ${auth?.access_token}`
                    },
                })
                .then((res: any) => {
                    const updatedFriend = { id: res.data.id, nickname: res.data.nickname, avatar: res.data.avatar };
                    setFriends([...friends, updatedFriend]);
                   // console.log("auth id ", auth.id);
                    //chat_socket.emit("UpallUsers");
                   // chat_socket.emit("UpFriendsList");
                })
                .catch((err: any) => {
                    console.log(err);
                })
            }
            updateDataFriend();
            const newUsersList = users.filter((user) => user.id !== friend.id);
            setUsers(newUsersList);
            setSuccess(false);
        })
            .then(async () => {
                await axios.post(`friends/${friend.id}`, {
                    friendId: me.id,
                    nickname: me.nickname,
                    user: {
                        id: friend.id,
                    }
                },
                {
                    headers: {
                        'Authorization': `Bearer ${auth?.access_token}`
                    },
                })

            }).then( async () =>
            {
                chat_socket.emit("UpFriendsList");
            })
            .catch((err: any) => {
                console.log(err);
            })
            setShowPopup(false);
    }

    const handleProfile = (id: number) => {
        setShowPopup(false);
        navigate(`/profile/${id}`);
    }

    const handleNormalPlay = () => {
        setShowPopup(false);
        game_socket.emit('inviteGame', {data: friend.id, mode: 'NormalMode'})
    }

    const handleQuadriPlay = () => {
        setShowPopup(false);
        game_socket.emit('inviteGame', {data: friend.id, mode: 'QuadriMode'})
    }

    useEffect(() => {
        try {
            const getMyMP = async () => {
                try {
                    const response = await axios({
                        method: 'GET',
                        url: `chat/mp/${me.id}`,
                        headers: {
                            'Authorization': `Bearer ${auth?.access_token}`
                        },
                    });
                    setMyMP(response.data);
                } catch (error: any) {
                    console.error(error.response?.data?.message);
                }
            };
            if (me.id) {
                getMyMP();
            }
            const getFriendMP = async () => {
                try {
                    const res = await axios({
                        method: 'GET',
                        url: `chat/mp/${friend.id}`,
                        headers: {
                            'Authorization': `Bearer ${auth?.access_token}`
                        },
                    });
                    setFriendMP(res.data);
                } catch (error: any) {
                    console.error(error.response?.data?.message);
                }
            };
            if (friend.id) {
                getFriendMP();
            }
        } catch (error) {
            console.error("Error getting channel:", error);
        }
    }, [mpCreated, friend.id, me.id, onChannelDataChange]);

    useEffect(() => {
        // console.log("channels", channels);
        // console.log("channel id", channelId);
        // console.log("channel selected ?", channelSelected);
        onChannelDataChange(channels, channelId, channelSelected);
    }, [channelId, channelSelected, channels])

    const handleMP = async (id: number) => {
        let nameMP: string = "";
        if (me.id > id) {
            nameMP = `mp_${me.id}_${id}`;
        }
        else {
            nameMP = `mp_${id}_${me.id}`;
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
                chat_socket.emit('invite', {id: id, channelId: id, toast: false, channel: res.data.name});
                chat_socket.emit("join", {channel: res.data.name}, (res: any) => {
				})
                const tmp =  [] as Channel[];
                tmp.push(res.data);
                setChannels(tmp);
                setChannelId(res.data.id);
                setChannelSelected(true);
            })
            .catch((err: any) => {
                console.log(err);
            })
        }
        setShowPopup(false);

    };

    return (
        <>
            {showPopup &&
                    <div className="user-popup-inner">
                        <div className="btn-add" onClick={handleAdd}>Add as a friend</div>
                        <div className="btn-add" onClick={handleNormalPlay}>Invite to play: Normal mode</div>
                        <div className="btn-add" onClick={handleQuadriPlay}>Invite to play: <span style={{color: 'red'}}>Qua</span><span style={{color: 'yellow'}}>dri</span><span style={{color: 'green'}}>col</span><span style={{color: 'blue'}}>or</span> mode</div>
                        <div className="btn-add" onClick={() => handleMP(friend.id)}>Send a message</div>
                        <div className="btn-add" onClick={() => handleProfile(friend.id)}>View profile</div>
                        <div className="btn-add" onClick={() => handleBlock(friend.id)}>Block</div>
                    </div>

                }
        </>
    )
}
