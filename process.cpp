#include "process.h"

namespace prcss {
    Process* createProcess(unsigned char id) {
        Process* p = new Process;

        p->process_id = id;
        p->page_table = mem::createPageTable();

        return p;
    }
}