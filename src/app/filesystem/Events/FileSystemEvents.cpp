#include "FileSystemEvents.h"

#include "efsw/efsw.hpp"
#include <iostream>

void FileSystemEvents::handleFileAction(efsw::WatchID watchid, const std::string &dir, const std::string &filename,
                                        efsw::Action action, std::string oldFilename) {
    switch (action) {
        case efsw::Actions::Add:
            this->refreshCallback();
            break;
        case efsw::Actions::Delete:
            this->refreshCallback();
            break;
        case efsw::Actions::Moved:
            this->refreshCallback();
            break;
    }
}

void FileSystemEvents::setRefreshCallback(std::function<void()> refreshCallback) {
    this->refreshCallback = refreshCallback;
}