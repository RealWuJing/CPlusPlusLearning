#include "download_manager.h"

DownloadManager::DownloadManager(QObject *parent)
{

}

DownloadManager::~DownloadManager()
{
}

int DownloadManager::removeJob()
{
    for(auto iter=jobs.begin(); iter!=jobs.end(); ++iter)
    {
        if (iter.value()->isFinished())
        {
            qInfo() << "appId:" << iter.key();
            delete iter.value();
            jobs.erase(iter);
            return 0;
        }
    }
    return -1;
}