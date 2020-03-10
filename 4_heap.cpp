#include <iostream>
#include <cstdio>

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

	void sort() {
		int target_index = -1;
		T temp_value = NULL;

		for (int i = node_index; i > 1; i /= 2) { // ¾Æ·¡
			target_index = i / 2; // À§

			if (node_array[target_index] < node_array[i]) {
				temp_value = node_array[i];
				node_array[i] = node_array[target_index];
				node_array[target_index] = temp_value;
			}
		}
	}

public:
	max_heap() : MAXSIZE(255), node_index(1) {
		node_array = new T[MAXSIZE];
	}
	~max_heap() {
		delete []node_array;
		cout << "ÈüÀÌ »èÁ¦µÊ" << endl;
	}

	void add(T value) {
		if (node_index > MAXSIZE) {
			throw OutBoundaryException(node_index, MAXSIZE);
		}
		node_array[node_index] = value;
		sort();
		node_index++;
	}
	
	T remove() {
		T result = node_array[1];
		if (node_index < 1) {
			throw OutBoundaryException(node_index, 1);
		}
		node_array[1] = node_array[node_index - 1];
		sort();
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
	max_heap<int> heap = max_heap<int>();
	try {
		heap.add(9);
		heap.add(7);
		heap.add(5);
		heap.add(3);
		heap.add(5);
		heap.add(10);
		heap.show();

		heap.remove();
		heap.remove();
		heap.remove();
		heap.remove();
		heap.remove();
		heap.remove();
		heap.remove();
		heap.remove();
		heap.show();
	}
	catch (OutBoundaryException obpn){
		obpn.ExceptionReason();
	}

	return 0;
}
