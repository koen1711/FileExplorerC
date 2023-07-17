//
// Created by aukev on 7/17/2023.
//

#ifndef FILEEXPLORERC_FILEVIEW_H
#define FILEEXPLORERC_FILEVIEW_H

#include <vector>
#include <string>
#include <raylib.h>
#include "../../filesystem/FileSystem.h"

class FileView {
    private:
        std::vector<std::string> files;
        Rectangle rectBound;
        FileSystem* fileSystem = new FileSystem();
        int index = 0;
        int selected = -1;

        Texture folder = LoadTexture(this->fileSystem->getFileIcon("Folder").c_str());
        Texture file = LoadTexture(this->fileSystem->getFileIcon("File").c_str());
    public:
        FileView();
        ~FileView();

        void render();
        void setFiles(std::vector<std::string> files);
        void setRectangle(Rectangle rect);
        void setIndex(int index);
        void setSelected(int selected);
};


#endif //FILEEXPLORERC_FILEVIEW_H
