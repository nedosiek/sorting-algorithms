#ifndef AIZO_1_SORTMEASURE_H
#define AIZO_1_SORTMEASURE_H


#include "../algorithms/InsertionSort/InsertionSort.h"
#include "../algorithms/QuickSort//QuickSort.h"
#include "../algorithms/HeapSort//HeapSort.h"
#include "../algorithms/ShellSort//ShellSort.h"
#include "RandomArray.h"
#include "FileActions.h"
#include <iostream>
#include <stdexcept>
#include "Timer.h"
using namespace std;

template<typename T>
class SortMeasure {
public:
   static int drunk_level;
   static int pivot;
   static int shell_method;


    SortMeasure() = default;
    ~SortMeasure() = default;

    // sprawdza, czy tablica jest posortowana
    static bool isSorted(const T* array, int size) {
        for (int i = 1; i < size; i++) {
            if (array[i-1] > array[i]) return false;
        }
        return true;
    }

    // wywołuje odpowiednie zapytania do użytkownika oraz wywołuje metodę do sortowania
    static void handleFileMode(int algorithm, const string& inputFile, const string& outputFile){
        FileActions<T> fileLoader;
        int size;
        T* data = fileLoader.load_file(inputFile, size);
        if (!data){
            cerr << "Error loading file" << endl;
            exit(-1);
        }

        // Process drunk parameter if HeapSort
        if (algorithm == 1) {
            cout << "Select version: 0-Standard, 1-Drunk\n";
            cin >> drunk_level;
            if (drunk_level == 1) {
                cout << "Enter drunk level (0-100%): ";
                cin >> drunk_level;
            }
        }/*
        else if (algorithm == 2) { // ShellSort
            cout << "Select method: 0-Shell, 1-Lazarus\n";
            cin >> shell_method;
        }*/
        else if (algorithm == 3) { // QuickSort
            cout << "Select pivot: 0-Right, 1-Left, 2-Middle, 3-Random\n";
            cin >> pivot;
        }

        algorithm_menu(algorithm, data, size, outputFile);
        //delete[] data;
    }


    // wywołuje metody w zaleznosci od potrzebnego typu danych
    static void type_menu(int algorithm, int type, int size, int arrayTypeSort, const string filename) {
        switch(type){
            case 0:
                SortMeasure<int>::arrayType_menu(algorithm, size, arrayTypeSort, filename);
                break;
            case 1:
                SortMeasure<float>::arrayType_menu(algorithm, size, arrayTypeSort, filename);
                break;
            case 2:
                SortMeasure<double>::arrayType_menu(algorithm, size, arrayTypeSort, filename);
                break;
            default:
                throw invalid_argument("Invalid data type!");
        }
    }


    // wywołuje metody w zależnosci od potrzebnego poczatkowego rozkladu sortowania zbioru
    static void arrayType_menu(int algorithm, int size, int arrayTypeSort, const string filename){
        if (size<=0){
            throw invalid_argument("Size must be positive!");
        }

        RandomArray<T> random_array;
        T *tab = nullptr;

        try{
            switch (arrayTypeSort){
                case 0:
                    tab = random_array.random_values(size);
                    break;
                case 1:
                    tab = random_array.descending_values(size);
                    break;
                case 2:
                    tab = random_array.sorted_33values(size);
                    break;
                case 3:
                    tab = random_array.sorted_66values(size);
                    break;
                case 4:
                    tab = random_array.sorted_values(size);
                    break;
                default:
                    throw invalid_argument("Invalid array type!");
            }

            if (!tab)
                throw runtime_error("Failed to generate array!");

            algorithm_menu(algorithm, tab, size, filename);
        } catch(...) {
            if (tab)
                RandomArray<T>::delete_array(tab);
            throw;
        }
    }

    // wywoluje odpowiednie metody sortowania oraz liczy czas wykonania algorytmu
    static T* algorithm_menu(int algorithm, T *tab, int size, const string filename) {
            HeapSort<T> heap;
            QuickSort<T> quick;
            ShellSort<T> shell;
            InsertionSort<T> insert;
            Timer timer;

            try {
                timer.reset();
                timer.start();

                switch (algorithm) {
                    case 0:
                        insert.insertion_algorithm(size, tab);
                        break;
                    case 1:
                        if (drunk_level>=0){
                            heap.heapsort_drunk(tab, size, drunk_level);
                        } else {
                            heap.heap_algorithm(size, tab);
                        }
                        break;
                    case 2:
                        shell.shell_algorithm(size, tab, shell_method);
                        break;
                    case 3:
                        quick.quick_sort(size, tab, pivot);
                        break;
                    default:
                        throw invalid_argument("Invalid algorithm!");
                }

                timer.stop();
                timer.result();

                FileActions<T> saving_file(size, tab);
                saving_file.save_file(filename);
                //printArray(size, filename);
                return tab;
            } catch (const exception& e){
                cerr << "Error during sorting " << e.what() << endl;
                throw;
            }
    }

    // wypisuje tablice dla uzytkownika
    static void printArray(int size, string filename){
        T *tab2 = new T[size];
        FileActions<T> file_loader(size, tab2);
        file_loader.load_file(filename);
        delete[] tab2;
    }


};

template<typename T> int SortMeasure<T>::drunk_level = -1;
template<typename T> int SortMeasure<T>::pivot = -1;
template<typename T> int SortMeasure<T>::shell_method = -1;

#endif


