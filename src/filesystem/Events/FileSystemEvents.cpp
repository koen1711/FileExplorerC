#include "FileSystemEvents.h"

#include "efsw/efsw.hpp"
#include <iostream>
#include <utility>

void FileSystemEvents::handleFileAction(efsw::WatchID watchid, const std::string &dir, const std::string &filename,
                                        efsw::Action action, std::string oldFilename) {
    // add dir and filename together and then remove everything after and including the last slash
    // this will give us the directory of the file
    std::string actualDir = dir + filename;
    actualDir = actualDir.substr(0, actualDir.find_last_of("\\/") + 1);
    if (!oldFilename.empty()) {
        this->refreshCallback(actualDir);
        return;
    }
    switch (action) {
        case efsw::Actions::Add:
            this->refreshCallback(actualDir);
            break;
        case efsw::Actions::Delete:
            this->refreshCallback(actualDir);
            break;
        case efsw::Actions::Moved:
            this->refreshCallback(actualDir);
            break;
    }
}

void FileSystemEvents::setRefreshCallback(std::function<void(std::string)> refreshCb) {
    this->refreshCallback = std::move(refreshCb);
}