#ifndef BTTF_H
#define BTTF_H

#include <iostream>

namespace bttf {
    struct FluxCapacitor {
        unsigned char* c_string;
        unsigned int value;
    };

    struct DeLorean {
        double speed_in_kmh;
        double current_power_level_in_mega_watts;
    };

    FluxCapacitor* createFluxCapacitor();
    FluxCapacitor* createFluxCapacitor(unsigned int value);
    FluxCapacitor** createFluxCapacitorArray(unsigned int n);
    FluxCapacitor** createFluxCapacitorArray(unsigned int n, unsigned int value);
    void printFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
    void bubbleSortFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
    void deleteFluxCapacitorArray(FluxCapacitor** array, unsigned int n);
}

#endif // BTTF_H
