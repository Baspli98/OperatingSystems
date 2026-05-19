#include "fs.h"

namespace fs {

    BsFat* createBsFat(int diskSize, int blockSize) {
        BsFat* fat = new BsFat;

        fat->diskSize = diskSize;
        fat->blockSize = blockSize;

        fat->blockCount = diskSize / blockSize;

        fat->blocks = new BsBlock[fat->blockCount];

        for (int i = 0; i < fat->blockCount; i++) {
            fat->blocks[i].state = FREE;
            fat->blocks[i].fileIndex = -1;
        }

        for (int i = 0; i < FILE_SPACE; i++) {
            fat->files[i].fileName[0] = '\0';
            fat->files[i].fileSize = 0;
            fat->files[i].readOnly = false;
            fat->files[i].hidden = false;
            fat->files[i].firstCluster = nullptr;
        }

        return fat;
    }

}