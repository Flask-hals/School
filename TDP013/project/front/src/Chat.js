import { useParams } from 'react-router-dom';
import { useState, useEffect } from 'react';
import socket from "./socket";

const Chat = () => {
    const { user } = useParams();
    const [room, setRoom] = useState("");
    const [message, setMessage] = useState("");
    const [sentMessage, setSentMessage] = useState([]);

    useEffect(() => {

        if (user !== "")
        {
            let roomName = [sessionStorage.getItem("username"), user];
            const sortedRoomName = roomName.sort().join('');
            setRoom(sortedRoomName);
            socket.emit("joinRoom", sortedRoomName);
        }

        socket.on("receivedMessage", (data) => {
            setSentMessage(prevMessages => [
            {
                message: data.message,
                friend: data.friend
            },
            ...prevMessages
            ]);
        });

        return () => {
            socket.off("receivedMessage");
        };
    }, []);


    const sendMessage = () => {
        const friend = sessionStorage.getItem("username");
        socket.emit("sendMessage", {message, room, friend});
        setMessage("");
    };

    return ( 
        <div>
            <h2>Chatting with {user}</h2>
            <input placeholder='message' value={message} onChange={(e) => setMessage(e.target.value)}></input>
            <button onClick={sendMessage}>Send</button>
            <div id="output">
                {sentMessage && sentMessage.map((msg, index) => (
                    <div className="msg" key={index}>
                        <p>Sent from: {msg.friend}</p>
                        <p>{msg.message}</p>
                    </div>
                ))}
            </div>
        </div>
    );
}
 
export default Chat;