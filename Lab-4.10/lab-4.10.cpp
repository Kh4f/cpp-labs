#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;
/*
Тема 4: пользовательские типы данных (структуры, объединения, перечисления).
10.Описать структуру, содержащую информацию о деятельности музея. 
Поля структуры должны включать информацию о сотрудниках, залах, экспонатах, экскурсиях и т.п. 
Создать файл данных, содержащий сведения о нескольких экспонатах. 
Написать программу, позволяющую добавлять новые экспонаты (с сохранением данных в файл),
а также выбирать и выводить необходимую информацию об имеющихся экспонатах на экран. 
Например, вывести список всех экспонатов второго зала. Формы запросов придумать самостоятельно.
*/


// constexpr + getUserInteger - regex
//1.Регулярные выражения (C++11)
//2.Constexpr (C++11)
struct MyMuseum {

    struct Exhibit {
        string name;
        string author;
        int creationYear;
        string description;
        int hallNumber;

        void displayInfo() {
            cout << "Имя: \033[4m" << name << "\033[0m;\n"
                << "Автор: " << author << ";\n"
                << "Год создания: " << creationYear << ";\n"
                << "Описание: " << description << ";\n"
                << "Номер зала: " << hallNumber << ".\n\n";
        }
    };

    struct Employee {
        string name;
        string position;
        double salary;
    };

    struct Hall {
        int number;
        int capacity;
        vector<Exhibit> exhibits;
    };

    struct Excursion {
        int duration_min;
        Employee guide;
        double cost;
    };

    string name;
    string address;
    vector<Hall> halls;
    vector<Employee> employees;
    vector<Excursion> excursions;

    MyMuseum(string name, string address) {
        this->name = name;
        this->address = address;
    }

    void readExhibitsFromFile(ifstream& file) {
        std::string line;
        while (getline(file, line)) {
            std::istringstream ss(line);

            string name, author, yearStr, description, hallNumberStr;
            getline(ss, name, ';');
            getline(ss, author, ';');
            getline(ss, yearStr, ';');
            getline(ss, description, ';');
            getline(ss, hallNumberStr);
            int year = std::stoi(yearStr);
            int hallNumber = std::stoi(hallNumberStr);

            addExhibit(name, author, description, year, hallNumber);
        }
        file.close();
    }

    void addExhibit(string& name, string& author, string& description, int& year, int& hallNumber) {
        Exhibit exhibit;
        exhibit.name = name;
        exhibit.author = author;
        exhibit.creationYear = year;
        exhibit.description = description;
        exhibit.hallNumber = hallNumber;

        bool hallExists = false;
        for (Hall& hall : halls) {
            if (hall.number == hallNumber) {
                hallExists = true;
                hall.exhibits.push_back(exhibit);
                break;
            }
        }
        if (!hallExists) {
            Hall hall;
            hall.number = hallNumber;
            hall.exhibits.push_back(exhibit);
            halls.push_back(hall);
        }
    }
};

void drawMenu(int& selected, string& header, vector<string> options) {
    system("cls");

    cout << header << "\n";
    for (int i = 0; i < options.size(); i++) {
        
        if (i == selected) {
            cout << " -> ";
        }
        else {
            cout << "    ";
        }
        cout << i + 1 << "." << options[i] << "\n"; 
    }
}

int getSelectedOption(string header, vector<string> options) {
    int selected = 0;
    bool redrawMenu = true;

    while (true) {
        if (redrawMenu) {
            drawMenu(selected, header, options);
        }

        // Ожидание ввода
        char input = _getch();
        switch (input) {
        case 72: // Стрелка вверх
            if (selected > 0) {
                selected--;
                redrawMenu = true;
            }
            break;
        case 80: // Стрелка вниз
            if (selected < options.size() - 1) {
                selected++;
                redrawMenu = true;
            }
            break;
        case 13: // Enter
            return selected+1;
            break;
        default: // Не перерисовывать меню для любой другой клавиши
            redrawMenu = false;
            break;
        }
    }
}

void replaceDelimToSpace(string& str) {
    replace_if(str.begin(), str.end(), [](char c) { return c == ';'; }, ' ');
}

void writeExhibitToFile(string& name, string& author, string& description, int& year, int& hallNumber) {
    ofstream outputFile("exhibits.txt", ios::app);

    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл. \n";
        exit(1);
    }

    outputFile << name << ";"
        << author << ";"
        << year << ";"
        << description << ";"
        << hallNumber << "\n";

    outputFile.close();
}


