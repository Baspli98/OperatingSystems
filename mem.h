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

    struct Process {
        unsigned char process_id;
        struct mem::PageTable* page_table;
    };

    void printSystemInfo();
    PageTable* createPageTable();
    TLB* createTLB(unsigned int size);
    Process* createProcess(unsigned char id);

}

#endif // MEM_H
