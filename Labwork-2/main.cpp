#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using std::vector,
    std::cin,
    std::cout,
    std::cerr;


vector<int> inputSequence() {

    vector<int> sequence;
    std::string inputString;

    cout << "Enter sequence elements separated by spaces: ";
    getline(cin >> std::ws, inputString);

    for (char& i : inputString) {
        if (!isdigit(i) && i != ' ') {
            throw std::invalid_argument("Error: There is a non-integer in the sequence.");
        }
    }

    std::istringstream iss(inputString);
    int number;
    while (iss >> number) {
        sequence.push_back(number);
    }

    return sequence;
}

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

void printUniqueNumbers(const vector<int>& uniqueNumbers) {

    cout << "Sequence of unique numbers: ";
    for (int num : uniqueNumbers) {
        cout << num << " ";
    }
    cout << '\n';
}

int main() {
    vector<int> sequence;
    try {
        sequence = inputSequence();
    }
    catch (const std::invalid_argument& err) {
        cerr << err.what() << '\n';
    }

    sort(sequence.begin(), sequence.end());

    vector<int> uniqueNumbers = removeDuplicates(sequence);

    printUniqueNumbers(uniqueNumbers);
}