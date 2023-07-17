//
// Created by aukev on 7/17/2023.
//

#include "FileView.h"
#include <iostream>

#define MAX_ENTRIES 25

FileView::FileView() {

}

FileView::~FileView() {
}

void FileView::render() {
    BeginScissorMode(this->rectBound.x, this->rectBound.y, this->rectBound.width, this->rectBound.height);
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
        ClearBackground(LIGHTGRAY);
        DrawText(this->files[this->selected].c_str(), 50, (this->selected - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, 20, WHITE);
        if (this->fileSystem->getFileType(this->files[this->selected]) == "Folder") {
            DrawTexture(this->folder, 0, (this->selected - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, WHITE);
        } else {
            DrawTexture(this->file, 0, (this->selected - this->index) * (GetScreenHeight() / MAX_ENTRIES) + 10, WHITE);
        }
        EndScissorMode();
    }
    EndScissorMode();
}

void FileView::setFiles(std::vector<std::string> files) {
    this->files = files;
    this->selected = -1;
    this->index = 0;
}

void FileView::setRectangle(Rectangle rect) {
    this->rectBound = rect;
}

void FileView::setIndex(int index) {
    this->index = index;
}

void FileView::setSelected(int selected) {
    this->selected = selected;
}