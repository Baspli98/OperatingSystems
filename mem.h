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

    constexpr unsigned char FRAME_TLB        = 1 << 0; // 00000001
    constexpr unsigned char FRAME_REFERENCED = 1 << 1; // 00000010

    struct MMU {
        struct TLB* tlb;
        struct Process* process;
    };

    struct TLB {
        struct TLBEntry** entries;
        unsigned int size;
    };

    struct TLBEntry {
        unsigned int page_index; //24 bit from virtual
        unsigned int page_frame_index; //20 bit from physical
        unsigned char frame_attributes; //8 bit
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
        struct PageTable* page_table;
    };

    void printSystemInfo();
    PageTable* createPageTable();
    TLB* createTLB(unsigned int size);
    Process* createProcess(unsigned char id);
    unsigned int countTLBEntries(struct Process* p);
    void copyTLBEntries(struct Process* p, struct TLB* tlb);
    unsigned int translate(unsigned int virtual_address, struct PageTable* pt);
    int preprocessInstructions(struct MMU* mmu, unsigned int* instructions, unsigned int instruction_count);
}

#endif // MEM_H
