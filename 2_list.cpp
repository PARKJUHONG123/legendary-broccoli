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
		cout << "리스트가 삭제됨" << endl;
	}

	void show() {
		node<T>* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->value << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};

template <typename T>
class doubleLinked : public singleLinked<T> {

};

class circleLinked {

};

int main() {
	singleLinked<int> list = singleLinked<int>();
	for (int i = 10; i > 0; i--) {
		list.add(i);
		list.remove(i - 1);
		list.remove(i - 2);
		list.remove(i);
		list.remove(i);
	}
	list.show();
	return 0;
}