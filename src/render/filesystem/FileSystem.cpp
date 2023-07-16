#include "FileSystem.h"
#include <filesystem>
#include "whereami.h"

#ifdef _WIN32
    #include <Windows.h>
    #include <ShlObj.h>
#elif __linux__
    #include <cstdlib>
    #include <unistd.h>
#endif

FileSystem::FileSystem() {

}

FileSystem::~FileSystem() {
    delete this;
}

std::vector<std::string> FileSystem::getFiles(std::string path) {
    std::vector<std::string> files;

    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        files.push_back(entry.path());
    }

    return files;
}


std::string FileSystem::getFileIcon(std::string filePath) {
    std::string resourcePath = "";
    std::string iconPath = "/";

    // check if the file is a directory

    if (std::filesystem::is_directory(filePath)) {
        iconPath += "resources/icons/folder.png";
    } else {
        iconPath += "resources/icons/file.png";
    }

    // get the path of the executable
    int length = wai_getExecutablePath(NULL, 0, NULL);
    char* path = new char[length];
    wai_getExecutablePath(path, length, NULL);
    // replace the last /FILE
    std::string pathString = std::string(path);
    pathString = pathString.substr(0, pathString.find_last_of("/\\"));


    return pathString + iconPath;
}
