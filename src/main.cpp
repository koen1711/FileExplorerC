#include <thread>
#include <functional>
#include "search/FindFiles.h"
#include "connection/SocketConnection.h"


int main() {
    FindFiles* findFiles;
    SocketConnection* socketConnection;

    std::function<void(std::map<std::string, std::string>)> findFileCallback = [findFiles](std::map<std::string, std::string> searchParameters) {
        findFiles->findFiles(searchParameters);
    };
    std::function<void(std::string)> refreshCallback = [socketConnection](std::string directory) {
        socketConnection->refreshCallback(directory);
    };

    socketConnection = new SocketConnection();
    findFiles = new FindFiles(refreshCallback);


    std::thread t1(&SocketConnection::socketConnection, socketConnection);


    return 0;
}
