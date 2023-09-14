#include <iostream>

using namespace std;


double getInputX() {

    double x{};

    cout << "Enter x: ";

    if (!(cin >> x)) {
        cerr << "Error: The entered number is not a double.";
        exit(1);
    }

    return x;
}

unsigned short chooseFunctionType() {

    unsigned short f_type;

    cout << "\n" << "Choose f(x) type: " << "\n"
        << "1. x^2" << "\n"
        << "2. e^x" << "\n"
        << "3. sin(x)" << "\n"
        << ">> ";
    cin >> f_type;

    return f_type;
}

double calculateFunction(double x, unsigned short f_type) {

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
        cerr << "Error: Invalid input.";
        exit(2);
    }

    return f;
}

double calculateY(double x, double f) {

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

