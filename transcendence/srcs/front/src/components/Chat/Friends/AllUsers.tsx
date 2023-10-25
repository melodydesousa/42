import { useState, useEffect } from "react";
import axios from "../../../api/axios";
import useAuth from "../../../hooks/useAuth";
import "./friends.css";
import { UserFriend } from "./Friends";
import { Options } from "./Options";
import chat_socket from "../../../sockets/chat.sockets";

export const AllUsers = ({ friends, setFriends, deleted, onChannelDataChange}: { friends: UserFriend[], setFriends: Function, deleted: boolean, onChannelDataChange: Function}) => {
    const [me, setMe] = useState({} as UserFriend);
    const [users, setUsers] = useState([] as UserFriend[]);
    const [success, setSuccess] = useState(false);
    const [friend, setFriend] = useState({} as UserFriend);
    const [selectedNickname, setSelectedNickname] = useState('');
    const { auth }: any = useAuth();

    const handlePopUp = (friend: UserFriend) => {
        setSuccess(!success);
        setSelectedNickname(friend.nickname);
        const _friend: UserFriend = { avatar: friend.avatar, id: friend.id, nickname: friend.nickname, isonline: friend.isonline, email: friend.email, adminOf: friend.adminOf };
        setFriend(_friend);
    }

    useEffect(() => {
        chat_socket.on("IamOnline", (data) => {
            chat_socket.emit('allUsers', (res:any) => 
            {
                if (res) {
                    const results = res.filter((user: UserFriend) => {
                        return user && user.nickname && user.nickname !== me.nickname
                    });
                    const filteredResults = results.filter((user: UserFriend) => {
                        const isFriend = friends.some((friend: UserFriend) => friend.nickname === user.nickname);
                        return !isFriend;
                    });
                    setUsers(filteredResults);
                }
            })
        })
    }, [])

    useEffect(() => {
        let isMounted: boolean = true
        const controller: AbortController = new AbortController()

        const getMe = async () => {
            await axios({
                method: 'GET',
                url: 'users/me',
                headers: {
                    'Authorization': `Bearer ${auth?.access_token}`
                },
            }).then((res: any) => {
                setMe(res.data);
            }).catch((error: any) => {
                console.error(error.response?.data?.message);
            })
        }
        getMe();
        chat_socket.emit('allUsers', (res:any) => 
        {
            if (res) {
                const results = res.filter((user: UserFriend) => {
                    return user && user.nickname && user.nickname !== me.nickname
                });
                const filteredResults = results.filter((user: UserFriend) => {
                    const isFriend = friends.some((friend: UserFriend) => friend.nickname === user.nickname);
                    return !isFriend;
                });
                setUsers(filteredResults);
            }
        })
        return () => {
            isMounted = false
            controller.abort()
        }
    }, [deleted, friends, auth?.access_token, me.nickname])

    return (
        <>
            <div className="chat">
                <h2>All Users</h2>
                {users.length === 0 ? (
                    <div className="item">No users found</div>
                ) : (
                    <>
                        {users.map((user, index) =>
                            user.nickname !== me.nickname ? (
                                <div className="user-friends" key={index}>
                                    <img className="img-avatar" src={user.avatar} alt="" />
                                    <div className="user-info">
                                        <a onClick={() => handlePopUp(user)}>{user.nickname}</a>
                                        {success && selectedNickname === user.nickname && (
                                            <div className="user-popup">
                                                <Options setSuccess={setSuccess} friend={friend} friends={friends} users={users} setFriends={setFriends} setUsers={setUsers} me={me} onChannelDataChange={onChannelDataChange}/>
                                            </div>
                                        )}
                                    </div>
                                </div>
                            ) : null
                        )}
                    </>
                )}
            </div>
        </>
    );
}