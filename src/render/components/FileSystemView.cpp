#include "FileSystemView.h"
#include <raylib.h>
#include <functional>
#include <utility>
#include "../filesystem/FileSystem.h"

#define MIN_SIZE 30

FileSystemView::FileSystemView() {
    std::function<void(std::string, std::string)> navBarInteractionCallback = [this](const std::string& path, const std::string& type) {
        this->navBarInteraction(path, type);
    };

    std::function<void(std::string)> pathCallBack = [this](const std::string& path) {
        this->updatePath(path);
    };

    float width = GetScreenWidth();

    this->navBar = new NavBar(Rectangle {0, 0, width, (float)(GetScreenHeight() * 0.1)}, this->currentPath, navBarInteractionCallback);
    this->fileView = new FileView(pathCallBack);
#ifdef __linux__
    this->currentPath getenv("HOME");
#else
    this->currentPath = std::string(getenv("TEMP"));
    this->currentPath = this->currentPath.substr(0, this->currentPath.length() - 18);
#endif
    this->files = this->fileSystem->getFiles(this->currentPath);
    this->fileView->setFiles(this->files);
    this->fileView->setRectangle(Rectangle {0, (float)(GetScreenHeight() * 0.1), width, (float)(GetScreenHeight() * 0.9)});
}

FileSystemView::~FileSystemView() {
    delete this->fileSystem;
}

void FileSystemView::navBarInteraction(const std::string& path, const std::string& type) {
    this->currentPath = path;
    this->files = this->fileSystem->getFiles(path);
    this->fileView->setFiles(this->files);
}

void FileSystemView::updatePath(const std::string& path) {
    this->currentPath = path;
    this->navBar->setPath(path);
    this->files = this->fileSystem->getFiles(path);
    this->fileView->setFiles(this->files);
}

void FileSystemView::render() {
    this->fileView->render();
    this->navBar->render();
}

void FileSystemView::resize() {
    float width = GetScreenWidth();
    this->navBar->setRect(Rectangle {0, 0, width, (float)(GetScreenHeight() * 0.1)});
    this->fileView->setRectangle(Rectangle {0, (float)(GetScreenHeight() * 0.1), width, (float)(GetScreenHeight() * 0.9)});
}

void FileSystemView::scroll(float ind) {
    if (this->index + ind < 0) {
        this->index = this->files.size() - 1;
    } else if (this->index + ind >= this->files.size()) {
        this->index = 0;
    } else {
        this->index += ind;
    }
    this->fileView->setIndex(index);
}

void FileSystemView::handleLeftClick(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, this->navBar->rectBound))
        this->navBar->handleLeftClick(mousePos);
    else
        this->fileView->handleLeftClick(mousePos);
}

void FileSystemView::handleRightClick(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, this->navBar->rectBound))
        this->navBar->handleRightClick(mousePos);
    else
        this->fileView->handleRightClick(mousePos);
}

void FileSystemView::handleLeftDoubleClick(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, this->navBar->rectBound))
        this->navBar->handleLeftDoubleClick(mousePos);
    else
        this->fileView->handleLeftDoubleClick(mousePos);
}