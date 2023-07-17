//
#include "FileSystemView.h"
#include <raylib.h>
#include "../filesystem/FileSystem.h"
#include <iostream>

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
    this->fileView->setRectangle(Rectangle {0, 0, 800, 600});
}

FileSystemView::~FileSystemView() {
    delete this->fileSystem;
}

void FileSystemView::updatePath(string path) {
    this->currentPath = path;
    this->files = this->fileSystem->getFiles(path);
    this->fileView->setFiles(this->files);
}

void FileSystemView::render() {
    this->fileView->render();
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
    int index = y / (GetScreenHeight() / MAX_ENTRIES);
    if (index >= this->files.size()) {
        return;
    }
    std::cout << this->files[index].c_str() << std::endl;
    this->fileView->setSelected(index);
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