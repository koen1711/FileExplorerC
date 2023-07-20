#include <iostream>
#include <utility>
#include "NavBar.h"

NavBar::NavBar(Rectangle rectBound, const std::string& path, CallBack cb) : callBack(std::move(cb)), rectBound(rectBound) {
    this->rectBound = rectBound;
    this->paths = new std::vector<std::string>;
    this->updatePath(path);
}

NavBar::~NavBar() = default;

void NavBar::render() {
    BeginScissorMode(this->rectBound.x, this->rectBound.y, this->rectBound.width, this->rectBound.height);
        ClearBackground((Color){ 90, 90, 90, 255 });
        if (this->currentIndex != 0) {
            std::cout << "Can go back!";
        }
        if (this->currentIndex != this->paths->size() - 1) {
            std::cout << "Can go forward";
        }
    EndScissorMode();
}

void NavBar::updatePath(const std::string& path) {
    if (currentIndex != this->paths->size()) {
        this->paths->erase(std::next(this->paths->begin(), currentIndex), std::next(this->paths->begin(), this->paths->size()));
    }
    this->paths->push_back(path);
    this->currentIndex = this->paths->size() - 1;
}


void NavBar::goForward() {
    this->currentIndex += 1;
    this->callBack(this->paths->at(this->currentIndex));
}

void NavBar::goBack() {
    this->currentIndex = this->currentIndex - 1;
    this->callBack(this->paths->at(this->currentIndex));
}

void NavBar::updateRect(Rectangle rect) {
    this->rectBound = rect;
}