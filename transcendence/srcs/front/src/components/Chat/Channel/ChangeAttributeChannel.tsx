import React, { useState } from "react";
import axios from "axios";
import { Channel } from "./ChanelData";
import useAuth from "../../../hooks/useAuth";
import chat_socket from "../../../sockets/chat.sockets";

interface ChangeAttributeChannelProps {
  channel: Channel; 
  channels: Channel[]; 
  channelId: number; 
  attributeType: string; 
  onClose: () => void;
}

	const ChangeAttributeChannel: React.FC<ChangeAttributeChannelProps> = ({ channel, channels, channelId, attributeType, onClose }) => {
	const [newAttribute, setNewAttribute] = useState<string>(attributeType);
	const [password, setPassword] = useState('');
	const { auth }: any = useAuth();

  
  
	const handleSubmit = async (e: React.FormEvent) => 
	{
		e.preventDefault();
		if (channel.privacy === newAttribute && !(channel.privacy === 'protected' && newAttribute === 'protected')) 
		{
			onClose();
			return;
		}
		try 
		{
			await axios.patch(`/chat/update/privacy/${channel.id}`, { privacy: newAttribute, mdpHash: password },
			{
                headers: {
                    Authorization: `Bearer ${auth?.access_token}`,
                },
            })
			.then (() => {
				chat_socket.emit('CreateChannel')
				onClose();
			});
		}
		catch (error) 
		{
			console.error("Erreur lors de la mise à jour des attributs du canal:", error);
		}
	}


  const isButtonDisabled = newAttribute === 'protected' && password.trim() === '';
  
  return (
	<div className="joinButton">
	  <h3>Modifier la Room</h3>
	  <form onSubmit={handleSubmit}>
		<div className="form-group">
		  <label htmlFor="newAttribute"></label>
		  <select
			id="newAttribute"
			name="newAttribute"
			value={newAttribute}
			onChange={(e) => setNewAttribute(e.target.value)}
		  >
			<option value="protected">Protected</option>
			<option value="private">Private</option>
			<option value="public">Public</option>
		  </select>
		</div>
		{newAttribute === 'protected' && (
		  <div className="form-group">
			<label htmlFor="password">New Password</label>
			<input
			  type="password"
			  id="password"
			  name="password"
			  value={password}
			  onChange={(e) => setPassword(e.target.value)}
			/>
		  </div>
		)}
		<div className="form-group">
		  <button type="submit" disabled={isButtonDisabled}>
			Changes
		  </button>
		  <button type="button" onClick={onClose}>
			Close
		  </button>
		</div>
	  </form>
	</div>
  );
};

export default ChangeAttributeChannel;