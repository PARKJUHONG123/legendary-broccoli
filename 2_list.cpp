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

	T remove(T value) {
		node<T>* ptr = head;
		node<T>* temp = ptr;
		T result = NULL;

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
					result = ptr->value;
					delete ptr;
				}
				else {
					head = nullptr;
					tail = nullptr;
					result = ptr->value;
					delete ptr;
				}
			}
			else {
				if (ptr == tail) {
					tail = temp;
				}
				temp->next = ptr->next;
				ptr->next = nullptr;
				result = ptr->value;
				delete ptr;
			}
		}
		return result;
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
		deleteList();
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

	T remove(T value) {
		node<T>* ptr = head;
		node<T>* temp = ptr;
		int count = 0;
		T result = NULL;

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
					result = ptr->value;
					delete ptr;
				}
				else {
					head = nullptr;
					tail = nullptr;
					result = ptr->value;
					delete ptr;
				}
			}
			else {
				if (ptr == tail) {
					tail = temp;
				}
				temp->next = ptr->next;
				ptr->next = nullptr;
				result = ptr->value;
				delete ptr;
			}
			size--;
		}
		return result;
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

	T remove(T value) {
		node_d<T>* ptr = head;
		node_d<T>* temp = ptr;
		T result = NULL;

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
					result = ptr->value;
					delete ptr;
				}
				else {
					head = nullptr;
					tail = nullptr;
					result = ptr->value;
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
				result = ptr->value;
				delete ptr;
			}
			size--;
		}
		return result;
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
	//singleLinked<int> list = singleLinked<int>();
	//circleLinked<int> list = circleLinked<int>();
	doubleLinked<int> list = doubleLinked<int>();

	int choice = -1, input = -1;
	bool check_out = false;

	while (1) {
		cout << "1.삽입 2.삭제 3.출력 4.종료 5.검색 (double 한정)" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cin >> input;
			list.add(input);
			break;

		case 2:
			cout << "삭제할 값을 입력하시오" << endl;
			cin >> input;
			cout << list.remove(input) << endl;
			break;

		case 3:
			list.show();
			break;


		case 4:
			check_out = true;
			break;

		/*
		case 5:
			cout << "검색할 인덱스를 입력하시오" << endl;
			cin >> input;
			list.get(input);
			break;
		*/
		}
		if (check_out) break;
	}
	return 0;
}