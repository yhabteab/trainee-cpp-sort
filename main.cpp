#include <iostream>
#include <fstream>
#include <vector>
#include <getopt.h>
#include <set>
#include <map>
#include <boost/lexical_cast.hpp>

using namespace std;

vector<string> bubbleSort(vector<string> arr, size_t length,
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
    };

    while ((options = getopt_long(argc, argv, "no:ubf", $longOptions, &optionIndex)) != -1) {
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

    size_t vectorSize = stringVector.size();
    vector<string> sortedElement = bubbleSort(stringVector, vectorSize, funcCallback);
    if (key_exists(mapOption, "o")) {
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
    if (firstNum.empty() || secondNum.empty()) {
        return false;
    }

    try {
        return boost::lexical_cast<int>(firstNum) < boost::lexical_cast<int>(secondNum);
    } catch (boost::bad_lexical_cast &$error) {
        return static_cast<int>(boost::lexical_cast<char>(firstNum)) <
               static_cast<int>(boost::lexical_cast<char>(secondNum));
    }
}

template<typename T, typename Key>
bool key_exists(const T &container, const Key &key) {
    return container.find(key) != end(container);
}
