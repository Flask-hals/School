import socket
import re
import time

PORT = 8001
HOST = socket.gethostbyname("127.0.0.1")

'''
Start of client side and proxy program.
Creates socket which browser / host connects to.
'''
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    print("Socket created")
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    # Binds the socket to host
    server_socket.bind((HOST, PORT))
    # Socket starts "listening" on incoming TCP connections
    server_socket.listen()
    print("Serversocket ready to receive")

    try:
        # Infinite loop to accept any incoming connections
        while True:
            # Accepts a connection, and saves it in a new socket: conn 
            # (when user clicks on a site for example, so this will be the request)
            conn, addr = server_socket.accept()
            with conn:
                print("Got connection from", addr)
                # Try to recieve the request data from the new connection
                data = conn.recv(4096)
                if not data:
                    break
                """
                Start of server side.
                Creates a new socket that communicates with the server as the host.
                """
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
                    # Finds the destination address in the request data
                    server_addr = re.search(rb"Host: \b(.*)\b", data)
                    # Set connection type to close instead of keep-alive since we dont want to wait for the timeout
                    data = re.sub(rb"(Connection: )\b(.*)\b", r"\1close".encode(), data)
                    # This is done so that the server always sends fresh data instead of 304 not modified
                    data = re.sub(rb"(If-Modified-Since: )\b(.*)\b", r"\1Mon, 01 Jan 0000 00:00:00 GMT".encode(), data)

                    # Connects the newly made socket to the server the initial request was made for
                    client_socket.connect((socket.gethostbyname(server_addr.group(1).decode()), 80))
                    # Sends the request and recieves the first chunk of data
                    client_socket.sendall(data)
                    s_data = client_socket.recv(4096)

                    # Split the headers and body part in first chunk
                    split = s_data.split('\r\n\r\n'.encode(),1)
                    response_headers = split[0]
                    response_headers += "\r\n\r\n".encode()
                    response_body = split[1]
                    
                    # If the response is an image, we send the chunks directly because we know that we don't need to modify the data
                    # Else we save the data so we can modify it and still change the content-length
                    if response_headers.find(b"Content-Type: image") != -1:
                        print("THIS IS AN IMAGE")
                        s_data = response_headers + response_body
                        # Send image in chunks
                        while len(s_data) > 0:
                            time.sleep(0.1)
                            conn.sendall(s_data)
                            s_data = client_socket.recv(4096)
                    else:
                        # Recieve next chunk that now only contains body data
                        s_data = client_socket.recv(4096)
                        # While still recieveing data save it in a buffer: response_body
                        while len(s_data) > 0:
                            time.sleep(0.1)
                            response_body += s_data
                            s_data = client_socket.recv(4096)

                        # Replace smiley.jpg links
                        response_body = re.sub(rb'(".*smiley.jpg)"', rb'http://www.sherv.net/cm/emoticons/memes/problem-meme-smiley-emoticon.jpg', response_body)
                        
                        # Replace smiley and Stockholm in text
                        response_body = re.sub(rb"(?i)( |^)(Smiley)", b" Trolly", response_body)
                        response_body = re.sub(rb"(?i)( |^)(Stockholm)", " Linköping".encode(), response_body)
                        
                        # Update content-length
                        response_headers = re.sub(rb"(Content-Length: )(\d+)", b"Content-Length: " + str(len(response_body)).encode(), response_headers)
       
                        # Set together the header and whole body that was saved in the buffer and send it through the socket that
                        # is connected to the host
                        s_data = response_headers + response_body                    
                        conn.sendall(s_data)
    
    # Handles ctrl-C when closing the proxy
    except KeyboardInterrupt:
        print("\nShutting down server...")
    finally:
        server_socket.close()