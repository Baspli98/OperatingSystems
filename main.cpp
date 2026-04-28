#include <iostream>
#include "bttf.h"
#include "container.h"
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

void* assembleDeLorean(void *indices_) {
    container::IndexContainer* idx = static_cast<container::IndexContainer*>(indices_);
    unsigned int sum = 0;

    for (int i = 0; i < idx->array_length; i++) {
        //std::cout << idx->cap_indices[i] << std::endl;
        sum += capacitors__[idx->cap_indices[i]]->value;
    }

    delorean__->current_power_level_in_mega_watts += sum;

    std::cout << "IndexContainer added" << std::endl;
    return nullptr;
}

void doAssignment_2(bool doit) {
    if(doit) {
        unsigned int capacitorAmount = 121;
        unsigned int capacitorValue = 10;

        capacitors__ = bttf::createFluxCapacitorArray(capacitorAmount, capacitorValue);
        //bttf::printFluxCapacitorArray(capacitors__, capacitorAmount);
        delorean__ = new bttf::DeLorean;
        auto c1 = new container::IndexContainer;
        c1->array_length = 21;
        c1->cap_indices = new unsigned int[21];
        for (int i = 0; i < c1->array_length; i++) {
            c1->cap_indices[i] = i;
        }
        auto c2 = new container::IndexContainer;
        c2->array_length = 100;
        c2->cap_indices = new unsigned int[100];
        for (int i = 0; i < c2->array_length; i++) {
            c2->cap_indices[i] = i + 21;
        }

        assembleDeLorean(c1);
        assembleDeLorean(c2);

        std::cout << delorean__->current_power_level_in_mega_watts << std::endl;
    }
}