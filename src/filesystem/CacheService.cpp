#include "CacheService.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <utility>
#ifdef _WIN32
#include <fileapi.h>
#endif

CacheService::CacheService() = default;

void CacheService::fileSystemWatcher() {

#ifdef _WIN32
    // loop through GetLogicalDrives() and add each drive to the file watcher
    DWORD drives = GetLogicalDrives();
    for (int i = 0; i < 26; i++) {
        if (drives & (1 << i)) {
            std::string drive = std::string(1, 'A' + i) + ":\\";
            try {
                this->fileWatcher->addWatch(drive, this->fileSystemEvents, true);
            } catch (std::filesystem::filesystem_error &e) {
                continue;
            }

        }
    }
#else
    this->fileWatcher->addWatch("/", this->fileSystemEvents, true);
#endif

    this->fileWatcher->watch();
}

void CacheService::setRefreshCallback(std::function<void(std::string)> refreshCallback) {
    fileSystemEvents->setRefreshCallback(std::move(refreshCallback));
}