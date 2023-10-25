import React, { useState } from 'react';
import CreateChannel from "./Channel/CreateChanel";
import ChanelBar from "./Channel/ChanelBar";
import Friends from "./Friends/Friends";
import { Channel } from "./Channel/ChanelBar";


export interface ChanelBarProps {
  onChannelDataChange: (channels: Channel[], selectedChannelId: number, isChannelClicked: boolean) => void;

}
export default function Search({onChannelDataChange }: ChanelBarProps) {
  const [showCreateChannel, setShowCreateChannel] = useState(false);
  const [key, setKey] = useState(0);
 
  const handleCreateChannelClick = () => {
    setShowCreateChannel(true);
  };

  const handleCreateChannelSuccess = () => {
    setKey((prevKey) => prevKey + 1);
    setShowCreateChannel(false)
    
    
  };

  return (
    <>
      <div className='hello'>
      <h2>Channels</h2>
        <button onClick={handleCreateChannelClick}>+ Create Channel
        </button>
      <div className='user'>
      <ChanelBar key={key} channelCreated={true} onChannelDataChange={onChannelDataChange}/>
      {showCreateChannel && (
        <CreateChannel onSuccess={handleCreateChannelSuccess} />
      )}
      </div>
      <div className='user'>
        <Friends onChannelDataChange={onChannelDataChange}/>
      </div>
      </div>
    </>
  );
}