#include "App.h"

#include <thread>
#include <functional>
#include "search/FindFiles.h"
#include "connection/SocketConnection.h"

App::App() {

}

void App::start() {


    std::function<void(std::map<std::string, std::string>, std::string)> findFileCallback = [this](std::map<std::string, std::string> searchParameters, std::string point) {
        if (this->findFiles != nullptr)
            this->findFiles->findFiles(searchParameters, point);
    };
    std::function<void(std::string)> refreshCallback = [this](std::string directory) {
        if (this->socketConnection != nullptr)
            this->socketConnection->refreshCallback(directory);
    };

    this->socketConnection = new SocketConnection(findFileCallback);
    this->findFiles = new FindFiles(refreshCallback);


    this->socketConnection->socketConnection();
}