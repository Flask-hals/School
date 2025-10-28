import { useState } from 'react';
import { useNavigate } from 'react-router-dom';

const Login = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const [errorMessage, setErrorMessage] = useState('');
    const navigate = useNavigate();

    const logIn = async (event) =>
    {
        event.preventDefault();

        try {
            const hashedPassword = await hashPassword(password);
            const response = await fetch(`/login/${username}`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    password: hashedPassword,
                })
            })
            
            if (response.ok)
            {
                    sessionStorage.setItem("username", username);
                    sessionStorage.setItem("page", username);
                    setErrorMessage("Correct password");
                    navigate(`/home/${username}`);
            }
            else
            {
                setErrorMessage("Wrong username or password!");
            }
        }
        catch (error)
        {
            console.error("Something went wrong:", error);
            setErrorMessage("Could not connect to server.");
        }
    };

    const register = async (event) =>
    {
        event.preventDefault();

        if (!username || !password)
        {
            setErrorMessage("Please enter username and password!");
            return;
        }

        try
        {
            const response = await fetch(`/users/${username}`);
            
            if (response.ok)
            {
                setErrorMessage("Username already exists!");
            }
            else
            {
                setErrorMessage("");
                await createNewUser(username, password);
            }
        }
        catch (error)
        {
            setErrorMessage("Could not connect to server.");
        }
    };

    const hashPassword = async (password) =>
    {
        const data = new TextEncoder().encode(password);
        const buffer = await crypto.subtle.digest('SHA-256', data);
        return Array.from(new Uint8Array(buffer))
            .map(b => b.toString(16).padStart(2, '0'))
            .join('');
    };

    const createNewUser = async (username, password) =>
    {
        try
        {
            const hashedPassword = await hashPassword(password);
            const response = await fetch('/newUser', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    username: username,
                    password: hashedPassword,
                    messages: [],
                    friends: []
                })
            });

            if (response.ok) 
            {
                setErrorMessage("User created successfully!");
            } 
            else 
            {
                setErrorMessage("Could not create user.");
            }
        } 
        catch (error) 
        {
            console.error("Error creating user:", error);
            setErrorMessage("Could not connect to server.");
        }
    };

    return ( 
        <div>
            <form>
                <div className="form-group">
                    <label htmlFor="username">Username</label>
                    <input type="username" className="form-control" id="username" placeholder="Enter username" value={username} onChange={e => setUsername(e.target.value)}/>
                </div>
                <div className="form-group">
                    <label htmlFor="password">Password</label>
                    <input type="password" className="form-control" id="password" placeholder="Password" value={password} onChange={e => setPassword(e.target.value)}/>
                </div>
                <button id="logInButton" className="btn btn-primary" onClick={logIn}>Log In</button>
                <button id="registerButton" className="btn btn-primary" onClick={register}>Register</button>
            </form>
            {errorMessage && <div className="text-danger mt-3">{errorMessage}</div>}
        </div>
    );
}
 
export default Login;