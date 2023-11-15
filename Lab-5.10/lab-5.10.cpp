#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

// Написать абстрактный класс «Работник фирмы».
// На его основе реализовать классы «Менеджер», «Администратор», «Программист» и т.п.
// Написать программу, демонстрирующую работу с этими классами

enum class WorkShift {
    Day,            // Дневная смена
    Evening,        // Вечерняя смена
    Night,          // Ночная смена
    Rotating,       // Ротационная смена
    TwelveHour,     // 12-часовая смена
    Overtime,       // Сверхурочная смена
    Weekend         // Выходная смена
};


class Employee {
public:
    virtual void displayDuties() const = 0;
    virtual int getCount() const = 0;
    friend string getWorkShiftString(const Employee&);

    void displayPersonalInfo() {
        cout << "Имя: " << name << "\n"
            << "Возраст: " << age << "\n"
            << "Адрес: " << address << "\n";
    }

    void displayContactInfo() {
        cout << "Номер телефона: " << phoneNumber << "\n"
            << "Email: " << email << "\n";
    }

    void displayProfessionalInfo() {
        cout << "Смена: " << getWorkShiftString(*this) << "\n"
            << "Зарплата: " << age << "\n"
            << "Номер отдела: " << address << "\n";
    }

    Employee(string& name, unsigned& age, string& address, string& phoneNumber, string& email, WorkShift& shift, int& departmentNumber, double& salary)
        : name{ name }, age{ age }, address{ address }, phoneNumber{ phoneNumber }, email{ email }, shift{ shift }, departmentNumber{ departmentNumber }, salary{ salary } {
        id = employeeCount++;
    }

protected:
    string name;
    unsigned age;
    string address;
    string phoneNumber;
    string email;
    WorkShift shift;
    int departmentNumber;
    double salary;
    int id;

private:
    static inline int employeeCount{};
};


string getWorkShiftString(const Employee& employee) {
    WorkShift shift = employee.shift;
    switch (shift) {
        case WorkShift::Day:
            return "Day";
            break;
        case WorkShift::Evening:
            return "Evening";
            break;
        case WorkShift::Night:
            return "Night";
            break;
        case WorkShift::Overtime:
            return "Overtime";
            break;
        case WorkShift::Rotating:
            return "Rotating";
            break;
        case WorkShift::TwelveHour:
            return "TwelveHour";
            break;
        case WorkShift::Weekend:
            return "Weekend";
            break;
        default:
            return "None";
    }
}


class Manager : public Employee {
private:
    static inline int managerCount{};

public:
    Manager(string name, unsigned age, string address, string phoneNumber, string email, WorkShift shift, int departmentNumber, double salary)
        : Employee(name, age, address, phoneNumber, email, shift, departmentNumber, salary) {
        managerCount += 1;
    }

    void displayDuties() const override {
        cout << "Обязанности менеджера: " << "\n";
        for (size_t i = 0; i < managerDuties.size(); i++) {
            cout << managerDuties[i] << "\n";
        }
    }

    int getCount() const override {
        return managerCount;
    }

protected:
    vector<string> managerDuties = {
        " -Планирование и организация работы отдела или проекта.",
        " -Координация работы команды, распределение задач и контроль их выполнения.",
        " -Взаимодействие с клиентами и партнёрами, представление интересов компании.",
        " -Анализ рынка, разработка стратегий развития и их реализация.",
        " -Отчётность и анализ эффективности работы отдела."
    };
};


class Administrator : public Employee {
private:
    static inline int administratorCount{};

public:
    Administrator(string name, unsigned age, string address, string phoneNumber, string email, WorkShift shift, int departmentNumber, double salary)
        : Employee(name, age, address, phoneNumber, email, shift, departmentNumber, salary) {
        administratorCount += 1;
    }

    void displayDuties() const override {
        cout << "Обязанности администратора: " << "\n";
        for (size_t i = 0; i < administratorDuties.size(); i++) {
            cout << administratorDuties[i] << "\n";
        }
    }

    int getCount() const override {
        return administratorCount;
    }

protected:
    vector<string> administratorDuties = {
        " -Обеспечение бесперебойной работы офиса или предприятия.",
        " -Управление административным персоналом, контроль за порядком и соблюдением правил.",
        " -Организация встреч, мероприятий, деловых визитов.",
        " -Ведение документооборота, контроль за сроками исполнения документации.",
        " -Обработка входящей и исходящей корреспонденции, приём телефонных звонков."
    };
};


class Programmer : public Employee {
private:
    static inline int programmerCount{};

public:
    Programmer(string name, unsigned age, string address, string phoneNumber, string email, WorkShift shift, int departmentNumber, double salary)
        : Employee(name, age, address, phoneNumber, email, shift, departmentNumber, salary) {
        programmerCount += 1;
    }

    void displayDuties() const override {
        cout << "Обязанности администратора: " << "\n";
        for (size_t i = 0; i < programmerDuties.size(); i++) {
            cout << programmerDuties[i] << "\n";
        }
    }

    int getCount() const override {
        return programmerCount;
    }

protected:
    vector<string> programmerDuties = {
        " -Разработка и поддержка программного обеспечения.",
        " -Анализ требований к программным продуктам, проектирование архитектуры.",
        " -Кодирование, тестирование и отладка программного обеспечения.",
        " -Составление технической документации и руководств пользователя.",
        " -Сотрудничество с другими разработчиками и отделами для улучшения качества продукта."
    };
};


class Company {
public:
    vector<Manager> managers;
    vector<Administrator> administrators;
    vector<Programmer> programmers;
};



