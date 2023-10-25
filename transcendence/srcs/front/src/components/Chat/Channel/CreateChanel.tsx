import axios from "axios";
import { useState, useEffect, useRef } from "react";
import useAuth from "../../../hooks/useAuth";
import "../../../styleChat.scss";
import chat_socket from "../../../sockets/chat.sockets";

axios.defaults.timeout = 5000;

export interface CreateChannelProps {
  onSuccess: () => void;
}

export default function CreateChannel({ onSuccess }: CreateChannelProps) 
{
	const userRef = useRef<HTMLInputElement | null>(null);
	const [password, setPassword] = useState("");
	const [showForm, setShowForm] = useState(true);
	const [name, setName] = useState("");
	const [isPrivate, setIsPrivate] = useState("public");
	const { auth }: any = useAuth();

	useEffect(() => 
	{
		if (userRef.current) 
		{
			userRef.current.focus();
		}
	}, []);

	const closeForm = () => 
	{
		setShowForm(false);
		handleSuccess();
	};

	const handleSuccess = () => 
	{
		if (typeof onSuccess === "function") 
		{
			onSuccess();
		}
	};

	const handleSubmit = async (e: any): Promise<any> => 
	{
		e.preventDefault();
		try 
		{
			await axios.post("/chat/create", 
			{
				name: name,
				privacy: isPrivate,
				mdpHash: password,
			}, 
			{
				headers: 
				{
					Authorization: `Bearer ${auth?.access_token}`,
				},

			}).then(()=>
			{
				chat_socket.emit('CreateChannel')}
			);
			handleSuccess();
		} catch (error: any)
		{
			console.error("Error creating channel:", error.response?.data?.message);
		}
	};

  return (
	<>
		{showForm &&
		<div className="formContainerChanel">
		  <div className="formWrapperChanel">
			<form onSubmit={handleSubmit}>
			<button className="close_popup" onClick={closeForm}>X</button>
			  <label htmlFor="nickname">
				<input
				  type="text"
				  id="nickname"
				  ref={userRef}
				  value={name}
				  onChange={(e) => setName(e.target.value)}
				  required
				  placeholder="name"
				/>
			  </label>
			  <div className="checkboxContainer">
				<label htmlFor="isPrivate">
				  <input
					type="checkbox"
					id="isPrivate"
					checked={isPrivate === "private"}
					onChange={(e) =>
					  setIsPrivate(e.target.checked ? "private" : "public")
					}
				  />
				  Private
				</label>
				<label htmlFor="isProtected">
				  <input
					type="checkbox"
					id="isProtected"
					checked={isPrivate === "protected"}
					onChange={(e) =>
					  setIsPrivate(e.target.checked ? "protected" : "public")
					}
				  />
				  Protected
				</label>
				{isPrivate === "protected" && (
				  <label htmlFor="password">
					<input
					  type="password"
					  id="password"
					  value={password}
					  onChange={(e) => setPassword(e.target.value)}
					  required
					  placeholder="Password"
					/>
				  </label>
				)}
			  </div>
			  <button className="buttonCreate" type="submit" value="Submit">
				Create
			  </button>
			</form>
		  </div>
		</div>
	}
	</>
  );
}
