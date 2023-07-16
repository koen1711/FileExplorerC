//
// Created by koen on 7/15/23.
//

#ifndef FILEEXPLORERC_APP_H
#define FILEEXPLORERC_APP_H
#include <string>
#include <thread>
#include "components/FileSystemView.h"

using namespace std;

class App {
    private:
        string currentPath;
        FileSystemView* fileSystemView;
    public:
        App();
        ~App();

        void run();
        void openFile();
        void openFolder();

        void setCurrentPath(string path);
        string getCurrentPath();
};


#endif //FILEEXPLORERC_APP_H
