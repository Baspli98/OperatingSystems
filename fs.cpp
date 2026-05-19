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
                              const char* fileName,
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

        if (getFreeDiskSpace(pFat) < neededBlocks) {
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

    void deleteFile(struct BsFat* pFat, const char* fileName) {
        int fileIndex = -1;

        for (int i = 0; i < FILE_SPACE; i++) {
            if (std::strcmp(pFat->files[i].fileName, fileName) == 0) {
                fileIndex = i;
                break;
            }
        }

        if (fileIndex == -1) {
            return;
        }

        BsFile* file = &pFat->files[fileIndex];
        BsCluster* current = file->firstCluster;

        while (current != nullptr) {
            int block = current->blockIndex;
            pFat->blocks[block].state = FREE;
            pFat->blocks[block].fileIndex = -1;

            BsCluster* next = current->next;
            delete current;
            current = next;
        }

        file->fileName[0] = '\0';
        file->fileSize = 0;
        file->readOnly = false;
        file->hidden = false;
        file->firstCluster = nullptr;
    }

    float getFragmentation(struct BsFat* pFat) {
        int fragmented = 0;
        int totalTransitions = 0;

        for (int i = 0; i < FILE_SPACE; i++) {
            BsFile* file = &pFat->files[i];
            if (file->fileName[0] == '\0') {
                continue;
            }

            BsCluster* current = file->firstCluster;

            while (current != nullptr && current->next != nullptr) {
                totalTransitions++;

                int currentBlock = current->blockIndex;
                int nextBlock = current->next->blockIndex;

                if (nextBlock != currentBlock + 1) {
                    fragmented++;
                }
                current = current->next;
            }
        }

        if (totalTransitions == 0) {
            return 0.0f;
        }

        return (fragmented * 100.0f) / totalTransitions;
    }

    void showFat(struct BsFat* pFat) {
        for (int i = 0; i < pFat->blockCount; i++) {
            std::cout << "|";
            switch (pFat->blocks[i].state) {
                case RESERVED:
                    std::cout << "R";
                    break;
                case DEFECT:
                    std::cout << "D";
                    break;
                case FREE:
                    std::cout << "F";
                    break;
                case OCCUPIED:
                    std::cout << pFat->blocks[i].fileIndex;
                    break;
            }
        }
        std::cout << "|";
    }

    void defragDisk(struct BsFat* pFat) {
        int targetBlock = 0;
        for (int fileIndex = 0; fileIndex < FILE_SPACE; fileIndex++) {
            BsFile* file = &pFat->files[fileIndex];
            if (file->fileName[0] == '\0') {
                continue;
            }

            std::cout << "Defragmenting file: " << file->fileName << std::endl;

            BsCluster* current = file->firstCluster;

            while (current != nullptr) {
                while (targetBlock < pFat->blockCount &&
                       pFat->blocks[targetBlock].state != FREE) {
                    targetBlock++;
                }

                if (targetBlock >= pFat->blockCount) {
                    return;
                }

                int oldBlock = current->blockIndex;
                pFat->blocks[oldBlock].state = FREE;
                pFat->blocks[oldBlock].fileIndex = -1;

                pFat->blocks[targetBlock].state = OCCUPIED;
                pFat->blocks[targetBlock].fileIndex = fileIndex;

                current->blockIndex = targetBlock;

                std::cout << "Moved Block " << oldBlock << " -> " << targetBlock << std::endl;

                targetBlock++;

                current = current->next;

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(300)
                );
            }
        }
        std::cout << "Defragmantation finished." << std::endl;
    }
}