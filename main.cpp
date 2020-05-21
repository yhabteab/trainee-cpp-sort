#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <getopt.h>
#include <set>
#include <map>
#include <boost/lexical_cast.hpp>

using namespace std;

void bubbleSort(vector<string> &arr, size_t length,
                bool (*funcCallback)(string &, string &));

void quickSort(vector<string> &arr, int low, int high,
               bool (*funcCallback)(string &, string &));

void printSortedArray(const vector<string> &arr);

bool checkForEquality(string &firstNum, string &secondNum);

bool checkNumeric(string &firstNum, string &secondNum);

template<typename T, typename Key>
bool key_exists(const T &container, const Key &key);

int main(int argc, char **argv) {
    vector<string> stringVector;
    string fileName;
    map<string, string> mapOption{};
    int options, optionIndex = 0;
    bool (*funcCallback)(string &, string &) = checkForEquality;
    static struct option $longOptions[] = {
            {"numeric-sort",          no_argument,       nullptr, 'n'},
            {"output",                required_argument, nullptr, 'o'},
            {"unique",                no_argument,       nullptr, 'u'},
            {"ignore-leading-blanks", no_argument,       nullptr, 'b'},
            {"ignore-case",           no_argument,       nullptr, 'f'},
            {"random-sort",           no_argument,       nullptr, 'R'},
            {"reverse",               no_argument,       nullptr, 'r'},
            {"quick-sort",            no_argument,       nullptr, 'q'},
    };

    while ((options = getopt_long(argc, argv, "no:ubfRrq", $longOptions, &optionIndex)) != -1) {
        switch (options) {
            case 'n':
                mapOption.insert(make_pair("n", "numeric-sort"));
                funcCallback = checkNumeric;
                break;
            case 'o':
                mapOption.insert(make_pair("o", "output"));
                fileName = optarg;
                break;
            case 'u':
                mapOption.insert(make_pair("u", "unique"));
                break;
            case 'b':
                mapOption.insert(make_pair("b", "ignore-leading-blanks"));
                break;
            case 'f':
                mapOption.insert(make_pair("f", "ignore-case"));
                break;
            case 'R':
                mapOption.insert(make_pair("R", "random-sort"));
                break;
            case 'r':
                mapOption.insert(make_pair("r", "reverse"));
                break;
            case 'q':
                mapOption.insert(make_pair("q", "quick-sort"));
                break;
            default: /* For invalid option e.g '?' */
                exit(EXIT_FAILURE);
        }
    }

    if (argv[optind] != nullptr) {
        fstream file{argv[optind]};
        for (string line; getline(file, line);) {
            if (key_exists(mapOption, "b") && line.empty()) {
                continue;
            }

            stringVector.emplace_back(line);
        }

        file.close();
    } else {
        for (string line; getline(cin, line);) {
            if (key_exists(mapOption, "b") && line.empty()) {
                continue;
            }

            stringVector.emplace_back(line);
        }
    }

    if (key_exists(mapOption, "u")) {
        set<string> s(stringVector.begin(), stringVector.end());
        stringVector.assign(s.begin(), s.end());
    } else if (key_exists(mapOption, "f")) {
        for (auto &line : stringVector) {
            for (auto &c : line) {
                c = toupper(c);
            }
        }
    }

    int vectorSize = stringVector.size();

    if (key_exists(mapOption, "R")) {
        random_device randomDevice;
        shuffle(stringVector.begin(), stringVector.end(), randomDevice);
    } else if (key_exists(mapOption, "q")) {
        quickSort(stringVector, 0, vectorSize - 1, funcCallback);
    } else {
        bubbleSort(stringVector, vectorSize, funcCallback);
    }

    if (key_exists(mapOption, "r")) {
        reverse(stringVector.begin(), stringVector.end());
    }

    if (key_exists(mapOption, "o")) {
        ofstream file{fileName};
        if (file.is_open() && file.good()) {
            for (const auto &line: stringVector) {
                file << line << endl;
            }

            file.close();
        } else {
            printf("Could not open file name %s", fileName.c_str());
            exit(EXIT_FAILURE);
        }
    } else {
        printSortedArray(stringVector);
    }

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

void quickSort(vector<string> &arr, int low, int high,
               bool (*funcCallback)(string &, string &)) {
    if (low < high) {
        string pivot = arr.at(high);
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (funcCallback(arr.at(j), pivot)) {
                i++;
                swap(arr.at(i), arr.at(j));
            }
        }

        swap(arr.at(i + 1), arr.at(high));

        int newPivot = i + 1;

        quickSort(arr, low, newPivot - 1, funcCallback);
        quickSort(arr, newPivot + 1, high, funcCallback);
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
    if (firstNum.empty() || secondNum.empty()) {
        return false;
    }
    char character2, character1;

    string::const_iterator it = firstNum.begin();
    string::const_iterator iterator = secondNum.begin();
    while (it != firstNum.end() && isdigit(*it)) ++it;
    while (iterator != secondNum.end() && isdigit(*iterator)) ++iterator;

    if (!firstNum.empty() && it == firstNum.end() && !secondNum.empty() && iterator == secondNum.end()) {
        return boost::lexical_cast<int>(firstNum) < boost::lexical_cast<int>(secondNum);
    } else {
        for (auto &lin : firstNum) {
            character1 = lin;
        }

        for (auto &line : secondNum) {
            character2 = line;
        }

        return (int) character1 < (int) character2;
    }
}

template<typename T, typename Key>
bool key_exists(const T &container, const Key &key) {
    return container.find(key) != end(container);
}
