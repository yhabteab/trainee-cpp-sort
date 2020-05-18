#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>


using namespace std;

void bubbleSort(vector<string> &arr, size_t length);

void printSortedArray(const vector<string> &arr);

int main(int argc, char **argv) {
    vector<string> stringVector;

    if (argc > 1 && strcmp(argv[1], "-") != 0) {
        ifstream file{argv[1]};
        for (string line; getline(file, line);) {
            stringVector.emplace_back(line);
        }

        file.close();
    } else {
        for (string line; getline(cin, line);) {
            stringVector.emplace_back(line);
        }
    }

    bubbleSort(stringVector, stringVector.size());
    printSortedArray(stringVector);

    return EXIT_SUCCESS;
}

void bubbleSort(vector<string> &arr, size_t length) {
    bool isSwapped = true;

    for (size_t i{0}; (i < length - 1) && (isSwapped); i++) {
        isSwapped = false;
        for (size_t j{0}; j < (length - i) - 1; j++) {
            if (arr.at(j + 1) < arr.at(j)) {
                swap(arr.at(j + 1), arr.at(j));

                isSwapped = true;
            }
        }
    }
}

void printSortedArray(const vector<string> &arr) {
    for (const auto &num: arr) {
        cout << num << endl;
    }
}
