//
// Created by aukev on 7/26/2023.
//

#ifndef FILEEXPLORERCBACKGROUNDSERVICE_SOCKETCONNECTION_H
#define FILEEXPLORERCBACKGROUNDSERVICE_SOCKETCONNECTION_H

#include <string>
#include <functional>
#include <map>
#include <sockpp/tcp_socket.h>
#define PORT 10000

class SocketConnection {
private:
    using FindFileCallback = std::function<void(std::map<std::string, std::string>, std::string)>;
    FindFileCallback findFileCallback;
    sockpp::tcp_socket* sock;
public:
    SocketConnection(std::function<void(std::map<std::string, std::string>, std::string)>);

    void socketConnection();
    void refreshCallback(std::string directory);
};


#endif //FILEEXPLORERCBACKGROUNDSERVICE_SOCKETCONNECTION_H
