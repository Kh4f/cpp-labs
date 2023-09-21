#include <iostream>
#include <string>

using std::cout, 
    std::cin, 
    std::cerr;


double getInputX() {

    std::string input;
    cout << "Enter x: ";
    getline(cin >> std::ws, input);

    if (input == "-") {
        throw std::invalid_argument("Error: There is a non-integer in the sequence.");
    }
    if (input[0] != '-' && !isdigit(input[0])) {
        throw std::invalid_argument("Error: The entered number is not a double.");
    }

    int dotCount = 0;
    for (int i = 1; i < input.length(); i++) {    
        if (input[i] == '.') {
            dotCount++;
            if (dotCount > 1) {
                throw std::invalid_argument("Error: The entered number is not a double.");
            }
            continue;
        } else if (!isdigit(input[i])) {
            throw std::invalid_argument("Error: The entered number is not a double.");
        }
    }
    return stod(input);
}

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

    return (x > 0) ? sin(x)/(1 + pow(f, 4)) : cbrt(cos(x) * cos(x));
}

int main() {
    try {
        double x = getInputX();
        int f_type = chooseFunctionType();
        double f = calculateFunction(x, f_type);
        double y = calculateY(x, f);
        cout << "\n" << "Result is: y = " << y << "\n";
    }
    catch (const std::invalid_argument &err) {
        cerr << err.what() << '\n';
    } 
}