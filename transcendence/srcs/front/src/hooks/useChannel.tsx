import { useContext } from "react";
import ChannelContext from "../context/ChannelProvider";

const useChannel = () => {
	return useContext(ChannelContext)
}

export default useChannel