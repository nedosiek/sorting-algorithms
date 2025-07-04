#ifndef AIZO_1_HEAPSORT_H
#define AIZO_1_HEAPSORT_H

#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <cstdlib>

using namespace std;

template<typename T>
class HeapSort {
public:
    HeapSort() {
        srand(time(nullptr));
    };
    ~HeapSort() =default;

    // metoda do sortowania przez kopcowanie
    void heap_algorithm(int size, T* array){
        if (array== nullptr){
            throw invalid_argument("Array cannot be null!");
        }
        if (size<=0){
            throw invalid_argument("Size must be positive!");
        }
        if (size==1){
            return;
        }

        for (int i = size/2 - 1; i >=0; i--){
            heapify(array, size, i);
        }

        for (int i= size-1; i>0; i--){
            manual_swap(array[0], array[i]);
            heapify(array, i, 0);
        }
    }

    // sortowanie przez kopcowanie w wersji pijanej
    void heapsort_drunk(T* array, int size, int drunkPercent) {
        if (array== nullptr){
            throw invalid_argument("Array cannot be null!");
        }
        if (size<=0){
            throw invalid_argument("Size must be positive!");
        }
        if (drunkPercent<0 || drunkPercent>100){
            throw invalid_argument("Drunk percent must be 0-100%!");
        }


        // Najpierw standardowe budowanie kopca
        for (int i = size/2 - 1; i >= 0; i--) {
            heapify(array, size, i);
        }

        // Sortowanie z "pijanymi" błędami w trakcie
        for (int i = size-1; i > 0; i--) {
            manual_swap(array[0], array[i]);


            if (rand() % 100 < drunkPercent) {  // % szans na aktywację "pijaństwa" w tej iteracji
                int random_node = rand() % i;
                heapify(array, i, random_node);
            } else{
                heapify(array, i, 0);
            }
        }

        // Ostateczna poprawka (gwarancja poprawności)
        for (int i = size/2 - 1; i >= 0; i--) {
            heapify(array, size, i);
        }
        for (int i = size-1; i > 0; i--) {
            manual_swap(array[0], array[i]);
            heapify(array, i, 0);
        }
    }

private:
    // metoda pomocnicza do swapowania danych
    void manual_swap(T& a, T& b){
        T temp = a;
        a = b;
        b = temp;
    }

    // metoda do przywracania wlasnosci kopca
    void heapify(T* array, int n, int i){
        int largest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;

        if (l < n && array[l] > array[largest])
            largest = l;
        if (r < n && array[r] > array[largest])
            largest = r;
        if (largest!=i){
            manual_swap(array[i], array[largest]);
            heapify(array, n, largest);
        }
    }
};

#endif

