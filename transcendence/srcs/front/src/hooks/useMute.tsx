import chat_socket from "../sockets/chat.sockets";
import { toast } from "react-toastify";

const useMute = () => {
	const muter = async (channelName: string, id_to_mute: number, is_admin: boolean, is_owner: boolean): Promise<boolean> => {
		return new Promise<boolean>((resolve) => {
			chat_socket.emit("mute", {
				muted_from: channelName,
				id_to_mute: id_to_mute,
				is_admin: is_admin,
				is_owner: is_owner
			}, (res: any) => {
				if (res.success === true) {
					toast(`${res.message}`);
					resolve(true);
				} else {
					toast(`${res.message}`);
					resolve(false);
				}
			});
		});
	};
	return muter;
};

export default useMute;

