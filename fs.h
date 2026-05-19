#ifndef FS_H
#define FS_H

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

}

#endif // FS_H
