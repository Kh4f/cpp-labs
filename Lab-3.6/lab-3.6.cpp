#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

/*
Тема 3: работа с файлами в C++.
6.Дан текстовый файл f1, содержащий текст на английском языке. 
Отсортировать слова по возрастанию длины и полученный результат записать в файл f2.
*/

// string::empty (until C++11)


std::vector<std::string> textToWordsVector(std::ifstream& inputFile, std::ofstream& outputFile) {
    std::vector<std::string> words;
    std::string word;
    while (inputFile >> word) {
        size_t leftIndex = 0;
        while (leftIndex < word.length() && !std::isalpha(word[leftIndex])) {
            leftIndex++;
        }

        size_t rightIndex = word.length() - 1;
        while (rightIndex > leftIndex && !std::isalpha(word[rightIndex])) {
            rightIndex--;
        }

        if (leftIndex <= rightIndex) {
            words.push_back(word.substr(leftIndex, rightIndex - leftIndex + 1));
        }
    }
    return words; 
}

int main() {
    std::ifstream inputFile("f1.txt");
    std::ofstream outputFile("f2.txt");
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Ошибка открытия файлов.\n";
        return 1;
    }

    std::vector<std::string> words = textToWordsVector(inputFile, outputFile);
    if (words.empty()) {
        std::cerr << "Слова не найдены.\n";
        return 1;
    }
    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    });

    for (const std::string& w : words) {
        outputFile << w << "\n";
    }

    inputFile.close();
    outputFile.close();
    std::cout << "Слова отсортированы и записаны в файл f2.txt\n";
}

