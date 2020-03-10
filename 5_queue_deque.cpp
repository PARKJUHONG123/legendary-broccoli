#include <cstdio>
#include <iostream>

using namespace std;

template <typename T>
struct node {
	node<T>* prev = nullptr;
	node<T>* next;
	T value;
};

class nullptrError {
public:
	void ExceptionError() {
		cout << "dequeue nullptr error" << endl;
	}
};

template <typename T>
class queue {
private:
	node<T>* head = nullptr;
	node<T>* tail = nullptr;

public:
	queue() : head(nullptr), tail(nullptr) {
		
	}
	~queue() {
		deleteQueue();
	}

	void enqueue(T value) {
		node<T>* temp = new node<T>;
		temp->next = nullptr;
		temp->prev = nullptr;
		temp->value = value;

		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}

	T dequeue() {
		if (head == nullptr) {
			throw nullptrError();
		}
		else {
			node<T>* temp = head;
			T result = temp->value;
			head = head->next;
			delete temp;
			return result;
		}
	}

	void show() {
		node<T>* temp = head;
		while (temp != nullptr) {
			cout << temp->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void deleteQueue() {
		node<T>* temp;
		while (head != nullptr) {
			temp = head;
			head = head->next;
			delete temp;
		}
		cout << "큐가 삭제됨" << endl;
	}
};

template <typename T>
class deque {
private:
	node<T>* head;
	node<T>* tail;

public:
	deque() : head(nullptr), tail(nullptr) {

	}
	~deque() {
		deleteDeque();
	}

	void head_enqueue(T value) {
		node<T>* temp = new node<T>;
		temp->next = nullptr;
		temp->prev = nullptr;
		temp->value = value;

		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
	}

	T head_dequeue() {
		if (head == nullptr) {
			throw nullptrError();
		}
		else {
			node<T>* temp = head;
			T result = temp->value;
			head = head->next;
			if (head != nullptr) head->prev = nullptr;
			delete temp;
			return result;
		}
	}

	void tail_enqueue(T value) {
		node<T>* temp = new node<T>;
		temp->next = nullptr;
		temp->prev = nullptr;
		temp->value = value;

		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}

	T tail_dequeue() {
		if (tail == nullptr) {
			throw nullptrError();
		}
		else {
			node<T>* temp = tail;
			T result = temp->value;
			tail = tail->prev;
			if (tail != nullptr) tail->next = nullptr;
			delete temp;
			return result;
		}
	}
	
	void show() {
		node<T>* temp = head;
		while (temp != nullptr) {
			cout << temp->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void deleteDeque() {
		node<T>* temp;
		while (head != nullptr) {
			temp = head;
			head = head->next;
			delete temp;
		}
		cout << "큐가 삭제됨" << endl;
	}
};

int main() {
	int choice = -1, input = -1, queChoice = -1;
	bool check_out = false;

	cout << "queue 를 선택하려면 0, dequeue 를 선택하려면 1 을 입력하세요 : " << endl;
	cin >> queChoice;
	if (queChoice == 0) {
		try {
			queue<int> test = queue<int>();
			while (1) {
				cout << "1.삽입 2.삭제 3.출력 4.종료" << endl;
				cin >> choice;

				switch (choice) {
				case 1:
					cin >> input;
					test.enqueue(input);
					break;

				case 2:
					cout << test.dequeue() << endl;
					break;

				case 3:
					test.show();
					break;

				case 4:
					check_out = true;
					break;
				}
				cout << endl;
				if (check_out) break;
			}
		}
		catch (nullptrError npe) {
			npe.ExceptionError();
		}
	}
	else {
		deque<int> test = deque<int>();
		try {
			while (1) {
				cout << "1.앞에서 삽입 2.앞에서 삭제 3.뒤에서 삽입 4.뒤에서 삭제 5.출력 6.종료" << endl;
				cin >> choice;

				switch (choice) {
				case 1:
					cin >> input;
					test.head_enqueue(input);
					break;

				case 2:
					cout << test.head_dequeue() << endl;
					break;

				case 3:
					cin >> input;
					test.tail_enqueue(input);
					break;

				case 4:
					cout << test.tail_dequeue() << endl;
					break;

				case 5:
					test.show();
					break;

				case 6:
					check_out = true;
					break;
				}
				cout << endl;
				if (check_out) break;
			}
		}
		catch (nullptrError npe) {
			npe.ExceptionError();
		}
	}
	return 0;
}