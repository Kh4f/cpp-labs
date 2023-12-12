#include <iostream>
#include <string>
#include <cmath>
#include <regex>
/*
Тема 1: знакомство с языком С++ и программирование линейных алгоритмов.
5.Для заданного x и функции f (x) вычислить значение выражения.
Предусмотреть выбор вида функции f(x) (x^2 ,e^x , sin(x) )
*/


// 1.Множественный импорт имён в using-объявлении (c++17)
using std::cout, std::cin, std::cerr;

// 2.Регулярные выражения (C++11)
double getUserDouble() {
    std::string input;
    bool valueIsValid = false;
    std::regex pattern("-?(\\d+|\\d*\\.\\d+)");

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
//double getUserDouble() {
//    std::string input;
//    bool valueIsValid = false;
//
//    do {
//        valueIsValid = true;
//        cout << "Enter x: ";
//        getline(cin >> std::ws, input);
//
//        if (input == "-" || input == ".") {
//            valueIsValid = false;
//        } else if ((input[0] != '-') && !isdigit(input[0]) && (input[0] != '.')) {
//            valueIsValid = false;
//        } else {
//            int dotCount = 0;
//            if (input[0] == '.') {
//                dotCount++;
//            }
//            for (int i = 1; i < input.length(); i++) {
//                if (input[i] == '.') {
//                    dotCount++;
//                    if (dotCount > 1) {
//                        valueIsValid = false;
//                        break;
//                    }
//                    continue;
//
//                } else if (!isdigit(input[i])) {
//                    valueIsValid = false;
//                    break;
//                }
//            }
//        }
//
//        if (!valueIsValid) {
//            cout << "Error: The entered number is not a double.\n\n";
//        }
//
//    } while (!valueIsValid);
//
//    return stod(input);
//}

int chooseFunctionType() {
    std::string input;
    cout << "\n" << "Choose f(x) type: " << "\n"
        << "1. x^2" << "\n"
        << "2. e^x" << "\n"
        << "3. sin(x)" << "\n"
        << ">> ";
    getline(cin >> std::ws, input);

    for (char& c : input) {
        if (!isdigit(c)) {
            throw std::invalid_argument("Error: The entered number is not an integer.");
        }
    }

    return stoi(input);
}

double calculateFunction(double& x, int& f_type) {
    double f;

    switch (f_type) {
        case 1:
            f = pow(x, 2);
            break;
        case 2:
            f = exp(x);
            break;
        case 3:
            f = sin(x);
            break;
        default:
            throw std::invalid_argument("Error: Non-existent option.");
    }

    return f;
}

double calculateY(double& x, double& f) {
    return (x > 0) ? sin(x) / (1 + pow(f, 4)) : cbrt(cos(x) * cos(x));
}

int main() {
    try {
        double x = getUserDouble();
        int f_type = chooseFunctionType();
        double f = calculateFunction(x, f_type);
        double y = calculateY(x, f);
        cout << "\n" << "Result is: y = " << y << "\n";
    } catch (const std::invalid_argument& err) {
        cerr << err.what() << '\n';
    }
}

//1.using - предотвращение дублирования 'using' + уменьшение шанса получения конфликта имён
//2.regexp - компактность + эффективность 