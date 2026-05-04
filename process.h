#ifndef PROCESS_H
#define PROCESS_H

namespace prcss {
    struct Process {
        unsigned char process_id;
        struct PageTable* page_table;
    };
}

#endif // PROCESS_H
