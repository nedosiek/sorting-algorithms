#ifndef AIZO_1_INSERTIONSORT_H
#define AIZO_1_INSERTIONSORT_H

#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T>
class InsertionSort {
public:
    InsertionSort() =default;
    ~InsertionSort() = default;

    // sortowanie przez wstawianie
    T* insertion_algorithm(int size, T* array){
        if (array== nullptr){
            throw invalid_argument("Array cannot be null!");
        }
        if (size<=0){
            throw invalid_argument("Size cannot be negative!");
        }
        if (size==1){
            return array;
        }


        for (int i=1; i< size; i++){
            T key = array[i];
            int j = i-1;

            while (j>=0 && array[j] > key){
                array[j+1] = array[j];
                j--;
            }
            array[j+1] = key;
        }
        return array;
    }


    // sortowanie przez wstawianie - malejaco
    void insertion_algorithm_descending(int size, T* array){
        if (array== nullptr){
            throw invalid_argument("Array cannot be null!");
        }
        if (size<=0){
            throw invalid_argument("Size cannot be negative!");
        }

        for (int i = 1; i < size; i++) {
            T key = array[i];
            int j = i -1;

            while (j >=0 && array[j] < key) { // UWAGA: tutaj '<'
                array[j + 1] = array[j];
                j--;
            }
            array[j+ 1] = key;
        }
    }
};

#endif //AIZO_1_INSERTIONSORT_H

