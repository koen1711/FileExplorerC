//
// Created by aukev on 7/17/2023.
//

#include "FileView.h"

#define MIN_SIZE 30

// CONSTRUCTOR DECONSTRUCTOR
FileView::FileView(CallBack cb) : updatePathCallback(cb) {

}

FileView::~FileView() {
}


// RENDER
void FileView::render() {
    BeginScissorMode(this->rectBound.x, this->rectBound.y, this->rectBound.width, this->rectBound.height);
    ClearBackground(DARKGRAY);
    const int amount = this->rectBound.height / MIN_SIZE;
    for (int i = this->index; i < this->index + amount; i++) {
        if (i >= this->files.size()) {
            continue;
        }
        DrawText(this->files[i].c_str(), 50, (i - this->index) * (GetScreenHeight() / amount) + this->rectBound.y, 20, WHITE);
        if (this->fileSystem->getFileType(this->files[i]) == "Folder") {
            DrawTexture(this->folder, 0, (i - this->index) * (GetScreenHeight() / amount) + this->rectBound.y, WHITE);
        } else {
            DrawTexture(this->file, 0, (i - this->index) * (GetScreenHeight() / amount) + this->rectBound.y, WHITE);
        }
    }
    if (this->selected != -1) {
        BeginScissorMode(0, (this->selected - this->index) * (GetScreenHeight() / amount) + this->rectBound.y, GetScreenWidth(), (GetScreenHeight() / amount));
        ClearBackground(LIGHTGRAY);
        DrawText(this->files[this->selected].c_str(), 50, (this->selected - this->index) * (GetScreenHeight() / amount) + this->rectBound.y, 20, WHITE);
        if (this->fileSystem->getFileType(this->files[this->selected]) == "Folder") {
            DrawTexture(this->folder, 0, (this->selected - this->index) * (GetScreenHeight() / amount) + this->rectBound.y, WHITE);
        } else {
            DrawTexture(this->file, 0, (this->selected - this->index) * (GetScreenHeight() / amount) + this->rectBound.y, WHITE);
        }
        EndScissorMode();
    }
    EndScissorMode();
}


// UPDATES
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


// CALLBACKS
void FileView::handleLeftClick(Vector2 mousePos) {
    int y = mousePos.y;
    const int amount = this->rectBound.height / MIN_SIZE;
    int select = (y - this->rectBound.y) / (GetScreenHeight() / amount );
    select += this->index;
    if (select >= this->files.size()) {
        return;
    }
    this->setSelected(select);
}

void FileView::handleRightClick(Vector2 mousePos) {
    int y = mousePos.y;
    const int amount = this->rectBound.height / MIN_SIZE;
    int index = (y - this->rectBound.y) / (GetScreenHeight() / amount );
    if (index >= this->files.size()) {
        return;
    }
}

void FileView::handleLeftDoubleClick(Vector2 mousePos) {
    int y = mousePos.y;
    const int amount = this->rectBound.height / MIN_SIZE;
    int index = (y - this->rectBound.y) / (GetScreenHeight() / amount );
    if (index >= this->files.size()) {
        return;
    }
    if (this->fileSystem->getFileType(this->files[index]) == std::string("File"))
        this->fileSystem->openFile(this->files[index]);
    else
        this->updatePathCallback(this->files[index]);
}