#include <iostream>
#include "bttf.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void doAssignment_1(bool doit);

int main()
{
    doAssignment_1(true);
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
