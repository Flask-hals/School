import { Navigate } from 'react-router-dom';

const ProtectedRoute = ({ element }) => {
  const username = sessionStorage.getItem("username");

  if (!username) {
    return <Navigate to="/" replace />;
  }
  
  return element;
};

export default ProtectedRoute;
