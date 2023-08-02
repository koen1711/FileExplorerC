#ifndef FILEEXPLORERCBACKGROUNDSERVICE_APP_H
#define FILEEXPLORERCBACKGROUNDSERVICE_APP_H

#include "search/FindFiles.h"
#include "connection/SocketConnection.h"

class App {
private:
    FindFiles* findFiles;
    SocketConnection* socketConnection;
public:
    App();
    void start();
};


#endif //FILEEXPLORERCBACKGROUNDSERVICE_APP_H
