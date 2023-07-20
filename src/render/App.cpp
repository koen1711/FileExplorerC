#include "App.h"
#include "components/FileSystemView.h"
#include <raylib.h>
#include <thread>

#define TARGET_FPS 10

App::App() {
    this->currentPath = "";
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR | LOG_TRACE);
    InitWindow(800, 600, "FileExplorer");

    SetTargetFPS(TARGET_FPS);
    this->fileSystemView = new FileSystemView();
}

App::~App() {

}

Vector2 mousePos;
double timeElapsed = 0;
int click = 0;
char key;
float scroll;

void App::logic(FileSystemView* fileSystemView) {

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        mousePos = GetMousePosition();
        if (GetTime() - timeElapsed < 0.5 && click == 1) {
            fileSystemView->handleLeftDoubleClick(mousePos);
            click = 0;
            timeElapsed = 0;
        } else {
            if (click > 0) {
                click = 0;
                timeElapsed = 0;
            }
            fileSystemView->handleLeftClick(mousePos);
            click += 1;
            timeElapsed = GetTime();
        }
    } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        mousePos = GetMousePosition();
        fileSystemView->handleRightClick(mousePos);
    }


    if (IsKeyPressed(72)) {
        fileSystemView->scroll(-1);
    } else if (IsKeyPressed(80)) {
        fileSystemView->scroll(1);
    }



    scroll = GetMouseWheelMove();
    if (scroll != 0) {
        fileSystemView->scroll(scroll * -1);
    }
}

void App::run() {

    fileSystemView->render();
    bool firstRun = true;
    while (!WindowShouldClose())
    {
        this->logic(fileSystemView);
        BeginDrawing();
            ClearBackground(DARKGRAY);
            this->fileSystemView->render();
        EndDrawing();
    }
    delete this->fileSystemView;

    CloseWindow();

}
