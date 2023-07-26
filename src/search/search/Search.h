#ifndef FILEEXPLORERC_SEARCH_H
#define FILEEXPLORERC_SEARCH_H

#include <string>
#include <map>
#include "../../filesystem/FileSystem.h"

#define MAX_RESULT 1000
#define MIN_RESULT 150

class Search {
private:
    FileSystem* fileSystem = new FileSystem();

    // SEARCH PARAMETERS DECODED
    bool acceptsDirectories = true;
    bool acceptsFiles = true;
    std::string fileExtension;
    std::string fileName;

public:
    Search(std::map<std::string, std::string> searchParameters);

    int getMatch(std::string fileName, std::string filePath);


};


#endif //FILEEXPLORERC_SEARCH_H
