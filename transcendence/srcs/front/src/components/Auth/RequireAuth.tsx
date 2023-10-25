import { useLocation, Navigate, Outlet } from "react-router-dom";
import useAuth from "../../hooks/useAuth";

const RequireAuth = () => {
	const {auth}:any = useAuth()
	const location = useLocation()
	const from = location.state?.from?.pathname || "/"
	return (
		auth?.user || auth?.access_token
			? <Outlet />
			: <Navigate to="/login" state={{from: location}} replace/>
	)
}

export default RequireAuth
