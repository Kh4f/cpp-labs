#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> sequence; // Вектор для хранения исходной последовательности
    std::vector<int> uniqueNumbers; // Вектор для хранения уникальных чисел

    int n; // Количество элементов в последовательности
    std::cout << "Введите количество элементов в последовательности: ";
    std::cin >> n;

    // Ввод элементов последовательности
    std::cout << "Введите элементы последовательности:\n";
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        sequence.push_back(num);
    }

    // Сортировка последовательности
    std::sort(sequence.begin(), sequence.end());

    // Удаление повторяющихся элементов и формирование уникального массива
    uniqueNumbers.push_back(sequence[0]); // Первый элемент всегда уникален
    for (int i = 1; i < n; ++i) {
        if (sequence[i] != sequence[i - 1]) {
            uniqueNumbers.push_back(sequence[i]);
        }
    }

    // Вывод уникальных чисел
    std::cout << "Уникальные числа в последовательности: ";
    for (int num : uniqueNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
