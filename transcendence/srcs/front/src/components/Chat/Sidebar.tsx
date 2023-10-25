import React from "react";
import '../../styleChat.scss'
import Search from "./Search";
import { Channel } from "./Channel/ChanelBar";

export interface DataChange{
	selectedChannelId: number;
	isChannelClicked: boolean
}

export interface ChanelBarProps {
    onChannelDataChange: (channels: Channel[], selectedChannelId: number, isChannelClicked: boolean) => void;
}

const Sidebar = ({onChannelDataChange }: ChanelBarProps) =>
{
    return (
        <div className='sidebar'>
            <Search onChannelDataChange={onChannelDataChange}/>
            {/* <ChanelBar /> */}
        </div>
    );
};

export  default Sidebar;