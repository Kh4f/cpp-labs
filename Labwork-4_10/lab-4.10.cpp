#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;


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

int getAnInteger(string header) {
    string inputValue;
    out:
    cout << header;
    getline(cin >> ws, inputValue);
    for (int i = 0; i < inputValue.length(); i++) {
        char& c = inputValue[i];
        if (c == '-' && i == 0) {
            continue;
        }
        if (!isdigit(c)) {
            cout << "Требуется целое число. Попробуйте ещё раз.\n";
            goto out;
        }
    }
    return stoi(inputValue);
}

int getPositiveInteger(string header) {
    string inputValue;
    out:
    cout << header;
    getline(cin >> ws, inputValue);
    for (char& c : inputValue) {
        if (!isdigit(c)) {
            cout << "Требуется целое положительное число. Попробуйте ещё раз.\n";
            goto out;
        }
    }
    return stoi(inputValue);
}

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
    
    int year = getAnInteger("Год создания: ");

    cout << "Описание: ";
    getline(cin >> ws, description);
    replaceDelimToSpace(description);
    
    int hallNumber = getPositiveInteger("Номер зала: ");

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
            int number = getPositiveInteger("\nВведите номер зала: ");
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
            int minYear = getAnInteger("\nВведите первый год диапазона: ");
            int maxYear = getAnInteger("Введите второй год диапазона: ");
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

int main() {
    MyMuseum myMuseum;

    ifstream file("exhibits.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл 'exhibits.txt'. \n";
        return 1;
    }
    myMuseum.readExhibitsFromFile(file);

    runMainMenu(myMuseum);
}

