#include "filemanager.h"

FileManager::FileManager(string location) {
    QDir dir(location.c_str());
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    /* std::cout << "     Bytes Filename" << std::endl; */
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        /* std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10) */
        /*                                         .arg(fileInfo.fileName()).arg(fileInfo.lastModified().toString("ddd MMMM d yyyy hh:mm:ss"))); */
        /* std::cout << std::endl; */
    }
}
