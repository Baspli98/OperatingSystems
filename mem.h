#ifndef MEM_H
#define MEM_H

#include "process.h"
#include <iostream>

namespace mem {

    constexpr unsigned int PAGE_SIZE = 1 << 10;
    constexpr unsigned int PHYSICAL_MEMORY_SIZE = 1 << 20;
    constexpr unsigned int VIRTUAL_MEMORY_SIZE = 1 << 24;

    constexpr unsigned int NUM_PAGES = 1 << 14;
    constexpr unsigned int NUM_PAGE_FRAMES = 1 << 10;

    constexpr unsigned int PAGE_FRAME_SIZE = PAGE_SIZE;

    struct MMU {
        struct TLB* tlb;
        struct Process* process;
    };

    struct TLB {
        struct TLBEntry** entries;
        unsigned int size;
    };

    struct TLBEntry {
        unsigned int page_index;
        unsigned int page_frame_index;
        unsigned char frame_attributes;
    };

    struct PageTable {
        struct PageTableEntry** entries;
        unsigned int size;
    };

    struct PageTableEntry {
        unsigned int page_frame_index;
        unsigned char frame_attributes;
    };

    void printSystemInfo() {
        std::cout << "Page size: " << PAGE_SIZE << " bytes" << std::endl;
        std::cout << "Physical memory size: " << PHYSICAL_MEMORY_SIZE << " bytes" << std::endl;
        std::cout << "Virtual memory size: " << VIRTUAL_MEMORY_SIZE << " bytes" << std::endl;
        std::cout << "Number of pages: " << NUM_PAGES << std::endl;
        std::cout << "Number of page frames: " << NUM_PAGE_FRAMES << std::endl;
        std::cout << "Page frame size: " << PAGE_FRAME_SIZE << " bytes" << std::endl;
    }
}

#endif // MEM_H
