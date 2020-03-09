#include <cstdio>
#include <iostream>

using namespace std;

template <typename T>
struct node {
public:
	T value;
	node<T>* next = nullptr;
};

template <typename T>
struct node_d {
public:
	T value;
	node_d<T>* next = nullptr;
	node_d<T>* prev = nullptr;
};

template <typename T>
class singleLinked {
private:
	node<T>* head = nullptr;
	node<T>* tail = nullptr;

public:
	singleLinked() : head(nullptr), tail(nullptr) {
	}
	~singleLinked() {
		deleteList();
	}

	void add(T value) {
		node<T>* ptr = new node<T>;
		ptr->next = nullptr;
		ptr->value = value;

		if (head == nullptr) {
			head = ptr;
			tail = ptr;
		}
		else {
			tail->next = ptr;
			tail = tail->next;
		}
	}

	void remove(T value) {
		node<T>* ptr = head;
		node<T>* temp = ptr;

		while (ptr != nullptr) {
			if (ptr->value == value) {
				break;
			}
			temp = ptr;
			ptr = ptr->next;
		}
		if (ptr == nullptr) {
			cout << "해당 하는 값이 없음" << endl;
		}
		else {
			if (ptr == head) {
				if (head->next != nullptr) {
					head = head->next;
					cout << "삭제되는 값 : " << ptr->value << endl;
					delete ptr;
				}
				else {
					head = nullptr;
					tail = nullptr;
					cout << "삭제되는 값 : " << ptr->value << endl;
					delete ptr;
				}
			}
			else {
				if (ptr == tail) {
					tail = temp;
				}
				temp->next = ptr->next;
				ptr->next = nullptr;
				cout << "삭제되는 값 : " << ptr->value << endl;
				delete ptr;
			}
		}
	}

	void deleteList() {
		node<T>* ptr = head;
		while (ptr != nullptr) {
			head = ptr->next;
			delete ptr;
			ptr = head;
		}
		delete head;
		delete tail;
		cout << "리스트가 삭제됨" << endl;
	}

	void show() const{
		node<T>* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->value << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};

template <typename T>
class circleLinked {
private:
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
	int size;
public:
	circleLinked() : head(nullptr), tail(nullptr), size(0){

	}
	~circleLinked() {

	}

	void add(T value) {
		node<T>* ptr = new node<T>;
		ptr->next = head;
		ptr->value = value;
		
		if (head == nullptr) {
			head = ptr;
			tail = ptr;
		}
		else {
			tail->next = ptr; // 바뀌기 전의 tail 의 다음이 ptr 이고
			tail = tail->next; // 바뀌기 전의 tail 을 다음 tail 역할인 ptr 로
		}
		size++;
	}

	void remove(T value) {
		node<T>* ptr = head;
		node<T>* temp = ptr;
		int count = 0;

		while (count < size) {
			if (ptr->value == value) {
				break;
			}
			temp = ptr;
			ptr = ptr->next;
			count++;
		}
		if (count >= size) {
			cout << "해당 하는 값이 없음" << endl;
		}
		else {
			if (ptr == head) {
				if (head->next != nullptr) {
					head = head->next;
					tail->next = head;
					cout << "삭제되는 값 : " << ptr->value << endl;
					delete ptr;
				}
				else {
					head = nullptr;
					tail = nullptr;
					cout << "삭제되는 값 : " << ptr->value << endl;
					delete ptr;
				}
			}
			else {
				if (ptr == tail) {
					tail = temp;
				}
				temp->next = ptr->next;
				ptr->next = nullptr;
				cout << "삭제되는 값 : " << ptr->value << endl;
				delete ptr;
			}
			size--;
		}
	}

	void deleteList() {
		node<T>* ptr = head;
		while (size != 0) {
			head = ptr->next;
			delete ptr;
			ptr = head;
			size--;
		}
		cout << "리스트가 삭제됨" << endl;
	}

	void show(int num) const {
		int count = 0;
		node<T>* ptr = head;
		while (count < num * size) {
			cout << ptr->value << " ";
			ptr = ptr->next;
			count++;
			if (count % size == 0) {
				cout << endl;
			}
		}
		cout << endl;
	}
};

template <typename T>
class doubleLinked {
private:
	node_d<T>* head = nullptr;
	node_d<T>* tail = nullptr;
	int size = 0;

public:
	doubleLinked() : head(nullptr), tail(nullptr) {
	}
	~doubleLinked() {
		deleteList();
	}

	void add(T value) {
		node_d<T>* ptr = new node_d<T>;
		ptr->next = nullptr;
		ptr->prev = nullptr;
		ptr->value = value;

		if (head == nullptr) {
			head = ptr;
			tail = ptr;
		}
		else {
			ptr->prev = tail;
			tail->next = ptr;
			tail = tail->next;
		}
		size++;
	}

	void remove(T value) {
		node_d<T>* ptr = head;
		node_d<T>* temp = ptr;

		while (ptr != nullptr) {
			if (ptr->value == value) {
				break;
			}
			temp = ptr;
			ptr = ptr->next;
		}
		if (ptr == nullptr) {
			cout << "해당 하는 값이 없음" << endl;
		}
		else {
			if (ptr == head) {
				if (head->next != nullptr) {
					head = head->next;
					head->prev = nullptr;
					cout << "삭제되는 값 : " << ptr->value << endl;
					delete ptr;
				}
				else {
					head = nullptr;
					tail = nullptr;
					cout << "삭제되는 값 : " << ptr->value << endl;
					delete ptr;
				}
			}
			else {
				if (ptr == tail) {
					tail = temp;
					temp->next = ptr->next;
				}
				else {
					temp->next = ptr->next;
					(ptr->next)->prev = temp;
				}
				cout << "삭제되는 값 : " << ptr->value << endl;
				delete ptr;
			}
			size--;
		}
	}

	void deleteList() {
		node_d<T>* ptr = head;
		while (ptr != nullptr) {
			head = ptr->next;
			delete ptr;
			ptr = head;
		}
		delete head;
		cout << "리스트가 삭제됨" << endl;
	}

	void show() const {
		node_d<T>* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->value << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}

	void get(int index) {
		node_d<T>* temp;

		if (index > size) {
			cout << "index over size" << endl;
		}
		else {
			if (index < size / 2) {
				temp = head;
				for (int i = 0; i < index; i++) {
					temp = temp->next;
				}
				cout << temp->value << endl;
			}
			else {
				temp = tail;
				for (int i = size - 1; i > index; i--) {
					temp = temp->prev;
				}
				cout << temp->value << endl;
			}
		}
	}
};

int main() {
	doubleLinked<int> list = doubleLinked<int>();
	for (int i = 10; i > 0; i--) {
		list.add(i);
	}
	list.show();
	list.get(0);
	list.get(9);
	list.deleteList();
	return 0;
}