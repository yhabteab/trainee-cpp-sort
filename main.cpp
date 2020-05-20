#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <boost/lexical_cast.hpp>

using namespace std;

void bubbleSort(vector<string> &arr, size_t length,
                bool (*funcCallback)(string &, string &));

void printSortedArray(const vector<string> &arr);

bool checkForEquality(string &firstNum, string &secondNum);

bool checkNumeric(string &firstNum, string &secondNum);

int main(int argc, char **argv) {
    vector<string> stringVector;
    int $options{};
    bool (* funcCallback)(string &, string &) = checkForEquality;

    while (($options = getopt(argc, argv, "n")) != -1) {
        switch ($options) {
            case 'n':
                funcCallback = checkNumeric;
                break;
            default: /* For invalid option e.g '?' */
                exit(EXIT_FAILURE);
        }
    }

    if (argv[optind] != nullptr) {
        ifstream file{argv[optind]};
        for (string line; getline(file, line);) {
            stringVector.emplace_back(line);
        }

        file.close();
    } else {
        for (string line; getline(cin, line);) {
            stringVector.emplace_back(line);
        }
    }

    size_t vectorSize = stringVector.size();

    bubbleSort(stringVector, vectorSize, funcCallback);
    printSortedArray(stringVector);

    return EXIT_SUCCESS;
}

void bubbleSort(vector<string> &arr, size_t length,
                bool (*funcCallback)(string &, string &)) {
    bool isSwapped = true;

    for (size_t i{0}; (i < length - 1) && (isSwapped); i++) {
        isSwapped = false;
        for (size_t j{0}; j < (length - i) - 1; j++) {
            if (funcCallback(arr.at(j + 1), arr.at(j))) {
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

bool checkForEquality(string &firstNum, string &secondNum) {
    return firstNum < secondNum;
}

bool checkNumeric(string &firstNum, string &secondNum) {
    return boost::lexical_cast<int>(firstNum) < boost::lexical_cast<int>(secondNum);
}
