//
#include "FileSystemView.h"
#include <raylib.h>
#include "../filesystem/FileSystem.h"
#include <iostream>

#define MAX_ENTRIES 20

FileSystemView::FileSystemView() {
#ifdef __linux__
    this->currentPath getenv("HOME");
#else
    this->currentPath = std::string(getenv("TEMP"));
    this->currentPath = this->currentPath.substr(0, this->currentPath.length() - 18);
#endif
    this->files = this->fileSystem->getFiles(this->currentPath);
}

FileSystemView::~FileSystemView() {
    delete this->fileSystem;
}

void FileSystemView::updatePath(string path) {
    this->currentPath = path;
    this->files = this->fileSystem->getFiles(path);
    this->selected = -1;
}

void FileSystemView::render() {

    for (int i = this->index; i < this->index + MAX_ENTRIES; i++) {
        if (i >= this->files.size()) {
            continue;
        }
        DrawText(this->files[i].c_str(), 50, (i - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, 20, WHITE);
        if (this->fileSystem->getFileType(this->files[i]) == "Folder") {
            DrawTexture(this->folder, 0, (i - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, WHITE);
        } else {
            DrawTexture(this->file, 0, (i - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, WHITE);
        }
    }
    if (this->selected != -1) {
        BeginScissorMode(0, (this->selected - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, GetScreenWidth(), (GetScreenHeight() / MAX_ENTRIES));
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), LIGHTGRAY);
            DrawText(this->files[this->selected].c_str(), 50, (this->selected - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, 20, WHITE);
            if (this->fileSystem->getFileType(this->files[this->selected]) == "Folder") {
                DrawTexture(this->folder, 0, (this->selected - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, WHITE);
            } else {
                DrawTexture(this->file, 0, (this->selected - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, WHITE);
            }
        EndScissorMode();
    }
}


void FileSystemView::scroll(int ind) {

    if (this->index + ind < 0) {
        this->index = this->files.size() - 1;
    } else if (this->index + ind >= this->files.size()) {
        this->index = 0;
    } else {
        this->index += ind;
    }
}

void FileSystemView::handleLeftClick(Vector2 mousePos) {
    int x = mousePos.x;
    int y = mousePos.y;
    int index = y / (GetScreenHeight() / MAX_ENTRIES);
    if (index >= this->files.size()) {
        return;
    }
    std::cout << this->files[index].c_str() << std::endl;
    this->selected = index;
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