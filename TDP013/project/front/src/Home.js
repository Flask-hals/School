import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';

const Home = () => {
    const [errorMessage, setErrorMessage] = useState("");
    const [messages, setMessages] = useState([]);
    const [message, setMessage] = useState("");
    const [searchedUser, setSearchedUser] = useState([]);
    const [foundUsers, setFoundUsers] = useState([]);
    const [friends, setFriends] = useState([]);
    const [page, setPage] = useState(sessionStorage.getItem("page"));
    const navigate = useNavigate();

    useEffect(() => {
        const FetchMessages = async () => {
            try
            {
                console.log("useEffect");
                let username = sessionStorage.getItem("username");
                const response = await fetch(`/users/${username}`);

                if (response.ok)
                {
                    let messages = await response.json();
                    setMessages(messages.reverse());
                    await loadFriends();
                }
            }
            catch(error)
            {
                setErrorMessage("Something went wrong!");
            }
        }
        FetchMessages();
    }, []);

    const getDate = () => {
        const date = new Date();
        let min = String(date.getMinutes());
        if (min.length === 1) {min = "0" + min}
        let hour = String(date.getHours());
        if (hour.length === 1) {hour = "0" + hour}
        let month = String(date.getMonth());
        if (month.length === 1) {month = "0" + month}
        let day = String(date.getDay());
        if (day.length === 1) {day = "0" + day}

        return "Posted at " + date.getFullYear() + "-" + month + "-" +  day + " " + hour + ":" + min;
    };

    const checkMessage = () => {
        const trimmedMessage = message.trim();
        setMessage(trimmedMessage);
        if (trimmedMessage.length <= 0 || trimmedMessage.length > 140)
        {
            setErrorMessage("Messages must contain 1 - 140 letters!");
        }
        else
        {
            setErrorMessage("");
            postMessage(trimmedMessage);
        }
    };

    const searchUser = async () => {
        try
        {
            const response = await fetch("/users");

            if (response.ok)
            {
                const users = await response.json();
                const filteredUsers = users.filter(use => 
                    use.username !== sessionStorage.getItem("username") &&
                    use.username.toLowerCase().includes(searchedUser.toLowerCase())
                );

                const results = await Promise.all(
                    filteredUsers.map(async (use) => {
                        const isFriend = await checkIfFriend(use.username);
                        return {...use, isFriend};
                    })
                )
                const users2Load = results.filter(u => !u.isFriend);
                setFoundUsers(users2Load);
            }
        }
        catch(error)
        {
            setErrorMessage("Friends not found, or something went wrong");
        }
    };
    
    const checkIfFriend = async (friend) => {
        try
        {
            const response = await fetch(`/checkIfFriend/${sessionStorage.getItem("username")}/${friend}`);

            if (response.ok)
            {
                return true;
            }
            else
            {
                const sentFriend = await fetch(`/checkIfFriend/${friend}/${sessionStorage.getItem("username")}`);
                if (sentFriend.ok)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        catch(error)
        {
            return false;
        }
    };

    const sendFriendRequest = async (user) => {
        try
        {
            const response = await fetch(`/friendRequest/${user}/friends`, {
                method: "POST",
                headers: {"Content-Type": "application/json"},
                body: JSON.stringify({
                    friend: sessionStorage.getItem("username"),
                    isFriend: false
                })
            });
            const text = await response.text();
            if (response.status === 201)
            {
                setErrorMessage(`Friend request sent to ${user}`);
                const updateFoundUsers = foundUsers.filter(fr => fr.username !== user);
                setFoundUsers(updateFoundUsers);
                return {status: response.status, body: text}
            }
            else
            {
                setErrorMessage("Friend request failed");
            }
        }
        catch(error)
        {
            setErrorMessage("Friend request failed");
        }
    };

    const postMessage = async (value) => {
        try
        {
            const response = await fetch(`/postMessage/${sessionStorage.getItem("page")}`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    author: sessionStorage.getItem("username"),
                    message: value,
                    date: getDate(),
                    read: false
                })
            });

            if (response.ok)
            {
                let messages = await response.json();
                setMessages(prevMessages => [
                    {
                        author: sessionStorage.getItem("username"),
                        message: value,
                        date: getDate(),
                        read: false,
                        _id: messages
                    },
                    ...prevMessages
                ]);
                setMessage("");
            }
        }
        catch(error)
        {
            setErrorMessage("Something went wrong with your post!");
        }
    };

    const checkRead = (id) => {
        const newMessages = messages.map(msg =>
            msg._id === id ? { ...msg, read: !msg.read } : msg
        );
        setMessages(newMessages);
        const message = newMessages.find(msg => msg._id === id);
        patchRead(message, id);
    };

    const patchRead = async (message, id) => {
        try
        {
            await fetch(`/patchRead/${sessionStorage.getItem("username")}/${id}`, {
                method: "PATCH",
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ read: message.read })
            });
        }
        catch(error)
        {
            setErrorMessage("Something went wrong clicking the checkbox!");
        }
    };

    const loadFriendsDoc = async (friend) => {
        if (sessionStorage.getItem("page") !== friend)
        {
            try
            {
                const response = await fetch(`/users/${friend}`)
                if (response.ok)
                {
                    let messages = await response.json();
                    setMessages(messages.reverse());
                    sessionStorage.setItem("page", friend);
                    setPage(friend);
                }
            }
            catch(error)
            {
                setErrorMessage("Couldnt find that page!");
            }
        }
    };

    const loadFriends = async () => {
        try
        {
            const response = await fetch(`/users/${sessionStorage.getItem("username")}/friends`);

            if (response.ok)
            {
                const friends = await response.json();
                setFriends(friends);
            }
        }
        catch(error)
        {
            setErrorMessage("Something went wrong loading your friends!");
        }
    };

    const handleFriend = async (friend, isFriend) => {
        try
        {
            const response = await fetch(`/handleFriend/${sessionStorage.getItem("username")}/${friend}/${isFriend}`, {
                method: "PATCH",
                headers: {
                    "Content-Type": "application/json"
                },
                body: isFriend ? JSON.stringify({remove: true}) : JSON.stringify({isFriend: true})
            })

            if (response.ok)
            {
                if (!isFriend)
                {
                    const updateFriends = friends.map(fr => 
                        fr.friend === friend ? {...fr, isFriend: !fr.isFriend } : fr
                    );
                    setFriends(updateFriends);
                }
                else
                {
                    const updateFriends = friends.filter(fr => fr.friend !== friend);
                    setFriends(updateFriends);
                }
            }
        }
        catch(error)
        {
            setErrorMessage("Something went wrong!");
        }
    };

    return (
        <div>
            <h2>{page}'s page</h2>
            <div id="outerHeader" className="container my-5">
                <div id="userDiv" className="container my-5">
                    <h2>Friends</h2>
                </div>
                <div id="inputDiv" className="container my-5">
                    <textarea id="post" className="form-control" value={message} onChange={(e) => setMessage(e.target.value)}></textarea>
                    <button id="postButton" className="btn btn-outline-primary btn-lg" onClick={checkMessage}>Post</button>
                </div>
                <div id="searchDiv" className="container my-5">
                    <input id="searchInput" className="form-controll" placeholder="Search user" value={searchedUser} onChange={(e) => setSearchedUser(e.target.value)}></input>
                    <button id="searchButton" className="btn btn-outline-primary btn-lg" onClick={searchUser}>Search</button>
                </div>
            </div>
            {errorMessage && <div id="errorMessage" className="text-danger mt-3">{errorMessage}</div>}
            <div id="divBox" className="container">
                <div id="friends">
                    {friends && friends.map((friend) => {
                        return(
                            <div className="foundFriends" key={friend.friend}>
                                <div className="userName">
                                <p style={{textAlign: "left", fontWeight: "bold"}}>{friend.friend}</p>
                                </div>
                                <div className="friendButtons">
                                <button
                                    style={{ border: "solid black 1px"}}
                                    type="button"
                                    className="btn btn-default btn-sm"
                                    onClick={() => handleFriend(friend.friend, friend.isFriend)}
                                    >
                                    {friend.isFriend ? "Remove" : "Add"}
                                </button>
                                {friend.isFriend && (
                                <button
                                    style={{ border: "solid black 1px"}}
                                    type="button"
                                    className="btn btn-default btn-sm"
                                    onClick={() => loadFriendsDoc(friend.friend)}
                                    >
                                    View page
                                </button>
                                )}
                                {friend.isFriend && (
                                <button
                                    style={{ border: "solid black 1px"}}
                                    type="button"
                                    className="btn btn-default btn-sm"
                                    onClick={() => navigate(`/chat/${friend.friend}`)}
                                    >
                                    Chat
                                </button>
                                )}
                                </div>
                            </div>
                        );
                    })}
                </div>
                <div id="messages">
                    {messages && messages.map((message) => (
                        <div className="messageBox" key={message._id}>
                            <div className="contentBox">
                                <p>{message.author}</p>
                                <p>{message.message}</p>
                                <p>{message.date}</p>
                            </div>
                            {sessionStorage.getItem("username") === sessionStorage.getItem("page") && (
                            <input
                            style={{ marginTop: '1rem', width: '3rem', height: '3rem', marginLeft: '1rem'}}
                            className="form-check-input checkBox"
                            type="checkbox"
                            checked={message.read}
                            onChange={() => checkRead(message._id)}
                            />
                            )}
                        </div>
                    ))}
                </div>
                <div id="searchFriends">
                    {foundUsers && foundUsers.map((users) => (
                        <div className="foundUsers" key={users._id}>
                             <p style={{fontWeight: "bold"}} >{users.username}</p>
                             <button
                             className="btn btn-default btn-sm" 
                             style={{ border: "solid black 1px"}} 
                             type="button" 
                             onClick={ () => sendFriendRequest(users.username)}>Add</button>
                        </div>
                    ))}
                </div>
            </div>
        </div>
    );
}
 
export default Home;