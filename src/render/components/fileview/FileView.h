//
// Created by aukev on 7/17/2023.
//

#ifndef FILEEXPLORERC_FILEVIEW_H
#define FILEEXPLORERC_FILEVIEW_H

#include <vector>
#include <string>
#include <raylib.h>
#include <functional>
#include "../../filesystem/FileSystem.h"

class FileView {
    private:
        using CallBack = std::function<void(std::string)>;

        std::vector<std::string> files;

        FileSystem* fileSystem = new FileSystem();
        int index = 0;
        int selected = -1;

        Texture folder = LoadTexture(this->fileSystem->getFileIcon("Folder").c_str());
        Texture file = LoadTexture(this->fileSystem->getFileIcon("File").c_str());

        CallBack updatePathCallback;
    public:
        FileView(CallBack cb);
        ~FileView();

        // RENDER
        void render();

        // UPDATES
        void setFiles(std::vector<std::string> files);
        void setRectangle(Rectangle rect);
        void setIndex(int index);
        void setSelected(int selected);

        // EVENTS
        void handleLeftClick(Vector2 mousePos);
        void handleLeftDoubleClick(Vector2 mousePos);
        void handleRightClick(Vector2 mousePos);

        Rectangle rectBound;
};


#endif //FILEEXPLORERC_FILEVIEW_H
