import { Link } from "react-router-dom";

const Missing = () => {
	return (
		<article style={{ padding: "100px" }}>
			<h1>Oops</h1>
			<p>Page not found</p>
			<div >
				<Link to="/">Homepage</Link>
			</div>
		</article>
	)
}

export default Missing
