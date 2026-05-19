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

    int getFreeDiskSpace(struct BsFat* pFat) {
        int freeBlocks = 0;

        for (int i = 0; i < pFat->blockCount; i++) {
            if(pFat->blocks[i].state == FREE) {
                freeBlocks++;
            }
        }

        return freeBlocks * pFat->blockSize;
    }

    struct BsFile* createFile(struct BsFat* pFat,
                              int szFile,
                              char* fileName,
                              bool readOnly,
                              bool hidden) {
        int fileIndex = -1;

        for (int i = 0; i < FILE_SPACE; i++) {
            if (pFat->files[i].fileName[0] == '\0') {
                fileIndex = i;
                break;
            }
        }

        if (fileIndex == -1) {
            return nullptr;
        }

        int neededBlocks = (szFile + pFat->blockSize -1) / pFat->blockSize;

        int freeBlocks = 0;
        if (freeBlocks < getFreeDiskSpace(pFat)) {
            return nullptr;
        }

        BsFile* file = &pFat->files[fileIndex];
        std::strcpy(file->fileName, fileName);
        file->fileSize = szFile;
        file->readOnly = readOnly;
        file->hidden = hidden;

        file->firstCluster = nullptr;
        BsCluster* lastCluster = nullptr;

        for (int i = 0; i < neededBlocks; i++) {
            int rndBlock;
            do {
                rndBlock = rand() % pFat->blockCount;
            } while (pFat->blocks[rndBlock].state != FREE);

            pFat->blocks[rndBlock].state = OCCUPIED;
            pFat->blocks[rndBlock].fileIndex = fileIndex;

            BsCluster* cluster = new BsCluster;
            cluster->blockIndex = rndBlock;
            cluster->next = nullptr;
            cluster->prev = lastCluster;

            if (lastCluster != nullptr) {
                lastCluster->next = cluster;
            } else {
                file->firstCluster = cluster;
            }
            lastCluster = cluster;
        }

        return file;
    }

}