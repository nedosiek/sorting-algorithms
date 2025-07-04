#ifndef AIZO_1_QUICKSORT_H
#define AIZO_1_QUICKSORT_H

#include <algorithm>
#include <iostream>
#include <ctime>
#include <stdexcept>

using namespace std;

template<typename T>
class QuickSort {
public:
    QuickSort() {
        srand(time(nullptr));
    };
    ~QuickSort() = default;

    // funkcja, ktora obsluguje sortowanie szybkie
    void quick_sort(int size, T *array, int pivot_stategy){
        if (array== nullptr){
            throw invalid_argument("Array cannot be null!");
        }
        if (size<=0){
            throw invalid_argument("Size must be positive!");
        }
        if (pivot_stategy<0 || pivot_stategy>3){
            throw invalid_argument("Invalid pivot chosen!");
        }


        quick_algorithms(array, 0, size-1, pivot_stategy);
    }

private:
    // metoda pomocnicza do swapowania danych
    void manual_swap(T* a, T* b){
        T temp = *a;
        *a = *b;
        *b = temp;
    }


    // partycja
    int partition(T* array, int left, int right, int strategy){
        int pivot_index = select_pivot(left, right, strategy);
        T pivot = array[pivot_index];

        manual_swap(&array[pivot_index], &array[right]);

        int store_id = left;
        for (int i=left; i<right; i++){
            if (array[i]<=pivot){
                manual_swap(&array[i], &array[store_id]);
                store_id++;
            }
        }

        manual_swap(&array[store_id], &array[right]);
        return store_id;
    }

    // wybranie pivota, zadanego przez uzytkownika
    int select_pivot(int left, int right, int strategy){
        switch (strategy) {
            case 0:
                return right;
            case 1:
                return left;
            case 2:
                return (left+right)/2;
            case 3:
                return left + rand() % (right-left+1);
            default:
                return right;
        }
    }

    // działanie sortowanie szybkiego - rekurencyjnie "dziel i zwyciezaj"
    void quick_algorithms(T* array, int l, int r, int strategy){
        if (l < r) {
            int piv = partition(array, l, r, strategy);
            quick_algorithms(array, l, piv-1, strategy);
            quick_algorithms(array, piv+1, r, strategy);
        }
    }
};

#endif