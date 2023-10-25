import { useNavigate } from "react-router-dom";

const Unauthorized = () => {
	const navigate = useNavigate()
	const goback = () => navigate(-1)
	return (
		<section>
			<h1>Unauthorized</h1>
			<br/>
			<p>
				You do not have access to this page
			</p>
			<div className="flexGrow">
				<button onClick={goback}>Go back</button>
			</div>
		</section>
	)
}

export default Unauthorized
