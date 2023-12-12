#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
/*
Тема 2: работа с массивами и указателями, функции.
5.Для заданной последовательности целых чисел (среди которых могут быть повторяющиеся)
составить массив из чисел, которые входят в последовательность по одному разу.
*/


// 1.Множественный импорт имён в using-объявлении (c++17)
using std::vector, std::cin, std::cout, std::cerr;

// 2.Регулярные выражения (C++11) + auto
bool isValidInteger(std::string& value) {
    constexpr auto patternStr = "-?\\d+";
     std::regex pattern(patternStr);
    return regex_match(value, pattern);
}
//bool isValidInteger(std::string& value) {
//    bool valueIsValid = true;
//
//    if (value == "-") {
//        valueIsValid = false;
//    } else if ((value[0] != '-') && !isdigit(value[0])) {
//        valueIsValid = false;
//    } else {
//        for (int i = 1; i < value.length(); i++) {
//            if (!isdigit(value[i])) {
//                valueIsValid = false;
//                break;
//            }
//        }
//    }
//
//    return valueIsValid;
//}

// 3.Auto keyword (C++11).
auto inputSequence() {

    vector<std::string> stringSequence;
    vector<int> numSequence;
    std::string inputString;

    cout << "Enter sequence elements separated by spaces: ";
    getline(cin >> std::ws, inputString);

    std::istringstream iss(inputString);
    std::string num;
    while (iss >> num) {
        stringSequence.push_back(num);
    }

    for (int i = 0; i < stringSequence.size(); ++i) { 
        if (isValidInteger(stringSequence[i])) {
            numSequence.push_back(stoi(stringSequence[i]));
        } else {
            throw std::invalid_argument("Error: There is a non-integer in the sequence.");
        }
    }

    return numSequence;
}

// Auto keyword
auto removeDuplicates(const vector<int>& sequence) {

    vector<int> uniqueNumbers;

    uniqueNumbers.push_back(sequence[0]);
    for (int i = 1; i < sequence.size(); ++i) {
        if (sequence[i] != sequence[i - 1]) {
            uniqueNumbers.push_back(sequence[i]);
        }
    }

    return uniqueNumbers;
}

void printUniqueNumbers(const vector<int>& uniqueNumbers) {

    cout << "Sequence of unique numbers: ";
    for (int num : uniqueNumbers) {
        cout << num << " ";
    }
    cout << '\n';
}

// 4.Лямбда функция в sort (C++11)
int main() {
    try {
        vector<int> sequence = inputSequence();
        sort(sequence.begin(), sequence.end(), [](int a, int b) { return a < b; });

        vector<int> uniqueNumbers = removeDuplicates(sequence);
        printUniqueNumbers(uniqueNumbers);
    }
    catch (const std::invalid_argument& err) {
        cerr << err.what() << '\n';
    }   
}

//1.using - предотвращение дублирования 'using' + уменьшение шанса получения конфликта имён
//2.regexp - эффективность + компактность
//3.auto - компактность кода + гибкость в случае изменения типа возвращаемого значения в будущем без необходимости изменения сигнатуры функции
//4.sort w/ lambda - без неё тоже работает, но для более точного сравнения... крч гибкость в сортировке