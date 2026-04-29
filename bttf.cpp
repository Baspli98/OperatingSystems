#include "bttf.h"
#include <cstdlib>
#include <ctime>
#include "sort.h"

extern pthread_mutex_t mutex;

namespace bttf {
    FluxCapacitor* createFluxCapacitor() {
        FluxCapacitor* fc = new FluxCapacitor;

        //c_string is an char* so,
        //... first, determine a random length for the name (range between 6 and 10)
        int length = std::rand() % 6 + 5;
        //... second, assign the length to a new char*
        fc->c_string = new unsigned char[length + 1];
        //... third, use pointer arithmetic to fill the places
        for(int i = 0; i < length; i++) {
            //... fourth, in the ASCII table letters go from 65 to 90
            //use modulo 26 with rand
            fc->c_string[i] = 'A' + (std::rand() % 26);
        }

        fc->c_string[length] = '\0';

        // Generating a positive non negative random number
        fc->value = std::rand() % 100;

        return fc;
    }

    FluxCapacitor* createFluxCapacitor(unsigned int value) {
        FluxCapacitor* fc = new FluxCapacitor;

        //c_string is an char* so,
        //... first, determine a random length for the name (range between 6 and 10)
        int length = std::rand() % 6 + 5;
        //... second, assign the length to a new char*
        fc->c_string = new unsigned char[length + 1];
        //... third, use pointer arithmetic to fill the places
        for(int i = 0; i < length; i++) {
            //... fourth, in the ASCII table letters go from 65 to 90
            //use modulo 26 with rand
            fc->c_string[i] = 'A' + (std::rand() % 26);
        }

        fc->c_string[length] = '\0';

        fc->value = value;

        return fc;
    }

    FluxCapacitor** createFluxCapacitorArray(unsigned int n) {
        FluxCapacitor** array = new FluxCapacitor*[n];

        for(int i = 0; i < n; i++) {
            array[i] = createFluxCapacitor();
        }
        std::cout << "FluxCapacitorArray generated." << std::endl;
        return array;
    }

    FluxCapacitor** createFluxCapacitorArray(unsigned int n, unsigned int value) {
        FluxCapacitor** array = new FluxCapacitor*[n];

        for(int i = 0; i < n; i++) {
            array[i] = createFluxCapacitor(value);
        }
        std::cout << "FluxCapacitorArray generated." << std::endl;
        return array;
    }

    void printFluxCapacitorArray(FluxCapacitor** array, unsigned int n) {
        std::cout << "----------START PRINTING FluxCapacitorArray----------" << std::endl;
        for(int i = 0; i < n; i++) {
            std::cout << "Array Index: " << i << std::endl;
            std::cout << "Name: " << array[i]->c_string << std::endl;
            std::cout << "Value: " << array[i]->value << std::endl;
        }
        std::cout << "----------END PRINTING FluxCapacitorArray------------" << std::endl;
    }

    void bubbleSortFluxCapacitorArray(FluxCapacitor** array, unsigned int n) {
        sort::bubbleSort(array, n, [](FluxCapacitor* a, FluxCapacitor* b){
            return a->value > b->value;
        });
        std::cout << "FluxCapacitorArray sorted." << std::endl;
    }

    void deleteFluxCapacitorArray(FluxCapacitor** array, unsigned int n) {
        for(int i = 0; i < n; i++) {
            delete[] array[i]->c_string;
            delete array[i];
        }
        delete[] array;
        std::cout << "Deleted Fluxcapacitors!" << std::endl;
    }

    DeLorean* createDeLorean() {
        DeLorean* d = new bttf::DeLorean;
        d->current_power_level_in_mega_watts = 0;
        d->speed_in_kmh = 0;
        std::cout << "Created DeLorean!" << std::endl;
        return d;
    }

    void deleteDeLorean(DeLorean* d) {
        delete d;
        std::cout << "Deleted DeLorean!" << std::endl;
    }

    extern DeLorean* delorean__;
    extern FluxCapacitor** capacitors__;

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
}