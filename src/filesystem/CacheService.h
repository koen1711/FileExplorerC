#ifndef FILEEXPLORERC_CACHESERVICE_H
#define FILEEXPLORERC_CACHESERVICE_H

#include <memory>
#include <functional>
#include "Events/FileSystemEvents.h"

class CacheService {
public:
    static std::shared_ptr<CacheService> Instance()
    {
        static std::shared_ptr<CacheService> s{new CacheService};
        return s;
    }

    void fileSystemWatcher();

    void setRefreshCallback(std::function<void(std::string)> refreshCallback);
private:
    efsw::FileWatcher* fileWatcher = new efsw::FileWatcher();
    FileSystemEvents* fileSystemEvents = new FileSystemEvents();
    static CacheService * const cacheService;
    CacheService();
};


#endif //FILEEXPLORERC_CACHESERVICE_H