// 1.RegExp (C++11)
int getUserInteger(string header, bool positiveInt = false) {
    string input;
    bool valueIsValid = false;
    string patternString = positiveInt ? "\\d+" : "-?\\d+";
    regex pattern(patternString);

    do {
        valueIsValid = true;
        cout << header;
        getline(cin >> std::ws, input);

        if (!regex_match(input, pattern)) {
            valueIsValid = false;
            cout << "Некорректный ввод. Попробуйте ещё раз.\n" ;
        }

    } while (!valueIsValid);

    return stoi(input);
}
/*int getUserInteger(string header) {
    string input;
    bool valueIsValid = false;

    do {
        valueIsValid = true;
        cout << header;
        getline(cin >> ws, input);

        if (input == "-") {
            valueIsValid = false;
        } else if ((input[0] != '-') && !isdigit(input[0])) {
            valueIsValid = false;
        } else {
            for (int i = 1; i < input.length(); i++) {
                if (!isdigit(input[i])) {
                    valueIsValid = false;
                    break;
                }
            }
        }

        if (!valueIsValid) {
            cout << "Требуется целое число. Попробуйте ещё раз.\n";
        }

    } while (!valueIsValid);

    return stoi(input);
}*/
/*int getPositiveInteger(string header) {
    string input;
    bool valueIsValid = false;

    do {
        valueIsValid = true;
        cout << header;
        getline(cin >> ws, input);

        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) {
                valueIsValid = false;
                break;
            }
        }

        if (!valueIsValid) {
            cout << "Требуется целое число. Попробуйте ещё раз.\n";
        }

    } while (!valueIsValid);

    return stoi(input);
}*/


void waitToPressEnter() {
    cout << "(Нажмите Enter, чтобы вернуться)";
    while (true) {
        char input = _getch();
        if (input == 13) {
            break;
        }
    }
}

void createNewExhibit(MyMuseum& myMuseum) {
    string name, author, yearStr, description, hallNumberStr;

    system("cls");
    cout << "Введите данные об экспонате: \n";
    cout << "Имя: ";
    getline(cin >> ws, name);
    replaceDelimToSpace(name);

    cout << "Автор: ";
    getline(cin >> ws, author);
    replaceDelimToSpace(author);
    
    int year = getUserInteger("Год создания: ");

    cout << "Описание: ";
    getline(cin >> ws, description);
    replaceDelimToSpace(description);
    
    int hallNumber = getUserInteger("Номер зала: ", true);

    myMuseum.addExhibit(name, author, description, year, hallNumber);
    writeExhibitToFile(name, author, description, year, hallNumber);
    cout << "\nЭкспонат успешно добавлен.\n";
    waitToPressEnter();
}

void chooseActionOnExhibits(MyMuseum& myMuseum) {
    bool exitLoop = false;

    while (!exitLoop) {
        int selectedAction = getSelectedOption("Выберите действие:", 
            { "Вывести экспонаты всего музея", 
            "Вывести экспонаты выбранного зала", 
            "Вывести экспонаты, отфильтровав по году создания", 
            "<-" });
        switch (selectedAction) {
        case 1: {
            system("cls");
            bool exhibitExists = false;
            for (MyMuseum::Hall& hall : myMuseum.halls) {
                for (MyMuseum::Exhibit& exhibit : hall.exhibits) {
                    exhibitExists = true;
                    exhibit.displayInfo();
                }
            }
            if (!exhibitExists) {
                cout << "Экспонаты отсутствуют. \n";
            }
            waitToPressEnter();
            break;
        }
        case 2: {
            int number = getUserInteger("\nВведите номер зала: ", true);
            system("cls");

            bool hallExists = false;
            for (MyMuseum::Hall& hall : myMuseum.halls) {
                if (hall.number == number) {
                    hallExists = true;
                    for (MyMuseum::Exhibit& exhibit : hall.exhibits) {
                        exhibit.displayInfo();
                    }
                    break;
                }
            }
            if (!hallExists) {
                cout << "В выбранном зале нет экспонатов. \n";
            }
            waitToPressEnter();
            break;
        }
        case 3: {
            int minYear = getUserInteger("\nВведите первый год диапазона: ");
            int maxYear = getUserInteger("Введите второй год диапазона: ");
            if (maxYear < minYear) {
                int temp = maxYear;
                maxYear = minYear;
                minYear = temp;
            }

            system("cls");
            bool exhExist = false;
            for (MyMuseum::Hall& hall : myMuseum.halls) {
                for (MyMuseum::Exhibit& exhibit : hall.exhibits) {
                    if ((exhibit.creationYear >= minYear) && (exhibit.creationYear <= maxYear)) {
                        exhExist = true;
                        exhibit.displayInfo();
                    }   
                }
            }

            if (!exhExist) {
                cout << "Искомые экспонаты отсутствуют. \n";
            }
            waitToPressEnter();
            break;
        }
        case 4:
            exitLoop = true;
            break;
        }
    }  
}

void runMainMenu(MyMuseum& myMuseum) {
    bool exitLoop = false;
    while (!exitLoop) {
        int selectedAction = getSelectedOption("Выберите действие:", { "Добавить новый экспонат", "Выбрать экспонаты", "Выйти" });
        switch (selectedAction) {
        case 1:
            createNewExhibit(myMuseum);
            break;
        case 2:
            chooseActionOnExhibits(myMuseum);
            break;
        case 3:
            exitLoop = true;
            break;
        }
    }
}

// 2.Constexpr specifier (C++11)
int main() {
    constexpr auto museumName = "Test Museum";
    constexpr auto museumAddress = "24 Stark Parkways, Lindystad, KY";
    MyMuseum myMuseum(museumName, museumAddress);

    ifstream file("exhibits.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл 'exhibits.txt'. \n";
        return 1;
    }
    myMuseum.readExhibitsFromFile(file);

    runMainMenu(myMuseum);
}

//1.regexp - компактность + эффективность 
//2.constexpr - компилятор проверяет корректность выражений еще до выполнения программы
//              + значения уже известны компилятору, что ускоряет программы

