import { io} from 'socket.io-client';
import { toast } from 'react-toastify';

	//const {auth}: any = useAuth();
const game_socket = io("",
	{
		withCredentials: true,
		reconnectionDelayMax: Infinity,
		path: "/game",
		autoConnect: false,
	})

game_socket.on('sendGameInvitation', ({friend:friend, mode:mode}) =>
	{
		const notify = () => {
		toast(`You are invited to play a ${mode} game`, {
				onClick: () => {
				game_socket.emit('acceptGameInvitation', {friend:friend, mode:mode});
		}})}
		notify();
})




game_socket.on('AlreadyInGame', (friend) =>
	{
		const notify = () => {
			toast("You or your opponent are already in a Game !", {
				})}
		notify();
	})

game_socket.on('OpponentHasLeft', () =>
	{
		const notify = () =>
		{
			toast("Your opponent is disconnected", {
		})}
		notify();
	});

	

export default game_socket
