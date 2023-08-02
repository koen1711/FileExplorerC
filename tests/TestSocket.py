import socket

HOST = 'localhost'  # Replace with the IP address or hostname of the server
PORT = 10000  # Replace with the port number used by the server (10000 in this case)

# Create a TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the server
    client_socket.connect((HOST, PORT))
    print(f"Connected to {HOST}:{PORT}")

    # Receive data from the server
    data = client_socket.recv(1024)
    print("Received:", data.decode())

except socket.error as e:
    print("Error: ", e)

while True:
    # check if there is data to receive
    try:
        data = client_socket.recv(1024)
        if data != b'':
            print("Received:", data.decode())

            if data.decode() == "SHUTDOWN":
                socket.close()
                break
    except socket.error as e:
        print("Error: ", e)
        break

