import React from "react";

const Chats = () =>
{
    return(
        <div className='chats'>
            <div className="userChat">
                <img src="https://cdn.intra.42.fr/users/666328edb8a6db63cd235ab5875a11d9/cfontain.jpg" 
                alt=""
                />
                <div className="userChatInfo">
                  	<span>Clement</span>
                    <p>Hello</p>
                </div>
            </div>
            <div className="userChat">
                <img src="https://cdn.intra.42.fr/users/3d5490f68f02f6c146c51f2dd0bbac69/mede-sou.JPG" 
                alt=""
                />
                <div className="userChatInfo">
                  	<span>Melody</span>
                    <p>Hello</p>
                </div>
            </div>
            <div className="userChat">
                <img src="https://cdn.intra.42.fr/users/f6e6081e9a015a9d004f28cda12cc6d2/tnoulens.JPG" 
                alt=""
                />
                <div className="userChatInfo">
                  	<span>Thibault</span>
                    <p>Hello</p>
                </div>
            </div>
        </div>
    )
}

export default Chats