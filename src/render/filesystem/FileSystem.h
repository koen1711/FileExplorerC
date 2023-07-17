//
// Created by koen on 7/15/23.
//

#ifndef FILEEXPLORERC_FILESYSTEM_H
#define FILEEXPLORERC_FILESYSTEM_H
#include <string>
#include <vector>

class FileSystem {
    private:
    public:
        FileSystem();
        ~FileSystem();

        std::vector<std::string> getFiles(std::string path);
        std::string getFileIcon(std::string path);
        std::string getFileType(std::string path);
        void openFile(std::string path);
        void openFolder();

};


#endif //FILEEXPLORERC_FILESYSTEM_H
