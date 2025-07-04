#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Timer.h"
#include "SortMeasure.h"

using namespace std;

void printHelp() {
    cout << "Usage:\n";
    cout << "FILE TEST MODE:\n";
    cout << "./YourProject --file <algorithm> <type> <inputFile> [outputFile]\n";
    cout << "<algorithm> 0-Insertion sort, 1-Heapsort, 2-Shell sort, 3-Quick sort\n";
    cout << "<type> 0-int, 1-float, 2-double\n";
    cout << "<inputFile> Input file with data\n";
    cout << "[outputFile] Optional output file\n\n";

    cout << "BENCHMARK MODE:\n";
    cout << "./YourProject --test <algorithm> <type> <arrayType> <size> <iterations> <outputFile>\n";
    cout << "<algorithm> 0-Insertion sort, 1-Heapsort, 2-Shell sort, 3-Quick sort\n";
    cout << "<type> 0-int, 1-float, 2-double\n";
    cout << "<arrayType> 0-Random, 1-Descending, 2-Partial (33%), 3-Partial (66%), 4-Sorted\n";
    cout << "<size> Number of elements to generate and sort\n";
    cout << "<iterations> Number of iterations\n";
    cout << "<outputFile> File for benchmark results\n\n";

    cout << "HELP MODE:\n";
    cout << "./YourProject --help\n";
    cout << "Displays this message\n\n";

    cout << "EXAMPLE CALLS:\n";
    cout << "./YourProject --file 1 0 input.txt output.txt\n";
    cout << "./YourProject --test 0 1 2 1000 100 results.txt\n";
}

int main(int argc, char* argv[]) {
    // help mode
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "--help") == 0)) {
        printHelp();
        return 0;
    }

    // file test mode
    if (argc >= 5 && strcmp(argv[1], "--file") == 0) {
        if (argc > 6) {
            cerr << "Error: Wrong number of arguments for file mode\n";
            printHelp();
            return -1;
        }

        int algorithm = atoi(argv[2]);
        int type = atoi(argv[3]);
        const string inputFile = argv[4];
        const string outputFile = (argc == 6) ? argv[5] : "";

        switch (type) {
            case 0: SortMeasure<int>::handleFileMode(algorithm, inputFile, outputFile); break;
            case 1: SortMeasure<float>::handleFileMode(algorithm, inputFile, outputFile); break;
            case 2: SortMeasure<double>::handleFileMode(algorithm, inputFile, outputFile); break;
            default:
                cerr << "Invalid data type!" << endl;
                return -1;
        }

        return 0;
    }


    // benchmark mode
    if (argc >= 6 && strcmp(argv[1], "--test") == 0) {
        if (argc <= 6) {
            cerr << "Error: Wrong number of arguments for test mode\n";
            printHelp();
            return -1;
        }

        int algorithm = atoi(argv[2]);
        int type = atoi(argv[3]);
        int arrayType = atoi(argv[4]);
        int size = atoi(argv[5]);
        int iterations = atoi(argv[6]);
        const string outputFile = argv[7];

        // wprowadzenie parametrów dla odpowiednich algorytmów
        if (algorithm == 1) { // Heap Sort
            cout << "Select version: 0-Standard, 1-Drunk\n";
            cin >> SortMeasure<int>::drunk_level;
            if (SortMeasure<int>::drunk_level == 1) {
                cout << "Enter drunk level (0-100%): ";
                cin >> SortMeasure<int>::drunk_level;
            }
        }
        else if (algorithm == 2) { // Shell Sort
            cout << "Select method: 0-Shell, 1-Lazarus\n";
            cin >> SortMeasure<int>::shell_method;
        }
        else if (algorithm == 3) { // Quick Sort
            cout << "Select pivot: 0-Right, 1-Left, 2-Middle, 3-Random\n";
            cin >> SortMeasure<int>::pivot;
        }


        // run benchmark
        for (int i=0; i<iterations; i++)
            SortMeasure<int>::type_menu(algorithm, type, size, arrayType, outputFile);
        return 0;


    }

    // niepoprawne argumenty
    cerr << "Error: Invalid arguments\n";
    printHelp();
    return -1;
}

