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

	// �ʱ�ȭ
	ArrayList(int num) : size(num + 1), used(0) {
		if (size < 1) {
			throw OutBoundaryException();
		}
		arr = new T[size];
	}

	// ������ �߰�
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

	// ������ ����
	T remove() {
		T result = arr[used];
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
		return result;
	}

	void show() {
		for (int i = 0; i < used; i++) {
			cout << arr[i] << ' ';
		}
		cout << endl;
	}

	// �ε����� ������ ����
	T remove_index(int index) {
		T result;
		if (index >= used) {
			throw OutBoundaryException(index, used);
		}
		result = arr[index];
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
		return result;
	}

	// �ش� �ε����� ������ ��ȯ
	T& operator[](int index) {
		if (index >= used) {
			throw OutBoundaryException(index, used);
		}
		return arr[index];
	}

	// �Ҹ���
	~ArrayList() {
		delete[]arr;
		cout << "free dynamic arrays" << endl;
	}
};

int main() {
	ArrayList<int> arrayList;
	int size;
	int choice = -1, input = -1;
	bool check_out = false;

	cout << "ũ�⸦ �Է��ϼ���" << endl;
	cin >> size;
	arrayList = ArrayList<int>(size);

	try {
		while (1) {
			cout << "1.���� 2.���� 3.��� 4.����" << endl;
			cin >> choice;

			switch (choice) {
			case 1:
				cin >> input;
				arrayList.add(input);
				break;

			case 2:
				cout << "Ư�� �ε����� �Է��ϼ��� (������ -1)" << endl;
				cin >> input;
				if (input == -1) {
					cout << arrayList.remove() << endl;
				}
				else {
					cout << arrayList.remove_index(input) << endl;
				}
				break;

			case 3:
				arrayList.show();
				break;

			case 4:
				check_out = true;
				break;
			}
			cout << endl;
			if (check_out) break;
		}
	}
	catch (OutBoundaryException obpn) {
		obpn.ExceptionReason();
	}

	return 0;
}