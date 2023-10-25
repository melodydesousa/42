import { io } from "socket.io-client";
import { toast  } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
import {string} from "prop-types";

const URL = "";
// https://www.npmjs.com/package/react-toastify
const notify = (res: string) => toast(res);

const chat_socket = io(URL,
	{
		withCredentials: true,
		reconnectionDelayMax: Infinity,
		path: "/messages",
		autoConnect: false}
);

chat_socket.on("disconnect", (data) => {
	console.log("disconnected")
})

chat_socket.on("IamOnline", (data: any) => {
	// console.log(`${data.id} has arrived`)
})

chat_socket.on("hasleft", (data: {id: number}) => {
	// console.log(`${data.id} has left`)
})

chat_socket.on("message", (data: any) => {
	if (window.location.pathname !== "/chat") {
		if (data.content) {
			notify(`${data.nicknameSender}: ${data.content}`)
		}
	}
	else {
		if (data instanceof string)
			notify(data as string)
	}
})

chat_socket.on("joinNotification", (res: string) => {
	notify(res)
})

chat_socket.on("AcceptInviteRoom", (data:any) => {
    const notify = () => {
		toast(`You are invited to join ${data.channel}` , {
				onClick: () => {
					chat_socket.emit('invite', ({id: data.id, channel:data.channel, channelId: data.channelId, toast: true}), (res:any) =>{
					//console.log(res);
					});
				}
		})
	}
	notify();
})



export default chat_socket;
