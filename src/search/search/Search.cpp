#include "Search.h"
#include <iterator>
#include <iostream>
#include <rapidfuzz/fuzz.hpp>

Search::Search(std::map<std::string, std::string> searchParameters) {
    for (auto keyValuePair : searchParameters) {
        if (keyValuePair.first == "fileName") {
            this->fileName = keyValuePair.second;
        } else if (keyValuePair.first == "allowDirectories") {
            if (keyValuePair.second == "true")
                this->acceptsDirectories = true;
            else
                this->acceptsDirectories = false;
        } else if (keyValuePair.first == "allowFiles") {
            if (keyValuePair.second == "true")
                this->acceptsFiles = true;
            else
                this->acceptsFiles = false;
        } else if (keyValuePair.first == "fileExtension") {
            this->fileExtension = keyValuePair.second;
        }
    }
}

int Search::getMatch(std::string fileName, std::string filePath) {
    std::string fileType = this->fileSystem->getFileType(filePath);

    if (this->acceptsFiles == false && fileType == "File") {
        return 0;
    }

    if (this->acceptsDirectories == false && this->fileSystem->getFileType(filePath) == "Folder") {
        return 0;
    }

    if (this->fileName + this->fileExtension == fileName) {
        return MAX_RESULT;
    }

    int result = 0;

    if (fileName != "" && this->fileExtension != "") {
        if (fileType == "File") {
            try {
                if (fileName.substr(fileName.size() - this->fileExtension.size()) == this->fileExtension) {
                    result += 75;
                }
            } catch (std::out_of_range &e) {
                // do nothing
            }
        } else {
            result += 75;
        }
    } else {
        result += 75;
    }

    // compare the filename string without extension with the this->fileName string
    std::string withoutExtension = fileName.substr(0, fileName.length() - this->fileExtension.length());


    result += rapidfuzz::fuzz::ratio(withoutExtension, this->fileName);

    if (result < MIN_RESULT)
        result = 0;

    return result;
}