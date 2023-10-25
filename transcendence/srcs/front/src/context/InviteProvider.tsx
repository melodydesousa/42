import React, { createContext, useState } from "react";

const InviteContext = createContext({})

export const InviteProvider = ({ children }: { children: React.ReactNode }) => {
    const [Invite, setInvite] = useState<any>({state: false})


    return (
        <InviteContext.Provider value={{Invite, setInvite}}>
            {children}
        </InviteContext.Provider>
    )
}

export default InviteContext