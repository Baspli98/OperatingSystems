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
        }

        return fat;
    }

}