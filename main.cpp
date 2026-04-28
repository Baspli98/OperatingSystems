#include <iostream>
#include "bttf.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void doAssignment_1(bool doit);
void doAssignment_2(bool doit);

struct bttf::DeLorean* delorean__;
struct bttf::FluxCapacitor** capacitors__;

int main()
{
    doAssignment_1(false);
    doAssignment_2(true);
    cout << "---------That's all folks!---------" << endl;
    return 0;
}

void doAssignment_1(bool doit) {
    if(doit) {
        std::srand(std::time(nullptr));
        int fc_amount = 10;
        auto array = bttf::createFluxCapacitorArray(fc_amount);
        bttf::printFluxCapacitorArray(array, fc_amount);
        bttf::bubbleSortFluxCapacitorArray(array, fc_amount);
        bttf::printFluxCapacitorArray(array, fc_amount);
        bttf::deleteFluxCapacitorArray(array, fc_amount);
    }
}

void doAssignment_2(bool doit) {
    if(doit) {
        unsigned int capacitorAmount = 121;
        unsigned int capacitorValue = 10;

        capacitors__ = bttf::createFluxCapacitorArray(capacitorAmount, capacitorValue);
        //bttf::printFluxCapacitorArray(capacitors__, capacitorAmount);
        delorean__ = new bttf::DeLorean;
    }
}