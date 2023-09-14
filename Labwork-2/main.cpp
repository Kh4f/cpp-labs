//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <sstream>
//using namespace std;
//
//int main() {
//
//    vector<int> sequence;
//    vector<int> uniqueNumbers;
//
//
//    // Ввод элементов последовательности
//    string inputString;
//    cout << "Enter sequence elements separated by spaces: ";
//    getline(cin, inputString);
//    istringstream iss(inputString);
//
//    int number;
//    while (iss >> number) {
//        sequence.push_back(number);
//    }
//
//
//    // Сортировка последовательности
//    sort(sequence.begin(), sequence.end());
//
//
//    // Удаление повторяющихся элементов и формирование уникального массива
//    uniqueNumbers.push_back(sequence[0]);
//    for (int i = 1; i < sequence.size(); ++i) {
//        if (sequence[i] != sequence[i - 1]) {
//            uniqueNumbers.push_back(sequence[i]);
//        }
//    }
//
//
//    // Вывод уникальных чисел
//    cout << "Sequence of unique numbers: ";
//    for (int num : uniqueNumbers) {
//        cout << num << " ";
//    }
//    cout << endl;
//}

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// Функция для ввода последовательности чисел
vector<int> inputSequence() {
    vector<int> sequence;
    string inputString;
    cout << "Enter sequence elements separated by spaces: ";
    getline(cin, inputString);
    istringstream iss(inputString);

    int number;
    while (iss >> number) {
        sequence.push_back(number);
    }
    return sequence;
}

// Функция для удаления повторяющихся элементов и формирования уникального массива
vector<int> removeDuplicates(const vector<int>& sequence) {
    vector<int> uniqueNumbers;
    uniqueNumbers.push_back(sequence[0]);
    for (int i = 1; i < sequence.size(); ++i) {
        if (sequence[i] != sequence[i - 1]) {
            uniqueNumbers.push_back(sequence[i]);
        }
    }
    return uniqueNumbers;
}

// Функция для вывода уникальных чисел
void printUniqueNumbers(const vector<int>& uniqueNumbers) {
    cout << "Sequence of unique numbers: ";
    for (int num : uniqueNumbers) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> sequence = inputSequence();
    sort(sequence.begin(), sequence.end());

    vector<int> uniqueNumbers = removeDuplicates(sequence);

    printUniqueNumbers(uniqueNumbers);
}

