//
// Created by aukev on 7/17/2023.
//

#ifndef FILEEXPLORERC_NAVBAR_H
#define FILEEXPLORERC_NAVBAR_H
#include <raylib.h>
#include <string>
#include <vector>
#include <functional>

class NavBar {
    private:
        Rectangle rectBound{};
        std::vector<std::string>* paths = {};
        int currentIndex = 0;
        using CallBack = std::function<void(std::string)>;
        CallBack callBack;


    public:
        NavBar(Rectangle rectBound, const std::string& path, CallBack cb);
        ~NavBar();

        void render();
        void updatePath(const std::string& path);
        void goBack();
        void goForward();

    void updateRect(Rectangle rect);


};


#endif //FILEEXPLORERC_NAVBAR_H
