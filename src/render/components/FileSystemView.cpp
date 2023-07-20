#include "FileSystemView.h"
#include <raylib.h>
#include <functional>
#include "../filesystem/FileSystem.h"

#define MAX_ENTRIES 25

FileSystemView::FileSystemView() {
#ifdef __linux__
    this->currentPath getenv("HOME");
#else
    this->currentPath = std::string(getenv("TEMP"));
    this->currentPath = this->currentPath.substr(0, this->currentPath.length() - 18);
#endif
    this->files = this->fileSystem->getFiles(this->currentPath);
    this->fileView->setFiles(this->files);

    std::function<void(std::string)> cb = [this](std::string path) {
        this->navBarInteraction(path);
    };

    float width = GetScreenWidth();
    this->navBar = new NavBar(Rectangle {0, 0, width, (float)(GetScreenHeight() * 0.1)}, this->currentPath, cb);
    this->fileView->setRectangle(Rectangle {0, (float)(GetScreenHeight() * 0.1), width, (float)(GetScreenHeight() * 0.9)});
}

FileSystemView::~FileSystemView() {
    delete this->fileSystem;
}

void FileSystemView::navBarInteraction(std::string path) {
    this->currentPath = path;
    this->files = this->fileSystem->getFiles(path);
    this->fileView->setFiles(this->files);
}

void FileSystemView::updatePath(string path) {
    this->currentPath = path;
    this->navBar->updatePath(path);
    this->files = this->fileSystem->getFiles(path);
    this->fileView->setFiles(this->files);
}

void FileSystemView::render() {
    this->fileView->render();
    this->navBar->render();
}


void FileSystemView::scroll(int ind) {
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
    int x = mousePos.x;
    int y = mousePos.y;
    int select = y / (GetScreenHeight() / MAX_ENTRIES);
    select += this->index;
    if (select >= this->files.size()) {
        return;
    }
    this->fileView->setSelected(select);
}

void FileSystemView::handleRightClick(Vector2 mousePos) {
    int x = mousePos.x;
    int y = mousePos.y;
    int index = y / (GetScreenHeight() / MAX_ENTRIES);
    if (index >= this->files.size()) {
        return;
    }
}

void FileSystemView::handleLeftDoubleClick(Vector2 mousePos) {
    int y = mousePos.y;
    int index = y / (GetScreenHeight() / MAX_ENTRIES);
    if (index >= this->files.size()) {
        return;
    }
    if (this->fileSystem->getFileType(this->files[index]) == std::string("File"))
        this->fileSystem->openFile(this->files[index]);
    else
        this->updatePath(this->files[index]);
}