//
// Created by koen on 7/15/23.
//

#ifndef FILEEXPLORERC_FILESYSTEMVIEW_H
#define FILEEXPLORERC_FILESYSTEMVIEW_H
#include <string>
#include "../filesystem/FileSystem.h"
#include "fileview/FileView.h"
#include <raylib.h>
#include "navbar/NavBar.h"

using namespace std;

class FileSystemView {
private:
    FileSystem* fileSystem = new FileSystem();
    NavBar* navBar;
    string currentPath;
    std::vector<std::string> files;
    int index = 0;

    FileView* fileView = new FileView();
public:
    FileSystemView();
    ~FileSystemView();

    void updatePath(const string& path);
    void render();
    void scroll(float ind);

    void handleLeftClick(Vector2 mousePos);
    void handleRightClick(Vector2 mousePos);
    void handleLeftDoubleClick(Vector2 mousePos);

    void navBarInteraction(const string& path);
};


#endif //FILEEXPLORERC_FILESYSTEMVIEW_H
