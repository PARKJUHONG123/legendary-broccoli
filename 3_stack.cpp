#include <cstdio>
#include <iostream>

using namespace std;

template <typename T>
struct node {
public:
	T value;
	node<T>* next = nullptr;
};

class OutBoundaryException {
private:
	int index, bound;
public:
	OutBoundaryException() : index(0), bound(0) {

	}
	OutBoundaryException(int a, int b) : index(a), bound(b) {

	}
	void ExceptionReason() {
		cout << "Error Reason : " << "Out of Boundary" << endl << "Index = " << index << endl << "Bound = " << bound << endl;
	}
};

template <typename T>
class arrayStack {
private:
	int element_number;
	int arr_length;
	T* arr;

public:
	arrayStack() : arr_length(1), element_number(0) {
		arr = new T[arr_length];
	}
	~arrayStack() {
		delete []arr;
		cout << "배열 스택이 삭제됨" << endl;
	}

	void push(T value) {		
		if (element_number >= arr_length) {
			T* temp = new T[arr_length];
			for (int i = 0; i < arr_length; i++) {
				temp[i] = arr[i];
			}
			delete []arr;
			arr_length *= 2;
			arr = new T[arr_length];
			for (int i = 0; i < arr_length / 2; i++) {
				arr[i] = temp[i];
			}
			delete []temp;
			
		}
		arr[element_number] = value;
		element_number += 1;
	}

	T pop() {
		element_number -= 1;
		if (element_number < 0) {
			throw OutBoundaryException(element_number, 0);
		}
		return arr[element_number];
	}

	void show() {
		for (int i = 0; i < element_number; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};

template <typename T>
class linkedStack {
private:
	node<T>* top = nullptr;

public:
	linkedStack() : top(nullptr){

	}
	~linkedStack() {
		deleteStack();
	}

	void push(T value) {
		node<T>* temp = new node<T>;
		temp->value = value;
		temp->next = nullptr;

		if (top == nullptr) {
			top = temp;
		}
		else {
			temp->next = top;
			top = temp;
		}
	}
	
	T pop() {
		T result;
		node<T>* temp = top;
		if (top == nullptr) {
			cout << "empty stack" << endl;
		}
		else {
			result = temp->value;
			temp = temp->next;
			delete top;
			top = temp;
			return result;
		}
	}
	
	void show() {
		node<T>* temp = top;
		while (temp != nullptr) {
			cout << temp->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void deleteStack() {
		node<T>* temp = top;
		while (temp != nullptr) {
			temp = temp->next;
			delete top;
			top = temp;
		}
		cout << "링크드 스택이 삭제됨" << endl;
	}
};

int main() {
	// arrayStack<int> stack = arrayStack<int>();
	linkedStack<int> stack = linkedStack<int>();
	int choice = -1, input = -1;
	bool check_out = false;

	try {
		while (1) {
			cout << "1.삽입 2.삭제 3.출력 4.종료" << endl;
			cin >> choice;

			switch (choice) {
			case 1:
				cin >> input;
				stack.push(input);
				break;

			case 2:
				cout << stack.pop() << endl;
				break;

			case 3:
				stack.show();
				break;

			case 4:
				check_out = true;
				break;
			}
			if (check_out) break;
		}
	}
	catch (OutBoundaryException obpn) {
		obpn.ExceptionReason();
	}
	return 0;
}