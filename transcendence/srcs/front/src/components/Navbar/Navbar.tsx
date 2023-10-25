import { Nav, NavLink, NavLinkCol, NavBtnCol, NavMenuCol, NavCol, NavLinkSettings, NavBtnLink, NavMenu, NavBtn, ImageContainer, NavBtnLinkCol } from './NavbarElements';
import { useNavigate, useLocation } from "react-router-dom";
import { useState, useEffect, useRef } from "react";
import useLogout from "../../hooks/useLogout";
import useAuth from "../../hooks/useAuth";
import axios from "axios";
import burger from './hamburger.png'
import { Users } from "../Users"

const Navbar = () => {
  const { auth }: any = useAuth();
  const [MyData, setMyData] = useState({} as Users);
  const navigate = useNavigate()
  const location = useLocation()
  const logout = useLogout()
  const effectRun = useRef(false);
  const [isMenuOpen, setIsMenuOpen] = useState(false);

  const signout = async () => {
    await logout()
    navigate('/login')
  }

  const toggleMenu = () => {
    setIsMenuOpen(!isMenuOpen);
  };

  useEffect(() => {
    let isMounted: boolean = true
    const controller: AbortController = new AbortController()

    if (effectRun.current || process.env.NODE_ENV !== 'development') {
      const getMyData = async () => {
			const host = process.env.REACT_APP_HOST
      await axios({
          method: 'GET',
          url: `http://${host}:3000/users/me`,
          headers: {
            'Authorization': `Bearer ${auth?.access_token}`
          },
        }).then((res) => {
          setMyData(res.data);
        }).catch((error) => {
          console.error(error.response?.data?.message);
        })
      }
      getMyData()
    }
    return () => {
      isMounted = false
      controller.abort()
      effectRun.current = true
    }
  }, [auth, navigate, location])


  return (
    <>
      <Nav style={
        { overflow: 'hidden', }
      }>
        <NavMenu >
          <img src={MyData.avatar} alt="avatar" height="30" width="30" style={{ objectFit: 'cover' }} />
          <NavLinkSettings to='/settings' style={{
            fontWeight: 'bold',
            paddingLeft: 10,
          }} >
            {MyData.nickname}
          </NavLinkSettings>
          <NavLink to='/' >
            Home
          </NavLink>
          <NavLink to={`/profile/${auth.id}`} >
            My Profile
          </NavLink>
          <NavLink to='/chat' >
            Chat
          </NavLink>
          <NavLink to='/lobby' >
            Game
          </NavLink>
        </NavMenu>
        <NavBtn>
          <NavBtnLink to='#' onClick={signout}>Sign Out</NavBtnLink>
        </NavBtn>
      </Nav>

      <ImageContainer onClick={toggleMenu}>
        <img src={burger} alt="burger" />
      </ImageContainer>
      {
        isMenuOpen && (
          <NavCol style={{ flexDirection: 'column' }}>
            <NavMenuCol style={{ flexDirection: 'column' }}>
              <NavLinkCol to='/' >
                Home
              </NavLinkCol>
              <NavLinkCol to='/chat' >
                Chat
              </NavLinkCol>
              <NavLinkCol to='/lobby' >
                Game
              </NavLinkCol>
              <NavBtnCol>
                <NavBtnLinkCol to='#' onClick={signout}>Sign Out</NavBtnLinkCol>
              </NavBtnCol>
            </NavMenuCol>
          </NavCol>
        )}
    </>
  );
};

export default Navbar;
