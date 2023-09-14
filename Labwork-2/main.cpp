#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

vector<int> inputSequence() {

    vector<int> sequence;
    string inputString;

    cout << "Enter sequence elements separated by spaces: ";
    getline(cin, inputString);
    if (inputString.empty()) {
        cerr << "Error: Empty input.";
        exit(1);
    }
    for (char c : inputString) {
        if (!isdigit(c) && c != ' ') {
            cerr << "Error: There is a non-integer in the sequence.";
            exit(1);
        }
    }

    istringstream iss(inputString);
    int number;
    while (iss >> number) {
        sequence.push_back(number);
    }
    cout << inputString;

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
    cout << endl;
}

int main() {
    vector<int> sequence = inputSequence();
    sort(sequence.begin(), sequence.end());

    vector<int> uniqueNumbers = removeDuplicates(sequence);

    printUniqueNumbers(uniqueNumbers);
}

