#ifndef FILEEXPLORERC_FINDFILES_H
#define FILEEXPLORERC_FINDFILES_H


#include <functional>
#include "search/Search.h"

class FindFiles {
private:
    std::string startingPoint;

    void getFilesInDirectory(std::string directory, std::vector<std::string>* files, Search* search);
public:
    FindFiles(std::function<void(std::string)> refreshCallback);

    std::map<int, std::string> findFiles(std::map<std::string, std::string> searchParameters);
};


#endif //FILEEXPLORERC_FINDFILES_H
