//
// Created by koen on 7/15/23.
//

#ifndef FILEEXPLORERC_FILESYSTEMVIEW_H
#define FILEEXPLORERC_FILESYSTEMVIEW_H
#include <string>
#include "../filesystem/FileSystem.h"
#include <raylib.h>

using namespace std;

class FileSystemView {
private:
    FileSystem* fileSystem = new FileSystem();
    string currentPath;
    std::vector<std::string> files;
    int index = 0;
    int selected = -1;

    Texture folder = LoadTexture(this->fileSystem->getFileIcon("Folder").c_str());
    Texture file = LoadTexture(this->fileSystem->getFileIcon("File").c_str());
public:
    FileSystemView();
    ~FileSystemView();

    void updatePath(string path);
    void render();
    void scroll(int ind);

    void handleLeftClick(Vector2 mousePos);
    void handleRightClick(Vector2 mousePos);
    void handleLeftDoubleClick(Vector2 mousePos);
};


#endif //FILEEXPLORERC_FILESYSTEMVIEW_H
