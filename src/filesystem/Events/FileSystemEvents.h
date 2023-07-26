#ifndef FILEEXPLORERC_FILESYSTEMEVENTS_H
#define FILEEXPLORERC_FILESYSTEMEVENTS_H

#include <functional>
#include "efsw/efsw.hpp"

class FileSystemEvents : public efsw::FileWatchListener {
public:
    void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename,
                          efsw::Action action, std::string oldFilename = "") override;

    void setRefreshCallback(std::function<void(std::string)> refreshCallback);
private:
    using RefreshCallback = std::function<void(std::string)>;
    RefreshCallback refreshCallback;
};


#endif //FILEEXPLORERC_FILESYSTEMEVENTS_H
