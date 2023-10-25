import React, { createContext, useState } from "react";

const ChannelContext = createContext({})

export const ChannelProvider = ({ children }: { children: React.ReactNode }) => {
    const [Channel, setChannel] = useState<any>({state: false})


    return (
        <ChannelContext.Provider value={{Channel, setChannel}}>
            {children}
        </ChannelContext.Provider>
    )
}

export default ChannelContext