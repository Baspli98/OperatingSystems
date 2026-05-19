#include <iostream>
#include "bttf.h"
#include "container.h"
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mem.h"
#include "ed209.h"
#include "fs.h"

using namespace std;

void doAssignment_1(bool doit);
void doAssignment_2(bool doit);
void doAssignment_3(bool doit);
void doAssignment_4(bool doit);

//Global Variables Assignment 2
struct bttf::DeLorean* bttf::delorean__;
struct bttf::FluxCapacitor** bttf::capacitors__;

pthread_mutex_t mutex;

int main()
{
    doAssignment_1(false);
    doAssignment_2(false);
    doAssignment_3(false);
    doAssignment_4(true);
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

void doAssignment_3(bool doit) {
    if (doit) {
        mem::printSystemInfo();
        unsigned int edSimulation[5] = {0xBDDE10, 0x5FFFE, 0x54AC01, 0x540C, 0xFFFFE}; //instructions
        rbt::ED_209* ed = new rbt::ED_209;
        mem::MMU* mmu = new mem::MMU;
        mmu->tlb = mem::createTLB(5);
        mmu->process = mem::createProcess(1);

        ed->mmu = mmu;

        auto pt = ed->mmu->process->page_table;
        //Calculate Page Index from Instruction
        //Put them in Instruction order
        pt->entries[0x2f77]->page_frame_index   = 0x0;
        pt->entries[0x17f]->page_frame_index    = 0x1;
        pt->entries[0x152b]->page_frame_index   = 0x2;
        pt->entries[0x15]->page_frame_index     = 0x3;
        pt->entries[0x3ff]->page_frame_index    = 0x4;

        mem::preprocessInstructions(ed->mmu, edSimulation, 5);
        rbt::startED209(ed);
    }
}

void doAssignment_4(bool doit) {
    if(doit) {
        srand(time(nullptr));

        fs::BsFat* fat = fs::createBsFat(8192, 512);

        fat->blocks[0].state = fs::RESERVED;
        fat->blocks[1].state = fs::RESERVED;

        fat->blocks[5].state = fs::DEFECT;
        fat->blocks[9].state = fs::DEFECT;

        fs::createFile(
            fat,
            1200,
            "FILE1.TXT",
            false,
            false
        );

        fs::createFile(
            fat,
            2000,
            "FILE2.TXT",
            false,
            false
        );

        fs::createFile(
            fat,
            700,
            "TEST.DAT",
            false,
            false
        );

        std::cout << "Initial FAT:" << std::endl;
        fs::showFat(fat);

        std::cout << "Fragmentation: " << fs::getFragmentation(fat) << "%" << std::endl;

        fs::deleteFile(fat, "FILE2.TXT");

        std::cout << "\nAfter delete:" << std::endl;
        fs::showFat(fat);

        fs::createFile(
            fat,
            1800,
            "NEW.BIN",
            false,
            false
        );

        std::cout << "\nAfter new File:" << std::endl;
        fs::showFat(fat);

        std::cout << "Fragmentation: " << fs::getFragmentation(fat) << "%" << std::endl;

        std::cout << "Starting defrag... " << std::endl;
        fs::defragDisk(fat);

        std::cout << "\nAfter defrag:" << std::endl;
        fs::showFat(fat);

        std::cout << "Fragmentation: " << fs::getFragmentation(fat) << "%" << std::endl;
    }
}