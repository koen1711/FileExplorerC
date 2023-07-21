#include "PathView.h"

PathView::PathView() = default;
PathView::~PathView() = default;

void PathView::render() {
    BeginScissorMode(this->rectBound.x, this->rectBound.y, this->rectBound.width, this->rectBound.height);
    DrawRectangleRounded(this->rectBound, 1, 4, DARKGRAY);
    // draw the current thext in this->rectBound
    DrawText(this->currentPath.c_str(), this->rectBound.x + 10, this->rectBound.y + 10, this->rectBound.height - 5, BLACK);
    EndScissorMode();
}


// UPDATES
void PathView::setRect(Rectangle rect) {
    this->rectBound = rect;
}

void PathView::setPath(std::string path) {
    this->currentPath = path;
}