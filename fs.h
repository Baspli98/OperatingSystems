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
}


#endif // FS_H
