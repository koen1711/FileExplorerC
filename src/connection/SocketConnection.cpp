//
// Created by aukev on 7/26/2023.
//

#include "SocketConnection.h"
#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_socket.h>

SocketConnection::SocketConnection() {

}

void SocketConnection::socketConnection() {
    try {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Failed to initialize Winsock." << std::endl;
        }

        sockpp::inet_address addr("0.0.0.0", PORT);
        sockpp::tcp_acceptor acceptor(addr);

        std::cout << "TCP Server is listening on port " << PORT << std::endl;

        while (true) {
            // check if there is a client connection
            if (acceptor) {
                // Get the connected socket
                this->sock = acceptor.accept();

                // Get the address of the client
                sockpp::inet_address client_addr = sock.peer_address();

                std::cout << "Received a connection from " << client_addr << std::endl;

                // Send a message to the client
                sock.write("Hello from TCP server!");

                // Close the client connection
                sock.close();
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    WSACleanup();
}

void SocketConnection::refreshCallback(std::string directory) {
    if (this->sock.is_open()) {
        this->sock.write( "REFRESH," + directory);
    }
}