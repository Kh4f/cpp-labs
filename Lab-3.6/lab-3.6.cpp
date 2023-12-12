#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
/*
Тема 3: работа с файлами в C++.
6.Дан текстовый файл f1, содержащий текст на английском языке. 
Отсортировать слова по возрастанию длины и полученный результат записать в файл f2.
*/


vector<string> textToWordsArray(ifstream& inputFile, ofstream& outputFile) {
    vector<string> words;
    string word;
    while (inputFile >> word) {
        size_t leftIndex = 0;
        while (leftIndex < word.length() && !isalpha(word[leftIndex])) {
            leftIndex++;
        }

        size_t rightIndex = word.length() - 1;
        while (rightIndex > leftIndex && !isalpha(word[rightIndex])) {
            rightIndex--;
        }

        if (leftIndex <= rightIndex) {
            words.push_back(word.substr(leftIndex, rightIndex - leftIndex + 1));
        }
    }
    return words; 
}

// 1.Empty (until C++11)
// 2.Лямбда функция в sort (C++11)
int main() {
    ifstream inputFile("f1.txt");
    ofstream outputFile("f2.txt");
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Ошибка открытия файлов.\n";
        return 1;
    }

    vector<string> words = textToWordsArray(inputFile, outputFile);
    if (words.empty()) {
        cerr << "Слова не найдены.\n";
        return 1;
    }
    sort(words.begin(), words.end(), [](const string& a, const string& b) {return a.length() < b.length();});

    for (const string& w : words) {
        outputFile << w << "\n";
    }

    inputFile.close();
    outputFile.close();
    cout << "Слова отсортированы и записаны в файл f2.txt\n";
}

//1.empty - более нагляден и понятен из-за своего названия + делает код более читаемым
//2.sort w/ lambda - гибкость в сортировке