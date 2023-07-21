#ifndef FILEEXPLORERC_PATHVIEW_H
#define FILEEXPLORERC_PATHVIEW_H

#include <string>
#include "raylib.h"

class PathView {
    private:
        std::string currentPath;
        bool active = false;
    public:
        // CONSTRUCTOR DECONSTRUCTOR
        PathView();
        ~PathView();

        // RENDER
        void render();

        // UPDATE
        void setPath(std::string path);
        void setRect(Rectangle rect);

        // EVENTS
        void handleLeftClick(Vector2 mousePos);
        void handleRightClick(Vector2 mousePos);
        void handleLeftDoubleClick(Vector2 mousePos);
        void handleKeyInput(char key);

        // PROPS
        Rectangle rectBound;
};


#endif //FILEEXPLORERC_PATHVIEW_H
