#include <iostream>
#include <string>

using std::string, 
    std::cout, 
    std::cin, 
    std::cerr;


double getInputX() {

    string input;
    cout << "Enter x: ";
    getline(cin, input);

    if (input.empty()) {
        cerr << "Error: Empty input.";
        exit(1);
    }

    int dotCount = 0;

    for (char& c : input) {
        if (!isdigit(c) && c != '.') {
            cerr << "Error: The entered number is not a double.";
            exit(1);
        }

        if (c == '.') {
            dotCount++;
            if (dotCount > 1) {
                cerr << "Error: The entered number is not a double.";
                exit(1);
            }
        }
    }
    double x = stod(input);

    return x;
}

unsigned short chooseFunctionType() {

    string input;

    cout << "\n" << "Choose f(x) type: " << "\n"
        << "1. x^2" << "\n"
        << "2. e^x" << "\n"
        << "3. sin(x)" << "\n"
        << ">> ";
    getline(cin, input);

    if (input.empty()) {
        cerr << "Error: Empty input.";
        exit(1);
    }

    for (char& c : input) {
        if (!isdigit(c)) {
            cerr << "Error: The entered number is not an integer.";
            exit(1);
        }
    }

    unsigned short f_type = stoi(input);

    return f_type;
}

double calculateFunction(double& x, unsigned short& f_type) {

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
        cerr << "Error: Non-existent option.";
        exit(1);
    }

    return f;
}

double calculateY(double& x, double& f) {

    double y;

    if (x > 0) {
        y = sin(x) / (1 + pow(f, 4));
    }
    else {
        y = cbrt(cos(x) * cos(x));
    }

    return y;
}

int main() {

    double x = getInputX();
    unsigned short f_type = chooseFunctionType();
    double f = calculateFunction(x, f_type);
    double y = calculateY(x, f);

    cout << "\n" << "Result: y = " << y << "\n";
}

