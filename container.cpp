#include "container.h"

namespace container {

    IndexContainer* createIndexContainer(unsigned int cap_indices, unsigned int array_length) {
        auto c = new container::IndexContainer;
        c->array_length = array_length;
        c->cap_indices = new unsigned int[cap_indices];
        for (int i = 0; i < c->array_length; i++) {
            c->cap_indices[i] = i;
        }

        return c;
    }

    IndexContainer* createIndexContainer(unsigned int cap_indices, unsigned int array_length, const IndexContainer* p_c) {
        auto c = new container::IndexContainer;
        c->array_length = array_length;
        c->cap_indices = new unsigned int[cap_indices];
        for (int i = 0; i < c->array_length; i++) {
            c->cap_indices[i] = i + *p_c->cap_indices;
        }

        return c;
    }

    void deleteIndexContainer(IndexContainer* c) {
        delete[]c->cap_indices;
        delete c;
        std::cout << "Deleted Container!" << std::endl;
    }
}