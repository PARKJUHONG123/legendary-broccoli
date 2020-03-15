#include <iostream>
#include <cstdio>

#define MIN_INT -99999
#define MAX_INT +99999

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
class max_heap {
private:
	int MAXSIZE;
	T* node_array;
	int node_index;

	void add_sort() {
		int target_index = -1;
		T temp_value = NULL;

		for (int i = node_index; i > 1; i /= 2) { // 아래
			target_index = i / 2; // 위

			if (node_array[target_index] < node_array[i]) {
				temp_value = node_array[i];
				node_array[i] = node_array[target_index];
				node_array[target_index] = temp_value;
			}
		}
	}

	void remove_sort(int index) {
		if (2 * index > node_index) { // 자식 없음
			return;
		}
		T temp_value = NULL;
		int son_index = -1;

		if (2 * index + 1 <= node_index) { // 자식 2명
			if (node_array[2 * index] > node_array[2 * index + 1]) {
				son_index = 2 * index;
			}
			else {
				son_index = 2 * index + 1;
			}
		}
		else { // 자식 왼쪽 1명
			son_index = 2 * index;
		}

		if (son_index != -1 && node_array[son_index] > node_array[index]) {
			temp_value = node_array[son_index];
			node_array[son_index] = node_array[index];
			node_array[index] = temp_value;
			remove_sort(son_index);
		}
	}

public:
	max_heap() : MAXSIZE(255), node_index(1) {
		node_array = new T[MAXSIZE];
	}
	~max_heap() {
		delete []node_array;
		cout << "힙이 삭제됨" << endl;
	}

	void add(T value) {
		if (node_index > MAXSIZE) {
			throw OutBoundaryException(node_index, MAXSIZE);
		}
		node_array[node_index] = value;
		add_sort();
		node_index++;
	}
	
	T remove() {
		T result = node_array[1];
		if (node_index <= 1) {
			throw OutBoundaryException(node_index, 1);
		}
		node_array[1] = node_array[node_index - 1];
		remove_sort(1);
		node_index--;
		return result;
	}

	T remove(T value) {
		if (node_index <= 1) {
			throw OutBoundaryException(node_index, 1);
		}

		int index = 1;
		T temp, result;
		for (index = 1; index < node_index; index++) {
			if (node_array[index] == value) {
				break;
			}
		}
		result = node_array[index];
		node_array[index] = MAX_INT;

		for (int i = index; i > 1; i /= 2) {
			if (node_array[i] > node_array[i / 2]) {
				temp = node_array[i];
				node_array[i] = node_array[i / 2];
				node_array[i / 2] = temp;
			}
		}

		node_array[1] = node_array[node_index - 1];
		remove_sort(1);
		node_index--;
		return result;
	}

	void show() {
		for (int i = 1; i < node_index; i++) {
			cout << node_array[i] << ' ';
		}
		cout << endl;
	}
};


template <typename T>
class min_heap {
private:
	int MAXSIZE;
	T* node_array;
	int node_index;

	void add_sort() {
		int target_index = -1;
		T temp_value = NULL;

		for (int i = node_index; i > 1; i /= 2) { // 아래
			target_index = i / 2; // 위

			if (node_array[target_index] > node_array[i]) {
				temp_value = node_array[i];
				node_array[i] = node_array[target_index];
				node_array[target_index] = temp_value;
			}
		}
	}

	void remove_sort(int index) {
		if (2 * index > node_index) { // 자식 없음
			return;
		}
		T temp_value = NULL;
		int son_index = -1;

		if (2 * index + 1 <= node_index) { // 자식 2명
			if (node_array[2 * index] < node_array[2 * index + 1]) {
				son_index = 2 * index;
			}
			else {
				son_index = 2 * index + 1;
			}
		}
		else { // 자식 왼쪽 1명
			son_index = 2 * index;
		}
		if (son_index != -1 && node_array[son_index] < node_array[index]) {
			temp_value = node_array[son_index];
			node_array[son_index] = node_array[index];
			node_array[index] = temp_value;
			remove_sort(son_index);
		}
	}

public:
	min_heap() : MAXSIZE(255), node_index(1) {
		node_array = new T[MAXSIZE];
	}
	~min_heap() {
		delete[]node_array;
		cout << "힙이 삭제됨" << endl;
	}

	void add(T value) {
		if (node_index > MAXSIZE) {
			throw OutBoundaryException(node_index, MAXSIZE);
		}
		node_array[node_index] = value;
		add_sort();
		node_index++;
	}

	T remove() {
		T result = node_array[1];
		if (node_index <= 1) {
			throw OutBoundaryException(node_index, 1);
		}
		node_array[1] = node_array[node_index - 1];
		remove_sort(1);
		node_index--;
		return result;
	}

	T remove(T value) {
		if (node_index <= 1) {
			throw OutBoundaryException(node_index, 1);
		}

		int index = 1;
		T temp, result;
		for (index = 1; index < node_index; index++) {
			if (node_array[index] == value) {
				break;
			}
		}
		result = node_array[index];
		node_array[index] = MIN_INT;
		
		for (int i = index; i > 1; i /= 2) {
			if (node_array[i] < node_array[i / 2]) {
				temp = node_array[i];
				node_array[i] = node_array[i / 2];
				node_array[i / 2] = temp;
			}
		}

		node_array[1] = node_array[node_index - 1];
		remove_sort(1);
		node_index--;
		return result;
	}

	void show() {
		for (int i = 1; i < node_index; i++) {
			cout << node_array[i] << ' ';
		}
		cout << endl;
	}
};


int main() {
	int heapChoice = -1, choice = -1, input = -1;
	bool check_out = false;
	
	cout << "최대 힙은 0, 최소 힙은 1 을 입력하세요" << endl;
	cin >> heapChoice;

	if (heapChoice == 0) {
		try {
			max_heap<int> test = max_heap<int>();
			while (1) {
				cout << "1.삽입 2.삭제 3.출력 4.종료" << endl;
				cin >> choice;

				switch (choice) {
				case 1:
					cin >> input;
					test.add(input);
					break;

				case 2:
					cout << test.remove() << endl;
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
		catch (OutBoundaryException obpn) {
			obpn.ExceptionReason();
		}
	}
	else {
		try {
			min_heap<int> test = min_heap<int>();
			while (1) {
				cout << "1.삽입 2.삭제 3.출력 4.종료" << endl;
				cin >> choice;

				switch (choice) {
				case 1:
					cin >> input;
					test.add(input);
					break;

				case 2:
					cin >> input;
					cout << test.remove(input) << endl;
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
		catch (OutBoundaryException obpn) {
			obpn.ExceptionReason();
		}
	}
	

	return 0;
}
