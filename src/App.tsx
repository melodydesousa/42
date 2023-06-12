import { Routes, Route } from "react-router-dom";
import './App.css';
import './style.scss'
import Register from './pages/Register';
// import Register42 from './pages/Register42';
import Home from './pages/Home';

function App() {
  return (
    <div>
      <Home />
      <div className='container'>
        <Register />
        {/* <Register42 /> */}
        {/* <Board/> */}
        {/* <ChatHome/> */}
      </div>
    </div>
  );
}

export default App