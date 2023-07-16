//
// Created by koen on 7/15/23.
//

#include "FileSystemView.h"
#include <raylib.h>
#include "../filesystem/FileSystem.h"
#include <iostream>

#define MAX_ENTRIES 25

FileSystemView::FileSystemView() {
    this->currentPath = getenv("HOME");
    this->fileSystem = new FileSystem();
    this->files = this->fileSystem->getFiles(this->currentPath);
}

FileSystemView::~FileSystemView() {
    delete this->fileSystem;
    ClearBackground(RAYWHITE);
}

void FileSystemView::updatePath(string path) {
    this->currentPath = path;
    this->files = this->fileSystem->getFiles(path);
}

void FileSystemView::render() {
    BeginDrawing();
    ClearBackground({ 89, 89, 89, 255 });
    for (int i = this->index; i < this->index + MAX_ENTRIES; i++) {
        if (i >= this->files.size()) {
            continue;
        }
        DrawText(this->files[i].c_str(), 50, (i - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, 20, WHITE);
        DrawTexture(LoadTexture(this->fileSystem->getFileIcon(this->files[i]).c_str()), 0, (i - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, WHITE);
    }
    EndDrawing();
}

void FileSystemView::scroll(int ind) {
    if (this->index + ind < 0) {
        this->index = this->files.size() - 1;
    } else if (this->index + ind >= this->files.size()) {
        this->index = 0;
    } else {
        this->index += ind;
    }
    this->render();
}

void FileSystemView::handleLeftClick(Vector2 mousePos) {
    int x = mousePos.x;
    int y = mousePos.y;
    int index = y / (GetScreenHeight() / MAX_ENTRIES);
    if (index >= this->files.size()) {
        return;
    }
    std::cout << this->files[index] << std::endl;
}

void FileSystemView::handleRightClick(Vector2 mousePos) {
    int x = mousePos.x;
    int y = mousePos.y;
    int index = y / (GetScreenHeight() / MAX_ENTRIES);
    if (index >= this->files.size()) {
        return;
    }
    std::cout << this->files[index] << std::endl;
}