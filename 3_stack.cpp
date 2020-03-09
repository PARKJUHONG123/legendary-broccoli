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
		cout << "Error : " << index << " <= " << bound << endl << "Reason : " << "Out of Boundary" << endl;
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
		cout << "delete arrayStack" << endl;
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

	void print() {
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
	
	void print() {
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
			print();
			temp = temp->next;
			delete top;
			top = temp;
		}
	}
};

int main() {
	/*
	linkedStack<int> stack = linkedStack<int>();
	for (int i = 0; i < 10; i++) {
		stack.push(i);
		stack.print();
	}
	stack.print();
	cout << "pop : " << stack.pop() << endl;
	*/

	try {
		arrayStack<int> stack = arrayStack<int>();
		for (int i = 0; i < 10; i++) {
			stack.push(i);
			stack.print();
		}
		for (int i = 0; i < 11; i++) {
			cout << "pop : " << stack.pop() << endl;
			stack.print();
		}
	}
	catch (OutBoundaryException obpn){
		obpn.ExceptionReason();
	}
	return 0;
}