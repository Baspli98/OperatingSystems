#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

namespace container {
    struct IndexContainer {
        unsigned int* cap_indices;
        unsigned int array_length;
    };

    IndexContainer* createIndexContainer(unsigned int cap_indices, unsigned int array_length);
    IndexContainer* createIndexContainer(unsigned int cap_indices, unsigned int array_length, const IndexContainer* p_c);
    void deleteIndexContainer(IndexContainer* c);
}

#endif // CONTAINER_H
