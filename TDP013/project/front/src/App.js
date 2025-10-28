import NavBar from './NavBar';
import Home from './Home';
import Login from './Login';
import Chat from './Chat';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import ProtectedRoute from './ProtectedRoute';

function App() {
  return (
    <Router>
      <div className="App">
        <NavBar />
        <div className="content">
          <Routes>
            <Route path="/" element={<Login />} />
            <Route path="/home/:user" element={<ProtectedRoute element={<Home />} />} />
            <Route path="/chat/:user" element={<ProtectedRoute element={<Chat />} />} />
          </Routes>
        </div>
      </div>
    </Router>
  );
}

export default App;
