#ifndef FS_H
#define FS_H

namespace fs {
    enum BlockStatus {
        RESERVED,
        DEFECT,
        FREE,
        OCCUPIED
    };

    struct BsBlock {
        BlockStatus state;
    };

    struct BsFat {
        int diskSize;
        int blockSize;
        int blockCount;

        BsBlock* blocks;
    };

    struct BsCluster {
        int blockIndex;

        BsCluster* next;
        BsCluster* prev;
    };

    struct BsFat* createBsFat(int diskSize, int blockSize);

}

#endif // FS_H
