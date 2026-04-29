#ifndef BTTF_H
#define BTTF_H

#include <iostream>
#include "container.h"

extern pthread_mutex_t mutex;

namespace bttf {
    struct FluxCapacitor {
        unsigned char* c_string;
        unsigned int value;
    };

    struct DeLorean {
        double speed_in_kmh;
        double current_power_level_in_mega_watts;
    };

    extern DeLorean* delorean__;
    extern FluxCapacitor** capacitors__;

    FluxCapacitor* createFluxCapacitor();
    FluxCapacitor* createFluxCapacitor(unsigned int value);
    FluxCapacitor** createFluxCapacitorArray(unsigned int n);
    FluxCapacitor** createFluxCapacitorArray(unsigned int n, unsigned int value);
    void printFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
    void bubbleSortFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
    void deleteFluxCapacitorArray(FluxCapacitor** array, unsigned int n);

    DeLorean* createDeLorean();
    void deleteDeLorean(DeLorean* d);
    void* assembleDeLorean(void *indices_);
}

#endif // BTTF_H
