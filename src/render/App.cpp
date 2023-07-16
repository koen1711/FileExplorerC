#include "App.h"
#include "components/FileSystemView.h"
#include <raylib.h>
#include <thread>

using namespace std;

App::App() {
    this->currentPath = "";
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "FileExplorer");
    this->fileSystemView = new FileSystemView();
}

App::~App() {

}

void App::run() {
    fileSystemView->render();

    Vector2 mousePos;
    while (!WindowShouldClose())
    {
        // check for mouse click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            mousePos = GetMousePosition();
            this->fileSystemView->handleLeftClick(mousePos);
        } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            mousePos = GetMousePosition();
            this->fileSystemView->handleRightClick(mousePos);
        }
        char key = GetCharPressed();
        if (key != 0) {
            // check for arrowup
            if (key == 72) {
                this->fileSystemView->scroll(-1);
            } else if (key == 80) {
                this->fileSystemView->scroll(1);
            }
            else {

            }

        }
        // check for scroll event
        int scroll = GetMouseWheelMove();
        if (scroll != 0) {
            this->fileSystemView->scroll(scroll * -1);
        }
        // check for resize event
        if (IsWindowResized()) {
            this->fileSystemView->render();
        }
        BeginDrawing();
        EndDrawing();
    }
    delete this->fileSystemView;
    CloseWindow();

}
