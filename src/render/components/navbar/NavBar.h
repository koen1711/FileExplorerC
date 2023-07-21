//
// Created by aukev on 7/17/2023.
//

#ifndef FILEEXPLORERC_NAVBAR_H
#define FILEEXPLORERC_NAVBAR_H
#include <raylib.h>
#include <string>
#include <vector>
#include <functional>
#include "../../filesystem/FileSystem.h"

class NavBar {
    private:
        void goBack();
        void goForward();

        bool canGoForward = false;
        bool canGoBackward = false;

        std::vector<std::string>* paths = {};
        int currentIndex = 0;
        using CallBack = std::function<void(std::string, std::string)>;
        CallBack callBack;
        FileSystem* fileSystem = new FileSystem();

        Texture forwardTexture = LoadTexture(this->fileSystem->getFileIcon("Forward").c_str());
        Texture backwardTexture = LoadTexture(this->fileSystem->getFileIcon("Backward").c_str());
        Texture forwardTexturei = LoadTexture(this->fileSystem->getFileIcon("ForwardI").c_str());
        Texture backwardTexturei = LoadTexture(this->fileSystem->getFileIcon("BackwardI").c_str());

        double buttonScale;

        Rectangle forwardRect;
        Rectangle backwardRect;
    public:
        NavBar(Rectangle rectBound, CallBack cb);
        ~NavBar();

        void render();

        // UPDATES
        void setPath(std::string path);
        void setRect(Rectangle rect);

        // CALLBACKS
        void handleLeftClick(Vector2 mousePos);
        void handleRightClick(Vector2 mousePos);
        void handleLeftDoubleClick(Vector2 mousePos);

        Rectangle rectBound{};
};


#endif //FILEEXPLORERC_NAVBAR_H
