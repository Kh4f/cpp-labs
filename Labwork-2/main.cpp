//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <sstream>
//using namespace std;
//
//int main() {
//
//    vector<int> sequence;
//    vector<int> uniqueNumbers;
//
//
//    // ���� ��������� ������������������
//    string inputString;
//    cout << "Enter sequence elements separated by spaces: ";
//    getline(cin, inputString);
//    istringstream iss(inputString);
//
//    int number;
//    while (iss >> number) {
//        sequence.push_back(number);
//    }
//
//
//    // ���������� ������������������
//    sort(sequence.begin(), sequence.end());
//
//
//    // �������� ������������� ��������� � ������������ ����������� �������
//    uniqueNumbers.push_back(sequence[0]);
//    for (int i = 1; i < sequence.size(); ++i) {
//        if (sequence[i] != sequence[i - 1]) {
//            uniqueNumbers.push_back(sequence[i]);
//        }
//    }
//
//
//    // ����� ���������� �����
//    cout << "Sequence of unique numbers: ";
//    for (int num : uniqueNumbers) {
//        cout << num << " ";
//    }
//    cout << endl;
//}

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// ������� ��� ����� ������������������ �����
vector<int> inputSequence() {
    vector<int> sequence;
    string inputString;
    cout << "Enter sequence elements separated by spaces: ";
    getline(cin, inputString);
    istringstream iss(inputString);

    int number;
    while (iss >> number) {
        sequence.push_back(number);
    }
    return sequence;
}

// ������� ��� �������� ������������� ��������� � ������������ ����������� �������
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

// ������� ��� ������ ���������� �����
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

