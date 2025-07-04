#ifndef AIZO_1_FILEACTIONS_H
#define AIZO_1_FILEACTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


using namespace std;

template<typename T>
class FileActions {
protected:
    T* elements_table;
    int number_of_elements;

public:
    FileActions(){
        elements_table = nullptr;
        number_of_elements = 0;
    };

    FileActions(int initialSize, T *tab){
        number_of_elements = initialSize;
        elements_table = tab;
    };

    ~FileActions(){
        delete[] elements_table;
    };

    FileActions(const FileActions&) = delete;
    FileActions& operator=(const FileActions&) = delete;

    // zaladowanie pliku i obsluga bledow
    T* load_file(const string& filename, int& size){
        ifstream MyReadFile(filename);
        if (!MyReadFile.is_open()){
            throw runtime_error("Failed to open file " + filename);
        }

        string line;
        if (!getline(MyReadFile, line)){
            throw runtime_error ("Empty file " + filename);
        }

        stringstream ss_line(line);
        if (!(ss_line >> size)){
            throw runtime_error("Invalid size in file " + filename);
        }

        if (size<=0){
            throw invalid_argument("Size must be positive in file "+ filename);
        }

        T* array = nullptr;
        try {
            array = new T[size];

            for (int i=0; i<size; ++i){
                if (!getline(MyReadFile, line)){
                    throw runtime_error("Unexpected end of the file at line "+to_string(i+1));
                }

                stringstream converter(line);
                if (!(converter >> array[i])){
                    throw runtime_error("Invalid data at line " + to_string(i+2));
                }

                string temp;
                if (converter >> temp){
                    throw runtime_error("Extra data at line " + to_string(i+2));
                }
            }
        } catch (...) {
            delete[] array;
            throw;
        }
       // MyReadFile.close();
        return array;
    }


    // wczytywanie do pliku i obsluga bledow
    void save_file(const string& filename) const{
        if (number_of_elements<=0 || elements_table== nullptr){
            throw runtime_error("No data to save");
        }

        ofstream MySaveFile(filename);
        if (!MySaveFile.is_open()){
            throw runtime_error("Failed to create file " + filename);
            return;
        }

        MySaveFile << number_of_elements << endl;
        for (int i =0; i< number_of_elements; ++i){
            if (!(MySaveFile << elements_table[i] << endl)){
                throw runtime_error("Write error at element " + to_string(i));
            }
        }
    }

    // wypisywanie tablicy z pliku
    void print() const{
        cout << "{";
        for (int i=0; i < number_of_elements; ++i){
            cout << elements_table[i];
            if (i < number_of_elements-1) cout << ", ";
        }
        cout << "}" <<endl;
    }

    T* get_data() const {
        return elements_table;
    }
    int size(){
        return number_of_elements;
    }
};

#endif

