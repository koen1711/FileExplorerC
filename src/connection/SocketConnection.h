//
// Created by aukev on 7/26/2023.
//

#ifndef FILEEXPLORERCBACKGROUNDSERVICE_SOCKETCONNECTION_H
#define FILEEXPLORERCBACKGROUNDSERVICE_SOCKETCONNECTION_H

#include <string>
#include <sockpp/tcp_socket.h>
#define PORT 10000

class SocketConnection {
private:
    sockpp::tcp_socket sock;
public:
    SocketConnection();

    void socketConnection();
    void refreshCallback(std::string directory);
};


#endif //FILEEXPLORERCBACKGROUNDSERVICE_SOCKETCONNECTION_H
