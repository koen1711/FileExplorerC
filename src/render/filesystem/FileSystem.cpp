#include "FileSystem.h"
#include <filesystem>
#include "whereami.h"
#include <vector>
#include <string>
#include <iostream>

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
}

std::vector<std::string> FileSystem::getFiles(std::string path) {
    std::vector<std::string> files;

    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        files.push_back(entry.path().string());
    }

    return files;
}


std::string FileSystem::getFileIcon(std::string fileType) {
    std::string resourcePath = "";
    std::string iconPath = "/";

    if (fileType == "Folder") {
        iconPath += "resources/icons/folder.png";
    } else {
        iconPath += "resources/icons/file.png";
    }

    // get the path of the executable
    int length = wai_getExecutablePath(NULL, 0, NULL);
    char* path = new char[length];
    wai_getExecutablePath(path, length, NULL);
    std::string pathString = std::string(path);
    pathString = pathString.substr(0, pathString.find_last_of("/\\"));


    return pathString + iconPath;
}

std::string FileSystem::getFileType(std::string path) {
    if (std::filesystem::is_directory(path)) {
        return "Folder";
    }
    return "File";
}

void FileSystem::openFile(std::string path) {
    std::cout << "explorer " << path << std::endl;
    system((std::string("explorer ") + path).c_str());
}