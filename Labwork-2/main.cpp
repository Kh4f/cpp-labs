#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using std::vector,
    std::cin,
    std::cout,
    std::cerr;


vector<int> inputSequence() {

    vector<std::string> stringSequence;
    vector<int> numSequence;
    std::string inputString;

    cout << "Enter sequence elements separated by spaces: ";
    getline(cin >> std::ws, inputString);

    std::istringstream iss(inputString);
    std::string num;
    while (iss >> num) {
        stringSequence.push_back(num);
    }
    

    for (int i = 0; i < stringSequence.size(); ++i) {
        if (stringSequence[i] == "-") {
            throw std::invalid_argument("Error: There is a non-integer in the sequence.");
        }
        if (stringSequence[i][0] != '-' && !isdigit(stringSequence[i][0])) {
            throw std::invalid_argument("Error: There is a non-integer in the sequence.");
        }
        for (char j = 1; j < stringSequence[i].length(); j++) {
            if (!isdigit(stringSequence[i][j])) {
                throw std::invalid_argument("Error: There is a non-integer in the sequence.");
            }
        }
        numSequence.push_back(stoi(stringSequence[i]));
    }

    return numSequence;
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
    try {
        vector<int> sequence = inputSequence();

        sort(sequence.begin(), sequence.end());

        vector<int> uniqueNumbers = removeDuplicates(sequence);

        printUniqueNumbers(uniqueNumbers);
    }
    catch (const std::invalid_argument& err) {
        cerr << err.what() << '\n';
    }   
}