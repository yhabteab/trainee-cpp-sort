#include <iostream>
#include <vector>
#include <fstream>
#include <getopt.h>
#include <boost/lexical_cast.hpp>

using namespace std;

vector<string> bubbleSort(vector<string> arr, size_t length,
                          bool (*funcCallback)(string &, string &));

void printSortedArray(const vector<string> &arr);

bool checkForEquality(string &firstNum, string &secondNum);

bool checkNumeric(string &firstNum, string &secondNum);

int main(int argc, char **argv) {
    vector<string> stringVector;
    int options, optionIndex = 0;
    bool isOptionO{false};
    bool (*funcCallback)(string &, string &) = checkForEquality;
    static struct option $longOptions[] = {
            {"numeric-sort", no_argument,       nullptr, 'n'},
            {"output",       required_argument, nullptr, 'o'},
    };

    while ((options = getopt_long(argc, argv, "no:", $longOptions, &optionIndex)) != -1) {
        switch (options) {
            case 'n':
                funcCallback = checkNumeric;
                break;
            case 'o':
                isOptionO = true;
                break;
            default: /* For invalid option e.g '?' */
                exit(EXIT_FAILURE);
        }
    }

    if (argv[optind] != nullptr) {
        fstream file{argv[optind]};
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
    vector<string> sortedElement = bubbleSort(stringVector, vectorSize, funcCallback);
    if (isOptionO) {
        for (int i = 0; i < argc; ++i) {
            if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                ofstream file{argv[i + 1]};
                if (file.is_open() && file.good()) {
                    for (const auto &line: sortedElement) {
                        file << line << endl;
                    }

                    file.close();
                } else {
                    printf("Could not open file name %s", argv[i + 1]);
                    break;
                }

                break;
            }
        }
    } else {
        printSortedArray(sortedElement);
    }

    return EXIT_SUCCESS;
}

vector<string> bubbleSort(vector<string> arr, size_t length,
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

    return arr;
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
