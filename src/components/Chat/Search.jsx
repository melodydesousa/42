import React from "react";

const Search = () =>
{
    return (
        <div className='search'>
            <div className="searchForm">
                <input type="text" placeholder='Find a user'/>
            </div>
            <div className="userChat">
                <img src="https://cdn.intra.42.fr/users/321334f85f1aa733c0ba0df06e67b3d7/amanasse.JPG" alt=""/>
                <div className="userChatInfo">
                  	<span>Clement</span>
                </div>
            </div>
        </div>
    )
}

export default Search