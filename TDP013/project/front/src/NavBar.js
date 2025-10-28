import { useLocation } from "react-router-dom";

const NavBar = () => {
    const location = useLocation();

    const logOut = () => {
        sessionStorage.clear();
    };

    const loadHomePage = () => {
        if (sessionStorage.getItem("page") !== sessionStorage.getItem("username"))
        {
            sessionStorage.setItem("page", sessionStorage.getItem("username"));
        }
    };

    return ( 
        <nav className="navbar">
            <h1>Tweeter - Hello {sessionStorage.getItem("username")}</h1>
            <div className="links">
                <a href={`/home/${sessionStorage.getItem("username")}`} onClick={loadHomePage}>Home Page</a>
                <a href="/" onClick={logOut}>Log out</a>
            </div>
        </nav>
    );
}
 
export default NavBar;