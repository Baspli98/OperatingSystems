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

//Global Variables Assignment 2
struct bttf::DeLorean* bttf::delorean__;
struct bttf::FluxCapacitor** bttf::capacitors__;

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

void doAssignment_2(bool doit) {
    if(doit) {
        pthread_mutex_init(&mutex, nullptr);

        unsigned int capacitorAmount = 121;
        unsigned int capacitorValue = 10;

        bttf::capacitors__ = bttf::createFluxCapacitorArray(capacitorAmount, capacitorValue);
        bttf::delorean__ = bttf::createDeLorean();

        auto c1 = container::createIndexContainer(21, 21);
        auto c2 = container::createIndexContainer(100, 100, c1);

        //Threads
        pthread_t t1, t2;

        pthread_create(&t1, nullptr, bttf::assembleDeLorean, c1);
        pthread_create(&t2, nullptr, bttf::assembleDeLorean, c2);

        pthread_join(t1, nullptr);
        pthread_join(t2, nullptr);

        std::cout << "Current Power Level (Mega Watt): " << bttf::delorean__->current_power_level_in_mega_watts << std::endl;

        //Fork
        pid_t pid = fork();
        if(pid == 0) {
            if(bttf::delorean__->current_power_level_in_mega_watts == 1210) {
                bttf::delorean__->speed_in_kmh = 144.1;
                std::cout << "Child: 1.21GW achieved!" << std::endl;
                std::cout << "Final Speed: " << bttf::delorean__->speed_in_kmh << std::endl;
            }
            _exit(0);
        } else {
            wait(nullptr);
            std::cout << "Parent: Child finished" << std::endl;
        }

        bttf::deleteFluxCapacitorArray(bttf::capacitors__, capacitorAmount);

        container::deleteIndexContainer(c1);
        container::deleteIndexContainer(c2);

        bttf::deleteDeLorean(bttf::delorean__);

        pthread_mutex_destroy(&mutex);
    }
}