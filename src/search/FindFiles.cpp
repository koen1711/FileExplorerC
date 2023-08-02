#include <iostream>
#include "FindFiles.h"
#include <filesystem>
#include <vector>
#include "../filesystem/CacheService.h"


FindFiles::FindFiles(std::function<void(std::string)> refreshCallback) {
    CacheService::Instance()->setRefreshCallback(std::move(refreshCallback));
    CacheService::Instance()->fileSystemWatcher();

}

std::map<int, std::string> FindFiles::findFiles(std::map<std::string, std::string> searchParameters, std::string startingPoint) {
    Search* search = new Search(searchParameters);

    std::vector<std::string>* files = new std::vector<std::string>{};
    this->getFilesInDirectory(startingPoint, files, search);

    return std::map<int, std::string>{};
}

void FindFiles::getFilesInDirectory(std::string directory, std::vector<std::string>* files, Search* search) {
    std::filesystem::directory_iterator it;

    try {
        it = std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied | std::filesystem::directory_options::follow_directory_symlink);
    } catch (std::filesystem::filesystem_error &e) {}

    for (const auto & entry : it) {
        if (search->getMatch(entry.path().filename().string(), entry.path().string()) != 0) {
            files->push_back(entry.path().string());
        }
        if (std::filesystem::is_directory(entry.path())) {
            // recursive call
            this->getFilesInDirectory(entry.path().string(), files, search);
        }

    }
}