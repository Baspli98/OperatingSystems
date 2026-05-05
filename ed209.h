#ifndef ED2_9_H
#define ED2_9_H

#include "mem.h"

namespace rbt {
    struct ED_209
    {
        struct mem::MMU* mmu;
    };

    void startED209(struct ED_209* ed);
}

#endif // ED2_9_H
