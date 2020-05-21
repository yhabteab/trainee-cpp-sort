#include <iostream>
#include <vector>
#include <fstream>
#include <getopt.h>
#include <set>
#include <boost/lexical_cast.hpp>

using namespace std;

vector<string> bubbleSort(vector<string> arr, size_t length,
                          bool (*funcCallback)(string &, string &));

void printSortedArray(const vector<string> &arr);

bool checkForEquality(string &firstNum, string &secondNum);

bool checkNumeric(string &firstNum, string &secondNum);

int main(int argc, char **argv) {
    vector<string> stringVector;
    string fileName;
    int options, optionIndex = 0;
    bool isOptionO{false}, isUnique{false};
    bool (*funcCallback)(string &, string &) = checkForEquality;
    static struct option $longOptions[] = {
            {"numeric-sort", no_argument,       nullptr, 'n'},
            {"output",       required_argument, nullptr, 'o'},
            {"unique",       no_argument,       nullptr, 'u'},
    };

    while ((options = getopt_long(argc, argv, "no:u", $longOptions, &optionIndex)) != -1) {
        switch (options) {
            case 'n':
                funcCallback = checkNumeric;
                break;
            case 'o':
                isOptionO = true;
                fileName = optarg;
                break;
            case 'u':
                isUnique = true;
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

    if (isUnique) {
        set<string> s(stringVector.begin(), stringVector.end());
        stringVector.assign(s.begin(), s.end());
    }

    size_t vectorSize = stringVector.size();
    vector<string> sortedElement = bubbleSort(stringVector, vectorSize, funcCallback);
    if (isOptionO) {
        ofstream file{fileName};
        if (file.is_open() && file.good()) {
            for (const auto &line: sortedElement) {
                file << line << endl;
            }

            file.close();
        } else {
            printf("Could not open file name %s", fileName.c_str());
            exit(EXIT_FAILURE);
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
