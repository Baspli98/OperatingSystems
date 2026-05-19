#ifndef FS_H
#define FS_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>
#include <chrono>

namespace fs {

    constexpr unsigned int FILE_SPACE = 10;

    enum BlockStatus {
        RESERVED,
        DEFECT,
        FREE,
        OCCUPIED
    };

    struct BsBlock {
        BlockStatus state;
        int fileIndex;
    };

    struct BsCluster {
        int blockIndex;

        BsCluster* next;
        BsCluster* prev;
    };

    struct BsFile {
        char fileName[13]; //8.3 format

        int fileSize;
        bool readOnly;
        bool hidden;

        BsCluster* firstCluster;
    };

    struct BsFat {
        int diskSize;
        int blockSize;
        int blockCount;

        BsBlock* blocks;

        BsFile files[FILE_SPACE];
    };

    struct BsFat* createBsFat(int diskSize, int blockSize);
    int getFreeDiskSpace(struct BsFat* pFat);
    struct BsFile* createFile(struct BsFat* pFat, int szFile, const char* fileName, bool readOnly, bool hidden);
    void deleteFile(struct BsFat* pFat, const char* fileName);
    float getFragmentation(struct BsFat* pFat);
    void showFat(struct BsFat* pFat);
    void defragDisk(struct BsFat* pFat);
}

#endif // FS_H
