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

        static std::vector<std::string> getFiles(const std::string& path);
        static std::string getFileIcon(const std::string& fileType);
        static std::string getFileType(const std::string& path);
        static void openFile(const std::string& path);
        void openFolder();

};


#endif //FILEEXPLORERC_FILESYSTEM_H
