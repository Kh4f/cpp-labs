#include <iostream>

int main() {
	int a = 8;
	int b = 10;

	double c1 = a / b;
	std::cout << c1; // -> 0

	double c2 = a / (double) b;
	std::cout << c2; // -> 0.8
}