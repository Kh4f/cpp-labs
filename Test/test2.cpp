#include <iostream>
#include <string>
#include <regex>
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

double getUserDouble() {

    string input;
    bool valueIsValid = false;

    do {
        valueIsValid = true;
        cout << "Enter x: ";
        getline(cin >> std::ws, input);

        if (input == "-" || input == ".") {
            valueIsValid = false;
        } else if ((input[0] != '-') && !isdigit(input[0]) && (input[0] != '.')) {
            valueIsValid = false;
        } else {
            int dotCount = 0;
            if (input[0] == '.') {
                dotCount++;
            }
            for (int i = 1; i < input.length(); i++) {
                if (input[i] == '.') {
                    dotCount++;
                    if (dotCount > 1) {
                        valueIsValid = false;
                        break;
                    }
                    continue;

                } else if (!isdigit(input[i])) {
                    valueIsValid = false;
                    break;
                }
            }
        }

        if (!valueIsValid) {
            cout << "Error: The entered number is not a double.\n\n";
        }

    } while (!valueIsValid);


    regex pattern("-?(\\d+|\\d*\\.\\d+)");
    if (regex_match(input, pattern)) {
        std::cout << "+\n";
    }

    return stod(input);
}

double getUserDouble2() {
    string input;
    bool valueIsValid = false;
    regex pattern("-?(\\d+|\\d*\\.\\d+)");

    do {
        valueIsValid = true;
        cout << "Enter x: ";
        getline(cin >> std::ws, input);

        if (!regex_match(input, pattern)) {
            valueIsValid = false;
            cout << "Error: The entered number is not a double.\n\n";
        }

    } while (!valueIsValid);

    return stod(input);
}


int main() {
    /*string input = "{4, 3}, {2, 5}, {-1, 3}";
    extractNumbers(input);
    return 0;*/
    while (true) {
        double d = getUserDouble2();
        cout << d << endl;
    }
    /*cout << stod("0");*/
    
}
