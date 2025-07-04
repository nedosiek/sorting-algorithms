#ifndef AIZO_1_RANDOMARRAY_H
#define AIZO_1_RANDOMARRAY_H

#include <cstdlib>
#include "../algorithms/InsertionSort/InsertionSort.h"
#include "../algorithms/HeapSort/HeapSort.h"
#include <ctime>
#include <type_traits>
#include <limits>
#include <random>
#include <stdexcept>


using namespace std;

template<typename T>
class RandomArray {
public:
    RandomArray()= default;
    ~RandomArray()= default;

    // tworzenie tablicy o elementach losowych
    T* random_values(int size) {
        if (size <=0){
            throw invalid_argument("Size must be positive!");
        }

        random_device rd; // zrodlo losowosci
        mt19937 gen(rd()); // generator Mersenne Twister
        T* tab = nullptr;

        try{
            tab = new T[size];
            if constexpr (is_same<T, int>::value){
                uniform_int_distribution<int> dist(numeric_limits<int>::min(), numeric_limits<int>::max());
                for (int i =0; i<size; i++)
                    tab[i]= dist(gen);
            } else if constexpr (is_same<T, float>::value){
                uniform_real_distribution<float> dist(numeric_limits<float>::min(), numeric_limits<float>::max());
                for (int i =0; i<size; i++)
                    tab[i]= dist(gen);
            } else if constexpr (is_same<T, double>::value){
                uniform_real_distribution<double> dist(numeric_limits<double>::min(), numeric_limits<double>::max());
                for (int i =0; i<size; i++)
                    tab[i]= dist(gen);
            }

            return tab;
        } catch (...){
            delete[] tab;
            throw;
        }
    }


    // sortowanie tablicy losowych elementow rosnaco za pomoca insertion sort
    T* sorted_values(int size){
        T* array = nullptr;
        try {
            array = random_values(size);
            InsertionSort<T> sorter;
            sorter.insertion_algorithm(size, array);
            return array;
        } catch (...){
            delete[] array;
            throw runtime_error("Failed to generate sorted array!");
        }
    }


    // sortowanie tablicy losowych elementow malejaco za pomoca insertion sort
    T* descending_values(int size){
        T* array = nullptr;
        try {
            array = random_values(size);
            InsertionSort<T> sorter;
            sorter.insertion_algorithm_descending(size, array);
            return array;
        } catch(...) {
            delete[] array;
            throw runtime_error("Failed to generate descending array!");
        }
    }


    // sortowanie czesciowe (33%) tablicy losowych elementow za pomoca insertion sort
    T* sorted_33values(int size){
        if (size <=0){
            throw invalid_argument("Size must be positive");
        }

        T* array = nullptr;
        T* sorted_part = nullptr;
        try{
            array = random_values(size);
            int sorted_size = size/3;
            sorted_part = new T[sorted_size];

            for (int i= 0; i<sorted_size; i++){
                sorted_part[i] = array[i];
            }
            InsertionSort<T> sorter;
            sorter.insertion_algorithm(sorted_size, sorted_part);

            for (int i= 0; i<sorted_size; i++){
                array[i] = sorted_part[i];
            }

            delete[] sorted_part;
            return array;
        } catch (...) {
            delete[] array;
            delete[] sorted_part;
            throw runtime_error("Failed to generate 33% sorted array!");
        }
    }

    // sortowanie czesciowe (33%) tablicy losowych elementow za pomoca insertion sort
    T* sorted_66values(int size){
        if (size <=0){
            throw invalid_argument("Size must be positive");
        }

        T* array = nullptr;
        T* sorted_part = nullptr;
        try{
            array = random_values(size);
            int sorted_size = 2*(size/3);
            sorted_part = new T[sorted_size];

            for (int i= 0; i<sorted_size; i++){
                sorted_part[i] = array[i];
            }
            InsertionSort<T> sorter;
            sorter.insertion_algorithm(sorted_size, sorted_part);

            for (int i= 0; i<sorted_size; i++){
                array[i] = sorted_part[i];
            }

            delete[] sorted_part;
            return array;

        } catch (...) {
            delete[] array;
            delete[] sorted_part;
            throw runtime_error("Failed to generate 66% sorted array!");
        }
    }

    // usuniecie tablicy
    static void delete_array(T* tab){
        delete[] tab;
    }

};


#endif

