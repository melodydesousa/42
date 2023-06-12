import React from "react";

const Navbar = () =>
{
    return (
        <div className='navbar'>
            <span className='logo'>Trascendence Chat</span>
            <div className='user'>
                <img src="https://cdn.intra.42.fr/users/321334f85f1aa733c0ba0df06e67b3d7/amanasse.JPG" alt=""/>
                <span>Adrian</span>
                <button>logout</button>
            </div>
        </div>
    )
}

export default Navbar