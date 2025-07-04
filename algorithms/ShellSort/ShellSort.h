#ifndef AIZO_1_SHELLSORT_H
#define AIZO_1_SHELLSORT_H

#include <cmath>
#include <stdexcept>

using namespace std;

template<typename T>
class ShellSort {
public:
    ShellSort() = default;
    ~ShellSort() = default;

    //sortowanie Shella
    void shell_algorithm(int size, T* array, int given_gap){
        if (array== nullptr){
            throw invalid_argument("Array cannot be null!");
        }
        if (size<=0){
            throw invalid_argument("Size cannot be negative!");
        }
        if (size == 1) {
            return;  // Tablica 1-elementowa jest już posortowana
        }

        switch(given_gap){
            // odstepy klasyczne
            case 0:
                for (int gap = size/2; gap > 0; gap /= 2){
                    for (int i = gap; i < size; i++){
                        T temp = array[i];
                        int j;
                        for (j=i; j>= gap && array[j-gap] > temp; j -=gap){
                            array[j] = array[j-gap];
                        }
                        array[j] = temp;
                    }
                }
                break;

                // odstepy Franka Lazarusa - opisane w sprawozdaniu
            case 1:
                int x=1;
                int gap;
                do {
                    gap = 2*size /pow(2, x++)+1;
                    for (int i=gap; i<size; i++){
                        T temp = array[i];
                        int j;
                        for (j=i; j>=gap && array[j-gap]>temp; j-=gap)
                            array[j]=array[j-gap];

                        array[j]=temp;
                    }
                } while (gap >1);
                break;
        }
    }
};

#endif
