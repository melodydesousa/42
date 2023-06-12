import React from "react";
const Logo42 = require('../img/42_Logo.png');

function Register()
{
    return (
        <div className="formContainer">
            <div className="formWrapper">
                <form>
                    <center><img src={Logo42} width="40px" height="40px" alt=""/></center>
                    <button>Connect with 42</button>
                </form>
            </div>
        </div>
    )
}

export default Register;
