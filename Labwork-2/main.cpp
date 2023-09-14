#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> sequence; // ������ ��� �������� �������� ������������������
    std::vector<int> uniqueNumbers; // ������ ��� �������� ���������� �����

    int n; // ���������� ��������� � ������������������
    std::cout << "������� ���������� ��������� � ������������������: ";
    std::cin >> n;

    // ���� ��������� ������������������
    std::cout << "������� �������� ������������������:\n";
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        sequence.push_back(num);
    }

    // ���������� ������������������
    std::sort(sequence.begin(), sequence.end());

    // �������� ������������� ��������� � ������������ ����������� �������
    uniqueNumbers.push_back(sequence[0]); // ������ ������� ������ ��������
    for (int i = 1; i < n; ++i) {
        if (sequence[i] != sequence[i - 1]) {
            uniqueNumbers.push_back(sequence[i]);
        }
    }

    // ����� ���������� �����
    std::cout << "���������� ����� � ������������������: ";
    for (int num : uniqueNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
