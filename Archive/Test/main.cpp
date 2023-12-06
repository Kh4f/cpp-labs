//#include <iostream>
//using namespace std;
//
//void test1() {
//    char s[] = "ldjxjpxovjtoalmi";
//    int a[] = { 6, 0, 4, 2, 3, 7, 0, 4, 3, 8 };
//    for (int i = 0; i < 10; i++) {
//        cout << *(s + *(a + i));
//    }
//}
//
//void test2() {
//    int a = 0, b = -1, c = -1;
//
//    if (++a && ++b || ++c) {
//        
//    }
//    else {
//        cout << -a;
//        cout << -b;
//        cout << -c;
//    }
//}
//
//int main() {
//    test2();
//}

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main() {
    std::string inputString = "Значение1; Значение2; Значение3; Значение4";
    std::string delimiter = "; ";
    std::vector<std::string> result;

    std::istringstream ss(inputString);
    std::string token;

    while (std::getline(ss, token, delimiter[0])) {
        result.push_back(token);
    }

    // Выводим элементы вектора
    for (const std::string& item : result) {
        std::cout << item << std::endl;
    }

    return 0;
}



