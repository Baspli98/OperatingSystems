#ifndef SORT_H
#define SORT_H

namespace sort {
    template <typename T, typename Compare>
    void bubbleSort(T* array, int n, Compare comp) {
        for(int i = 0; i < n - 1; i++) {
            for(int j = 0; j < n - i - 1; j++) {
                if(comp(array[j], array[j + 1])) {
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
}

#endif // SORT_H
