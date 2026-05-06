#include "mem.h"

namespace mem {
    void printSystemInfo() {
        std::cout << "Page size: " << PAGE_SIZE << " bytes" << std::endl;
        std::cout << "Physical memory size: " << PHYSICAL_MEMORY_SIZE << " bytes" << std::endl;
        std::cout << "Virtual memory size: " << VIRTUAL_MEMORY_SIZE << " bytes" << std::endl;
        std::cout << "Number of pages: " << NUM_PAGES << std::endl;
        std::cout << "Number of page frames: " << NUM_PAGE_FRAMES << std::endl;
        std::cout << "Page frame size: " << PAGE_FRAME_SIZE << " bytes" << std::endl;
    }

    PageTable* createPageTable() {
        PageTable* pt = new PageTable;
        pt->size = NUM_PAGES;
        pt->entries = new PageTableEntry*[pt->size];
        for (int i = 0; i < pt->size; i++) {
            pt->entries[i] = new PageTableEntry;

            pt->entries[i]->page_frame_index = 0;
            pt->entries[i]->frame_attributes = 0;
        }
        return pt;
    }

    TLB* createTLB(unsigned int size) {
        TLB* tlb = new TLB;
        tlb->size = size;
        tlb->entries = new TLBEntry*[tlb->size];

        for (int i = 0; i < tlb->size; i++) {
            tlb->entries[i] = new TLBEntry;

            tlb->entries[i]->page_index = 0;
            tlb->entries[i]->page_frame_index = 0;
            tlb->entries[i]->frame_attributes = 0;
        }

        return tlb;
    }

    Process* createProcess(unsigned char id) {
        Process* p = new Process;

        p->process_id = id;
        p->page_table = createPageTable();

        return p;
    }

    unsigned int countTLBEntries(struct Process* p) {
        int count = 0;
        for (int i = 0; i < p->page_table->size; i++) {
            if(p->page_table->entries[i]->frame_attributes & FRAME_TLB) {
                count += 1;
            }
        }
        return count;
    }

    void copyTLBEntries(struct Process* p, struct TLB* tlb) {
        int tlbIndex = 0;
        for (int i = 0; i < p->page_table->size; i++) {
            if(p->page_table->entries[i]->frame_attributes & FRAME_TLB) {

                tlb->entries[tlbIndex]->page_index = i; //I do not understand that yet
                tlb->entries[tlbIndex]->page_frame_index = p->page_table->entries[i]->page_frame_index;
                tlb->entries[tlbIndex]->frame_attributes = p->page_table->entries[i]->frame_attributes;
                tlbIndex += 1;
            }
        }
    }

    unsigned int translate(unsigned int virtual_address, struct PageTable* pt) {
        //Virtual address contains 24 bits split into Page Index 14 bits and Offset 10 bits
        unsigned int page_index = virtual_address >> 10;
        unsigned int offset = virtual_address & 1023;
        //010010101101001101010101
        //000000000000001111111111 = 1023

        //Use Page Index to search pt for the frame
        auto entry = pt->entries[page_index];
        //Sidequest - Set Flags
        entry->frame_attributes |= FRAME_TLB;
        entry->frame_attributes |= FRAME_REFERENCED;

        auto frame = entry->page_frame_index;

        //Glue frame + offset
        unsigned int physical = (frame << 10) | offset;
        //01010110010000000000
                  //1101001010

        return physical;
    }

    int preprocessInstructions(struct MMU* mmu, unsigned int* instructions, unsigned int instruction_count) {
        if(!mmu || !instructions || instruction_count == 0)
            return -1;

        Process* p = mmu->process;
        PageTable* pt = p->page_table;

        for (int i = 0; i < instruction_count; i++) {
            translate(instructions[i], pt);
        }

        unsigned int count = countTLBEntries(p);
        if(count == 0)
            return -1;

        copyTLBEntries(p, mmu->tlb);

        return 0;
    }
}