void waitToPressEnter() {
    cout << "(Нажмите Enter, чтобы вернуться)";
    while (true) {
        char input = _getch();
        if (input == 13) {
            break;
        }
    }
}

void drawMenu(int& selected, string& header, vector<string> options) {
    system("cls");

    cout << header << "\n";
    for (int i = 0; i < options.size(); i++) {

        if (i == selected) {
            cout << " -> ";
        } else {
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
                return selected + 1;
                break;
            default: // Не перерисовывать меню для любой другой клавиши
                redrawMenu = false;
                break;
        }
    }
}

void displayWorkersNumber(Company& myCompany, int poistion) {
    switch (poistion) {
        case 1:
            cout << myCompany.managers[0].getCount();
            break;
        case 2:
            cout << myCompany.administrators[0].getCount();
            break;
        case 3:
            cout << myCompany.programmers[0].getCount();
            break;
        default:
            break;
    }
}

void dutiesOfPosition(Company& myCompany, int poistion) {
    switch (poistion) {
        case 1:
            myCompany.managers[0].displayDuties();
            break;
        case 2:
            myCompany.administrators[0].displayDuties();
            break;
        case 3:
            myCompany.programmers[0].displayDuties();
            break;
        default:
            break;
    }
}

void displayEmloyeesInfo(Company& myCompany, int poistion) {
    switch (poistion) {
        case 1:
            for (size_t i = 0; i < myCompany.managers.size(); i++) {
                myCompany.managers[i].displayPersonalInfo();
                myCompany.managers[i].displayContactInfo();
                myCompany.managers[i].displayProfessionalInfo();
                cout << "\n";
            }
            break;
        case 2:
            for (size_t i = 0; i < myCompany.administrators.size(); i++) {
                myCompany.administrators[i].displayPersonalInfo();
                myCompany.administrators[i].displayContactInfo();
                myCompany.administrators[i].displayProfessionalInfo();
                cout << "\n";
            }
            break;
        case 3:
            for (size_t i = 0; i < myCompany.programmers.size(); i++) {
                myCompany.programmers[i].displayPersonalInfo();
                myCompany.programmers[i].displayContactInfo();
                myCompany.programmers[i].displayProfessionalInfo();
                cout << "\n";
            }
            break;
        default:
            break;
    }
}

void selectAction(Company& myCompany, int poistion) {
    bool exitLoop = false;
    while (!exitLoop) {
        int selectedAction = getSelectedOption("Выберите действие: ", { "Вывести число работников должности", "Вывести обязанности должности", "Вывести информацию о работниках должности", "<-" });
        switch (selectedAction) {
            case 1:
                system("cls");
                displayWorkersNumber(myCompany, poistion);
                cout << "\n\n";
                waitToPressEnter();
                break;
            case 2:
                system("cls");
                dutiesOfPosition(myCompany, poistion);
                cout << "\n";
                waitToPressEnter();
                break;
            case 3:
                system("cls");
                displayEmloyeesInfo(myCompany, poistion);
                cout << "\n";
                waitToPressEnter();
                break;
            default:
                exitLoop = true;
                break;
        }
    }
}

void selectEmployeePosition(Company& myCompany) {
    bool exitLoop = false;
    while (!exitLoop) {
        int selectedAction = getSelectedOption("Выберите должность работника компании: ", { "Менеджер", "Администратор", "Программист", "Выйти" });
        switch (selectedAction) {
            case 1:
                selectAction(myCompany, selectedAction);
                break;
            case 2:
                selectAction(myCompany, selectedAction);
                break;
            case 3:
                selectAction(myCompany, selectedAction);
                break;
            default:
                exitLoop = true;
                break;
        }
    }
}



int main() {
    Company myCompany;
    myCompany.managers.push_back({ "Петров Вячеслав", 23, "ул. Косиора, 18", "+7 932 195 477", "pacido57@gmail.com", WorkShift::Overtime, 6, 70000 });
    myCompany.managers.push_back({ "Павлов Максим", 20, "ул. Славы, 64", "+7 993 969 454", "jebogo80@aol.com", WorkShift::Day, 1, 71000.500 });
    myCompany.managers.push_back({ "Рудаков Леонид", 22, "въезд Сталина, 96", "+7 911 256 159", "fayifle56@hotmail.com", WorkShift::Rotating, 8, 65000.200 });

    myCompany.administrators.push_back({ "Денисов Роман", 30, "наб. Ломоносова, 52", "+7 953 852 857", "fikxe64@aol.com", WorkShift::TwelveHour, 1, 102000 });
    myCompany.administrators.push_back({ "Данилов Марк", 19, "шоссе Славы, 47", "+7 985 458 250", "swezito73@mail.com", WorkShift::Day, 5, 59000 });
    myCompany.administrators.push_back({ "Чернов Егор", 25, "спуск Космонавтов, 83", "+7 900 097 490", "wodole9@hotmail.com", WorkShift::Weekend, 2, 115500 });


    myCompany.programmers.push_back({ "Григорьев Артемий", 24, "пр. Бухарестская, 71", "+7 954 821 257", "wivna89@hotmail.com", WorkShift::Day, 7, 156000 });
    myCompany.programmers.push_back({ "Афанасьев Михаил", 25, "бульвар 1905 года, 89", "+7 956 054 501", "dogasu4i60@outlook.com", WorkShift::Evening, 5, 190000 });
    myCompany.programmers.push_back({ "Филимонов Мирон", 31, "ул. Ленина, 48", "+7 908 650 020", "bebado23@gmail.com", WorkShift::Night, 3, 89800 });


    selectEmployeePosition(myCompany);
}


