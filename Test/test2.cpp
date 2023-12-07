#include <iostream>
#include <string>
using namespace std;

void extractNumbers(const string& input) {
    string number;
    bool inNumber = false;

    for (char c : input) {
        if (isdigit(c) || c == '-' || c == ',') {
            if (c == '-') {
                // Добавляем минус в число, если он находится в начале числа
                if (number.empty() && !inNumber) {
                    number += c;
                    inNumber = true;
                }
                else {
                    // Иначе это не число, игнорируем
                    inNumber = false;
                }
            }
            else if (isdigit(c)) {
                // Добавляем цифру к числу
                number += c;
                inNumber = true;
            }
            else if (c == ',') {
                // Если встретили запятую, выводим число
                if (inNumber) {
                    cout << number << endl;
                    number.clear();
                    inNumber = false;
                }
            }
        }
        else {
            // Если символ не является цифрой, минусом или запятой,
            // считаем, что это разделитель чисел и сбрасываем число
            if (inNumber) {
                cout << number << endl;
                number.clear();
                inNumber = false;
            }
        }
    }
}

int main() {
    string input = "{4, 3}, {2, 5}, {-1, 3}";
    extractNumbers(input);
    return 0;
}
