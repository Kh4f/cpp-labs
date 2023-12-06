#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <sstream>
using namespace std;

/*
Тема 7: шаблоны функций и классов.
#4. Для лабораторной #6 определить шаблоны соответствующих классов.
Написать тестовую программу, демонстрирующую работу шаблонных классов с различными типами данных.
*/


template <typename T> class SinglyLinkedList {
public:
	class Node {
	private:
		T value;
		Node* next;

	public:
		Node(T value, Node* next) : value(value), next(next) {}
		Node(T value) : Node(value, nullptr) {}

		T getValue() {
			return value;
		}
		void setValue(T value) {
			this->value = value;
		}
		Node* getNext() {
			return next;
		}
		void setNext(Node* next) {
			this->next = next;
		}
	};

	SinglyLinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	~SinglyLinkedList() {
		removeAll();
	}

	SinglyLinkedList(const SinglyLinkedList& sll) {
		Node* currNode = sll.head;

		while (currNode != nullptr) {
			this->addLast(currNode->getValue());
			currNode = currNode->getNext();
		}
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void checkEmpty() {
		if (isEmpty()) {
			throw SinglyLinkedListException("List is empty");
		}
	}

	void checkIndex(int index) {
		if (index < 0 || index >= size) {
			throw out_of_range("Incorrect index");
		}
	}

	Node* getNode(int index) {
		checkEmpty();
		checkIndex(index);

		int counter = 0;
		Node* current = head;
		while (counter++ < index) {
			current = current->getNext();
		}

		return current;
	}

	void addFirst(T value) {
		head = new Node(value, head);
		if (isEmpty()) {
			tail = head;
		}
		++size;
	}

	void addLast(T value) {
		if (isEmpty()) {
			addFirst(value);
			return;
		}
		Node* newNode = new Node(value);
		tail->setNext(newNode);
		tail = newNode;
		++size;
	}

	void removeFirst() {
		checkEmpty();
		Node* temp = head;
		head = head->getNext();
		delete temp;
		--size;
	}

	void removeLast() {
		checkEmpty();
		if (size == 1) {
			removeFirst();
			return;
		}

		tail = getNode(size - 2);
		Node* temp = tail->getNext();
		tail->setNext(nullptr);
		delete temp;
		--size;
	}

	void removeAll() {
		while (!isEmpty()) {
			removeLast();
		}
	}

	void insert(int index, T value) {
		if (index == 0) {
			addFirst(value);
			return;
		}
		else if (index == size) {
			addLast(value);
			return;
		}
		checkIndex(index);
		Node* newNode = new Node(value);
		Node* prev = getNode(index - 1);
		Node* next = prev->getNext();

		prev->setNext(newNode);
		newNode->setNext(next);

		++size;
	}

	void remove(int index) {
		checkEmpty();

		if (index == 0) {
			removeFirst();
			return;
		}
		else if (index == (size - 1)) {
			removeLast();
			return;
		}
		checkIndex(index);
		Node* prev = getNode(index - 1);
		Node* curr = prev->getNext();
		Node* next = curr->getNext();
		prev->setNext(next);
		delete curr;
		--size;
	}

	T getValueAt(int index) {
		checkIndex(index);
		return getNode(index)->getValue();
	}

	void print() {
		if (isEmpty()) {
			cout << "[]";
			return;
		}
		Node* currNode = head;

		cout << "[";
		int index = 0;
		while (currNode != nullptr) {
			cout << currNode->getValue();
			if (index < (size - 1)) {
				cout << ", ";
			}
			currNode = currNode->getNext();
			index += 1;
		}
		cout << "]";
	}

	string toString() {
		if (isEmpty()) {
			return "[]";
		}
		Node* currNode = head;
		stringstream ss;

		ss << "[";
		int index = 0;
		while (currNode != nullptr) {
			ss << currNode->getValue();
			if (index < (size - 1)) {
				ss << ", ";
			}
			currNode = currNode->getNext();
			index += 1;
		}
		ss << "]";
		string stringValue = ss.str();
		return stringValue;
	}

	class SinglyLinkedListIterator {
	private:
		Node* curr;

	public:
		SinglyLinkedListIterator(Node* start) : curr(start) {}

		bool hasNext() {
			return curr != nullptr;
		}

		T get() {
			T value = curr->getValue();
			return value;
		}

		void next() {
			curr = curr->getNext();
		}
	};

	SinglyLinkedListIterator iterator() {
		return SinglyLinkedListIterator(head);
	}

	T operator [](int index) {
		return getValueAt(index);
	}

	SinglyLinkedList<T> operator+(SinglyLinkedList<T>& other) {
		SinglyLinkedList<T> result = *this;

		typename SinglyLinkedList<T>::SinglyLinkedListIterator it = other.iterator();

		while (it.hasNext()) {
			result.addLast(it.get());
			it.next();
		}

		return result;
	}

	SinglyLinkedList<T> operator-(SinglyLinkedList<T>& second) {
		SinglyLinkedList<T> result = *this;
		typename SinglyLinkedList<T>::SinglyLinkedListIterator it1 = result.iterator();

		int index = 0;
		while (it1.hasNext()) {
			typename SinglyLinkedList<T>::SinglyLinkedListIterator it2 = second.iterator();
			bool elementFound = false;

			while (it2.hasNext()) {
				if (it1.get() == it2.get()) {
					elementFound = true;
					break;
				}
				it2.next();
			}
			it1.next();
			if (elementFound) {
				result.remove(index);
			}
			else {
				index += 1;
			}
		}

		return result;
	}

	template <typename T> friend bool isSubset(SinglyLinkedList<T>& list1, SinglyLinkedList<T>& list2);

private:
	class SinglyLinkedListException : public exception {
	public:
		explicit SinglyLinkedListException(const string& message) : msg(message) {}

		const char* what() const noexcept override {
			return msg.c_str();   // получаем из std::string строку const char*
		}

	private:
		string msg;
	};

	Node* head;
	Node* tail;
	int size;
};

template <typename T> bool isSubset(SinglyLinkedList<T>& list1, SinglyLinkedList<T>& list2) {
	typename SinglyLinkedList<T>::Node* curr1 = list1.head;

	while (curr1 != nullptr) {
		typename SinglyLinkedList<T>::Node* curr2 = list2.head;
		bool found = false;

		while (curr2 != nullptr) {
			if (curr1->getValue() == curr2->getValue()) {
				found = true;
				break;
			}
			curr2 = curr2->getNext();
		}

		if (!found) {
			return false;
		}

		curr1 = curr1->getNext();
	}

	return true;
}

//int main() {
//	SinglyLinkedList<int> list1;
//	list1.addFirst(1);
//	list1.addFirst(2);
//	list1.addFirst(3);
//	cout << "Добавление в начало: " << list1.toString() << "\n";
//
//	list1.addLast(6);
//	list1.addLast(5);
//	list1.addLast(4);
//	cout << "Добавление в конец: " << list1.toString() << "\n";
//
//	SinglyLinkedList<int> list2;
//	list2.addLast(2);
//	list2.addLast(15);
//	list2.addLast(6);
//
//	list1.removeFirst();
//	list1.removeLast();
//	cout << "Удаление первого и последнего элемента: " << list1.toString() << "\n";
//
//	list1.remove(1);
//	cout << "Удаление по индексу '1': " << list1.toString() << "\n";
//
//	list1.insert(1, 15);
//	cout << "Вставка значения '15' по индексу '1': " << list1.toString() << "\n";
//
//	cout << "Итератор по элементам list1: ";
//	SinglyLinkedList<int>::SinglyLinkedListIterator it = list1.iterator();
//	while (it.hasNext()) {
//		cout << it.get() << " ";
//		it.next();
//	}
//	cout << "\n\n";
//
//	cout << "Получение элемента по оператору [0]: " << list1[0] << "\n\n";
//
//	SinglyLinkedList<int> list3 = list1 + list2;
//	cout << "List1: " << list1.toString() << "\n";
//	cout << "List2: " << list2.toString() << "\n";
//	cout << "List3 = List1 + List2: " << list3.toString() << "\n\n";
//
//	SinglyLinkedList<int> list4 = list1 - list2;
//	cout << "List1: " << list1.toString() << "\n";
//	cout << "List2: " << list2.toString() << "\n";
//	cout << "List4 = List1 - List2: " << list4.toString() << "\n\n";
//
//	bool isSubsetResult = isSubset(list2, list1);
//	if (isSubsetResult) {
//		cout << "List2 is a subset of List1\n";
//	} else {
//		cout << "List2 is NOT a subset of List1\n";
//	}
//}

void drawMenu(int& selected, string& header, vector<string> options, string footer = "") {
	system("cls");

	cout << header << "\n";
	for (int i = 0; i < options.size(); i++) {
		if (i == selected) {
			cout << " -> ";
		}
		else {
			cout << "    ";
		}
		/*cout << options[i] << "\n";*/
		cout << "• " << options[i] << "\n";
		/*cout << i + 1 << "." << options[i] << "\n";*/
	}
	if (footer != "") {
		cout << footer << "\n";
	}
}

int getSelectedOption(string header, vector<string> options, string footer = "") {
	int selected = 0;
	bool redrawMenu = true;

	while (true) {
		if (redrawMenu) {
			drawMenu(selected, header, options, footer);
		}

		char input = _getch(); // Ожидание ввода

		switch (input) {
		case 72: // Arrow UP
			if (selected > 0) {
				selected--;
				redrawMenu = true;
			}
			break;
		case 80: // Arrow DOWN
			if (selected < options.size() - 1) {
				selected++;
				redrawMenu = true;
			}
			break;
		case 13: // Enter
			return selected + 1;
			break;
		case 27: // Escape
			exit(0);
			break;
		default: // Не перерисовывать меню
			redrawMenu = false;
			break;
		}
	}
}

template <typename T> void fun(T value) {
	T var = value;
	cout << var;
	SinglyLinkedList<T> list;
}

string getTypeName(int& typeNumber) {
	string typeName;

	switch (typeNumber) {
	case 1:
		typeName = "int";
		break;
	case 2:
		typeName = "double";
		break;
	case 3:
		typeName = "string";
		break;
	}
	return typeName;
}

int getIntegerValue(int& typeNumber) {
	string inputValue;
	bool valueIsCorrect = false;

	while (!valueIsCorrect) {
		cout << "\nВведите значение нового элемента: ";
		getline(cin >> ws, inputValue);

		valueIsCorrect = true;
		for (int i = 0; i < inputValue.length(); i++) {
			char& c = inputValue[i];
			if (c == '-' && i == 0) {
				continue;
			}
			if (!isdigit(c)) {
				cout << "Ошибка: элемент должен быть типа <" << getTypeName(typeNumber) << ">\n";
				valueIsCorrect = false;
				break;
			}
		}
	}

	return stoi(inputValue);
}

double getDoubleValue(int& typeNumber) {
	string input;
	/*double result = 0.0;*/
	bool valueIsValid = false;

	while (!valueIsValid) {
		valueIsValid = true;

		cout << "\nВведите значение нового элемента: ";
		getline(cin >> ws, input);

		if (input == "-") {
			valueIsValid = false;
			continue;
		}
		if (input[0] != '-' && !isdigit(input[0])) {
			valueIsValid = false;
			continue;
		}

		int dotCount = 0;
		for (int i = 1; i < input.length(); i++) {
			if (input[i] == '.') {
				dotCount++;
				if (dotCount > 1) {
					valueIsValid = false;
					break;
				}
				continue;
			}
			else if (!isdigit(input[i])) {
				valueIsValid = false;
				break;
			}
		}

		if (!valueIsValid) {
			cout << "Ошибка: элемент должен быть типа <" << getTypeName(typeNumber) << ">\n";
		}
	}
	return stod(input);
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

template <typename T> void addFirstOption(int& typeNumber, SinglyLinkedList<T>& list);

template <typename T> void selectAction(int typeNumber, SinglyLinkedList<T>& list, string footer = "") {
	bool exitLoop = false;
	while (!exitLoop) {
		int selectedAction = getSelectedOption("Ваш текущий список: " + list.toString() + "\n\nВыберите действие: ",
			{ "добавить в начало", "добавить в конец", "очистить", "<- назад" }, footer);
		switch (selectedAction) {
		case 1: {
			addFirstOption(typeNumber, list);
			break;
		}
		case 2: {
			/*addLastOption(typeName);*/
			break;
		}
		case 3: {
			/*clearListOption();*/
			break;
		}
		default: {
			exitLoop = true;
			break;
		}
		}
	}
}

template <typename T> void addFirstOption(int& typeNumber, SinglyLinkedList<T>& list) {
	T value{};
	switch (typeNumber) {
	case 1: {
		value = getIntegerValue(typeNumber);
		list.addFirst(value);
		break;
	}
	case 2: {
		value = getDoubleValue(typeNumber);
		list.addFirst(value);
		break;
	}
	case 3: {
		string str;
		getline(cin, str);
		list.addFirst(str);
		break;
	}
	}
}

void selectListDataType() {
	bool exitLoop = false;
	while (!exitLoop) {
		int selectedType = getSelectedOption("Выберите тип данных для списка: ", { "int", "double", "string" }, "\n(Нажмите ESCAPE, чтобы выйти)");
		switch (selectedType) {
		case 1: {
			SinglyLinkedList<int> list1;
			selectAction<int>(1, list1);
			break;
		}
		case 2: {
			SinglyLinkedList<double> list2;
			selectAction<double>(2, list2);
			break;
		}
		case 3: {
			SinglyLinkedList<string> list3;
			selectAction<string>(3, list3);
			break;
		}
		default: {
			exitLoop = true;
			break;
		}
		}
	}
}

int main() {
	/*SinglyLinkedList<string> list1;
	list1.addLast("string1");
	list1.addLast("string2");
	list1.addLast("string3");
	list1.addLast("string4");
	list1.addLast("string5");

	SinglyLinkedList<int> list2;
	list2.addLast(1);
	list2.addLast(2);
	list2.addLast(3);
	list2.addLast(4);
	list2.addLast(5);

	SinglyLinkedList<bool> list3;
	list3.addLast(true);
	list3.addLast(false);
	list3.addLast(true);
	list3.addLast(true);
	list3.addLast(false);*/

	/*list.print();*/
	/*fun<int>("f");*/
	selectListDataType();
	/*cout << list3.toString();*/
	/*char input = _getch();
	cout << static_cast<unsigned int>(input);*/
}
