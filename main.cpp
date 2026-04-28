#include <iostream>
#include "bttf.h"
#include "container.h"
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void doAssignment_1(bool doit);
void doAssignment_2(bool doit);

struct bttf::DeLorean* delorean__;
struct bttf::FluxCapacitor** capacitors__;

pthread_mutex_t mutex;

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
    pthread_mutex_lock(&mutex);

    container::IndexContainer* idx = static_cast<container::IndexContainer*>(indices_);
    unsigned int sum = 0;

    for (int i = 0; i < idx->array_length; i++) {
        //std::cout << idx->cap_indices[i] << std::endl;
        sum += capacitors__[idx->cap_indices[i]]->value;
    }

    delorean__->current_power_level_in_mega_watts += sum;

    std::cout << "Thread sum added: " << sum << std::endl;

    pthread_mutex_unlock(&mutex);
    return nullptr;
}

void doAssignment_2(bool doit) {
    if(doit) {
        pthread_mutex_init(&mutex, nullptr);

        unsigned int capacitorAmount = 121;
        unsigned int capacitorValue = 10;

        capacitors__ = bttf::createFluxCapacitorArray(capacitorAmount, capacitorValue);
        //bttf::printFluxCapacitorArray(capacitors__, capacitorAmount);
        delorean__ = new bttf::DeLorean;
        delorean__->current_power_level_in_mega_watts = 0;
        delorean__->speed_in_kmh = 0;

        //Create IndexContainer
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

        //Function Call one Thread
        //assembleDeLorean(c1);
        //assembleDeLorean(c2);

        //Threads
        pthread_t t1, t2;

        pthread_create(&t1, nullptr, assembleDeLorean, c1);
        pthread_create(&t2, nullptr, assembleDeLorean, c2);

        pthread_join(t1, nullptr);
        pthread_join(t2, nullptr);

        std::cout << "Current Power Level (Mega Watt): " << delorean__->current_power_level_in_mega_watts << std::endl;

        //Fork - I do not get why we have to set it in the child process.
        pid_t pid = fork();
        if(pid == 0) {
            if(delorean__->current_power_level_in_mega_watts == 1210) {
                delorean__->speed_in_kmh = 144.1;
                std::cout << "Child: 1.21GW achieved!" << std::endl;
            }
            _exit(0);
        } else {
            wait(nullptr);
            std::cout << "Parent: Child finished" << std::endl;
        }

        std::cout << "Final Speed: " << delorean__->speed_in_kmh << std::endl;

        bttf::deleteFluxCapacitorArray(capacitors__, capacitorAmount);

        delete[]c1->cap_indices;
        delete[]c2->cap_indices;

        delete delorean__;

        pthread_mutex_destroy(&mutex);
    }
}