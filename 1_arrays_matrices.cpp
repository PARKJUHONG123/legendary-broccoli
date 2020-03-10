#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

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
class ArrayList {
private:
	int size;
	int used;
	T* arr;

public:
	ArrayList() : size(1), used(0) {
		arr = new T[size];
	}

	// 초기화
	ArrayList(int num) : size(num + 1), used(0) {
		if (size < 1) {
			throw OutBoundaryException();
		}
		arr = new T[size];
	}

	// 데이터 추가
	void add(T input) {
		if (used + 1 < size) {
			arr[used] = input;
		}
		else {
			T* temp = new T[size];
			for (int i = 0; i < used; i++) {
				temp[i] = arr[i];
			}
			delete[]arr;

			size *= 2;
			arr = new T[size];

			for (int i = 0; i < used; i++) {
				arr[i] = temp[i];
			}
			delete[]temp;
			arr[used] = input;
		}
		used++;
	}

	// 데이터 제거
	void pop() {
		if (used == 0) {
			throw OutBoundaryException();
		}

		T* temp = new T[--used];
		for (int i = 0; i < used; i++) {
			temp[i] = arr[i];
		}
		delete[]arr;
		arr = new T[size];

		for (int i = 0; i < used; i++) {
			arr[i] = temp[i];
		}
		delete[]temp;
	}

	void print() {
		for (int i = 0; i < used; i++) {
			cout << arr[i] << ' ';
		}
		cout << endl;
	}

	// 인덱스의 데이터 제거
	void pop_index(int index) {
		if (index >= used) {
			throw OutBoundaryException(index, used);
		}

		T* temp = new T[used - 1];
		for (int i = 0; i < index; i++) {
			temp[i] = arr[i];
		}
		for (int i = index + 1; i < used; i++) {
			temp[i - 1] = arr[i];
		}
		delete[]arr;

		arr = new T[--used];
		for (int i = 0; i < used; i++) {
			arr[i] = temp[i];
		}
		delete[]temp;
	}

	// 해당 인덱스의 데이터 반환
	T& operator[](int index) {
		if (index >= used) {
			throw OutBoundaryException(index, used);
		}
		return arr[index];
	}

	// 소멸자
	~ArrayList() {
		delete[]arr;
		cout << "free dynamic arrays" << endl;
	}
};

int main() {
	int size;
	cout << "크기를 입력하세요" << endl;
	cin >> size;

	try {
		ArrayList<char> input_arrays(size);
		input_arrays.add('a');
		input_arrays.add('b');
		input_arrays.add('c');
		cout << input_arrays[2] << endl;
		input_arrays.add('d');
		input_arrays.print();
		input_arrays.pop_index(3);

		input_arrays.print();
		input_arrays.pop();
		input_arrays.print();
		input_arrays.pop();
		input_arrays.print();
		input_arrays.pop();
		input_arrays.print();
		input_arrays.pop();
		input_arrays.print();
	}
	catch (OutBoundaryException obpn) {
		obpn.ExceptionReason();
	}

	return 0;
}