#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Написать класс «Односвязный список».
Реализовать конструкторы, деструктор, методы добавления и удаления элементов.
Реализовать перегрузку операторов доступа по индексу [], сложение (+) и разность (-) элементов двух списков.
Предложить и реализовать дружественную функцию для данного класса.
*/


template <typename T> class SinglyLinkedList {
private:
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



public:
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
		} else if (index == size) {
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
		} else if (index == (size - 1)) {
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

	string toString() {
		if (isEmpty()) {
			return "[]";
		}
		string str = "[";
		Node* currNode = head;

		int index = 0;
		while (currNode != nullptr) {
			str += to_string(currNode->getValue());
			if (index < (size - 1)) {
				str += ", ";
			}
			currNode = currNode->getNext();
			index += 1;
		}
		str += "]";

		return str;
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

	template <typename T> friend SinglyLinkedList<T> operator-(SinglyLinkedList<T>&, SinglyLinkedList<T>&);
};

template <typename T> SinglyLinkedList<T> operator-(SinglyLinkedList<T>& first, SinglyLinkedList<T>& second) {
	SinglyLinkedList<T> result = first;
	typename SinglyLinkedList<T>::SinglyLinkedListIterator it1 = first.iterator();

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
		} else {
			index += 1;
		}
	}

	return result;
}


int main() {
	SinglyLinkedList<int> list1;
	list1.addFirst(1);
	list1.addFirst(2);
	list1.addFirst(3);
	cout << "Добавление в начало: " << list1.toString() << "\n";

	list1.addLast(6);
	list1.addLast(5);
	list1.addLast(4);
	cout << "Добавление в конец: " << list1.toString() << "\n";

	SinglyLinkedList<int> list2;
	list2.addLast(2);
	list2.addLast(4);
	list2.addLast(6);

	list1.removeFirst();
	list1.removeLast();
	cout << "Удаление первого и последнего элемента: " << list1.toString() << "\n";

	list1.remove(1);
	cout << "Удаление по индексу '1': " << list1.toString() << "\n";

	list1.insert(1, 15);
	cout << "Вставка значения '15' по индексу '1': " << list1.toString() << "\n";

	cout << "Итератор по элементам list1: ";
	SinglyLinkedList<int>::SinglyLinkedListIterator it = list1.iterator();
	while (it.hasNext()) {
		cout << it.get() << " ";
		it.next();
	}
	cout << "\n\n";

	cout << "Получение элемента по оператору [0]: " << list1[0] << "\n\n";

	SinglyLinkedList<int> list3 = list1 + list2;
	cout << "List1: " << list1.toString() << "\n";
	cout << "List2: " << list2.toString() << "\n";
	cout << "List3 = List1 + List2: " << list3.toString() << "\n\n";

	SinglyLinkedList<int> list4 = list1 - list2;
	cout << "List1: " << list1.toString() << "\n";
	cout << "List2: " << list2.toString() << "\n";
	cout << "List4 = List1 - List2: " << list4.toString() << "\n\n";
}


