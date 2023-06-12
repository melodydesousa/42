import React from "react";
import Sidebar from "../components/Chat/Sidebar";
import Chat from "../components/Chat/Chat";

const ChatHome = () => 
{
    return (
        <div className='home'>
            <div className='container01'>
            <Sidebar/>
            <Chat/>
            </div>
        </div>
    )
}

export default ChatHome