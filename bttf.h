#ifndef BTTF_H
#define BTTF_H

#include <iostream>

namespace bttf {
    struct FluxCapacitor {
        unsigned char* c_string;
        unsigned int value;
    };

    FluxCapacitor* createFluxCapacitor();
    FluxCapacitor** createFluxCapacitorArray(unsigned int n);
    void printFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
    void bubbleSortFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
    void deleteFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
}

#endif // BTTF_H
