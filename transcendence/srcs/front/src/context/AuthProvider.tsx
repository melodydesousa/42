import React, { createContext, useState } from "react";

const AuthContext = createContext({})

export const AuthProvider = ({ children }: { children: React.ReactNode }) => {
    const [persist, setPersist] = useState(
        JSON.parse(localStorage.getItem("persist") || "false"))
    const [auth, setAuth] = useState<any>({
        user: "",
        access_token: "",
        nickname: "",
        id: ""
    })

    return (
        <AuthContext.Provider value={{ auth, setAuth, persist, setPersist}}>
            {children}
        </AuthContext.Provider>
    )
}

export default AuthContext
