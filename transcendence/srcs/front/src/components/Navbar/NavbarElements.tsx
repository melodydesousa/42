import { NavLink as Link } from 'react-router-dom';
import styled from 'styled-components';

export const Nav = styled.nav`
background: #ffffff;
height: 65px;
display: flex;
justify-content: space-between;
padding: 1rem;
z-index: 12;
overflow: hidden;
`;

export const NavCol = styled.nav`
background: #ffffff;
height: 115px;
display: flex;
justify-content: space-between;
padding: 1rem;
z-index: 12;
overflow: hidden;
`;

export const NavLink = styled(Link)`
color: #262773;
display: flex;
align-items: center;
text-decoration: none;
padding: 0 2rem;
height: 100%;
cursor: pointer;
&.active {
	color: #262773;
}
@media screen and (max-width: 650px) {
	display: none;
&:hover {
	transition: all 0.2s ease-in-out;
	background: #fff;
	color: #262773;
}}
`;

export const NavLinkCol = styled(Link)`
	color: #262773;
	align-items: center;
	text-decoration: none;
	padding: 0 2rem;
	height: 100%;
	cursor: pointer;
	&.active {
		color: #262773;
	}
&:hover {
	transition: all 0.2s ease-in-out;
	background: #fff;
	color: #262773;
}
`;

export const NavLinkSettings = styled(Link)`
color: #262773;
display: flex;
align-items: center;
text-decoration: none;
padding: 0 2rem;
height: 100%;
cursor: pointer;
&.active {
	color: #262773;
}
`;

export const NavMenu = styled.div`
display: flex;
align-items: center;
margin-right: -24px;
white-space: nowrap;
overflow: hidden;
`;

export const NavMenuCol = styled.div`
display: flex;
align-items: center;
// margin-right: -24px;
white-space: nowrap;
// overflow: hidden;
`;

export const NavBtn = styled.nav`
display: flex;
align-items: center;
margin-right: 14px;
/* Third Nav */
/* justify-content: flex-end;
width: 100vw; */
@media screen and (max-width: 650px) {
	display: none;
}
`;

export const NavBtnCol = styled.nav`
	display: flex;
	align-items: center;
	margin-right: 14px;
	width: 100vw;
	justify-content: center;
`;

export const NavBtnLink = styled(Link)`
border-radius: 20px;
position: fixed;
top: 10px;
right: 20px;
background: rgb(17 16 107);
padding: 10px 22px;
color: #ffffff;
outline: none;
border: none;
cursor: pointer;
transition: all 0.2s ease-in-out;
text-decoration: none;
/* Second Nav */
margin-left: 14px;
@media screen and (max-width: 650px) {
	display: none;
&:hover {
	transition: all 0.2s ease-in-out;
	background: #fff;
	color: #262773;
}
`;

export const NavBtnLinkCol = styled(Link)`
border-radius: 20px;
position: fixed;
align-self: center;
background: rgb(17 16 107);
padding: 10px 22px;
color: #ffffff;
outline: none;
border: none;
cursor: pointer;
transition: all 0.2s ease-in-out;
text-decoration: none;
margin-left: 14px;
`;

export const ImageContainer = styled.div`
  display: none;
  
  @media screen and (max-width: 650px) {
	display: block;
	position: fixed;
	top: 10px;
	right: 10px;
	width: 50px;
	height: 50px;
	cursor: pointer;
  }
`;
