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

std::vector<std::string> FileSystem::getFiles(const std::string& path) {
    std::vector<std::string> files;


    try {
        for (const auto &entry: std::filesystem::directory_iterator(path,
                                                                    std::filesystem::directory_options::skip_permission_denied |
                                                                    std::filesystem::directory_options::follow_directory_symlink)) {
            files.push_back(entry.path().string());
        }
    } catch(std::filesystem::filesystem_error e) {
        files.emplace_back("Error: This directory seems to have given an error at runtime, maybe it is protected?");
        return files;
    }

    return files;
}


std::string FileSystem::getFileIcon(const std::string& fileType) {
    std::string resourcePath;
    std::string iconPath = "/";

    if (fileType == "Folder")
        iconPath += "resources/icons/folder.png";
    else if (fileType == "Forward")
        iconPath += "resources/icons/forwardTexture.png";
    else if (fileType == "Backward")
        iconPath += "resources/icons/texture.png";
    else if (fileType == "ForwardI")
        iconPath += "resources/icons/forwardi.png";
    else if (fileType == "BackwardI")
        iconPath += "resources/icons/backwardi.png";
    else
        iconPath += "resources/icons/file.png";


    // get the path of the executable
    int length = wai_getExecutablePath(NULL, 0, NULL);
    char* path = new char[length];
    wai_getExecutablePath(path, length, NULL);
    std::string pathString = std::string(path);
    pathString = pathString.substr(0, pathString.find_last_of("/\\"));


    return pathString + iconPath;
}

/// Get the file type, given a std::string that's a valid path
std::string FileSystem::getFileType(const std::string& path) {
    if (reinterpret_cast<const char *>(path[6]) == "Error:") {
        return "File";
    }
    if (std::filesystem::is_directory(path)) {
        return "Folder";
    }
    return "File";
}

/// Open a file, given a std::string that's a valid path
void FileSystem::openFile(const std::string& path) {
    try {
        system((std::string("explorer ") + path).c_str());
    } catch(std::error_code) {
       std::cout << "Can't open file, maybe it is protected?";
    }
}