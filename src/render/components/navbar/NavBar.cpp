#include <iostream>
#include <utility>
#include "NavBar.h"
#include <cmath>

// CONSTRUCTORS AND DECONSTRUCTORS
NavBar::NavBar(Rectangle rectBound, const std::string& path, CallBack cb) : callBack(std::move(cb)), rectBound(rectBound) {
    this->setRect(rectBound);
    this->paths = new std::vector<std::string>;
    this->setPath(path);
}

NavBar::~NavBar() = default;

// RENDER
void NavBar::render() {
    BeginScissorMode(this->rectBound.x, this->rectBound.y, this->rectBound.width, this->rectBound.height);
        ClearBackground((Color){ 90, 90, 90, 255 });
        float texturesize = 30 * this->buttonScale;
        float ycenter = (this->rectBound.height / 2) - (texturesize / 2);

        // Backward logic
        if (this->currentIndex != 0) {
            DrawTextureEx(this->backwardTexture, Vector2{(float)(this->buttonScale * 30), ycenter}, 0, this->buttonScale, BLACK);
        } else {
            DrawTextureEx(this->backwardTexturei, Vector2{(float)(this->buttonScale * 30), ycenter}, 0, this->buttonScale, RED);
        }

        // Forward logic
        if (this->currentIndex != this->paths->size() - 1) {
            DrawTextureEx(this->forwardTexture, Vector2{(float)(this->buttonScale * 30 + this->buttonScale * 30), ycenter}, 0, this->buttonScale, LIGHTGRAY);
        } else {
            DrawTextureEx(this->forwardTexturei, Vector2{(float)(this->buttonScale * 30 + this->buttonScale * 30), ycenter}, 0, this->buttonScale, LIGHTGRAY);
        }
    EndScissorMode();
}


// EVENTS
void NavBar::goForward() {
    if (this->currentIndex != this->paths->size() - 1)
        return;
    this->canGoBackward = true;
    this->currentIndex += 1;
    this->callBack(this->paths->at(this->currentIndex), "Forward");
    if (this->currentIndex != this->paths->size() - 1)
        this->canGoForward = false;
    else
        this->canGoForward = true;
}

void NavBar::goBack() {
    if (this->currentIndex == 0)
        return;
    this->canGoForward = true;
    this->currentIndex = this->currentIndex - 1;
    this->callBack(this->paths->at(this->currentIndex), "Backward");
    if (this->currentIndex == 0)
        this->canGoBackward = false;
    else
        this->canGoBackward = true;
}


// UPDATES
void NavBar::setRect(Rectangle rect) {
    this->rectBound = rect;
    std::cout << this->rectBound.height;
    this->buttonScale = (this->rectBound.height * 0.5) / 30;
    std::cout << this->buttonScale;
}

void NavBar::setPath(const std::string& path) {
    if (currentIndex != this->paths->size() - 1) {
        this->paths->erase(std::next(this->paths->begin(), currentIndex), std::next(this->paths->begin(), this->paths->size()));
    }
    this->paths->push_back(path);
    this->currentIndex = this->paths->size() - 1;
    this->canGoForward = false;
    if (this->currentIndex == 0)
        this->canGoBackward = false;
    else
        this->canGoBackward = true;
}

// CALLBACKS
void NavBar::handleLeftClick(Vector2 mousePos) {
    // TODO: HANDLE LEFT CLICKS ON NAVBAR
}

void NavBar::handleRightClick(Vector2 mousePos) {
    // TODO: HANDLE RIGHT CLICKS ON NAVBAR
}

void NavBar::handleLeftDoubleClick(Vector2 mousePos) {
    // TODO: HANDLE LEFT DOUBLE CLICKS ON NAVBAR
}