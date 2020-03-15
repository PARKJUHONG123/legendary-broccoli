#include <cstdio>
#include <iostream>
#include <ctime>
#include <list>
using namespace std;

//1. seperate chaining
template <typename V>
class HashMap_SP {
private:
	int fixed_size;
	list<V>* table;

public:
	HashMap_SP(int size) {
		this->fixed_size = size;
		table = new list<V>[fixed_size];
	}

	~HashMap_SP() {
		table->~list;
	}

	void insertNode(V value) {
		int index = hash(value);
		table[index].push_back(value);
	}

	void deleteNode(V value) {
		int index = hash(value);

		typename list<V> ::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++) {
			if (*i == value) break;
		}
		if (i != table[index].end()) {
			table[index].erase(i);
		}
	}

	int hash(V value) {
		return (value % fixed_size);
	}

	void display() {
		for (int i = 0; i < fixed_size; i++) {
			cout << i;
			for (auto value : table[i]) {
				cout << "--> " << value;
			}
			cout << endl;
		}
	}
};


//2. open addressing 
template <typename K, typename V>
class HashNode {
public:
	V value;
	K key;

	HashNode(K key, V value) {
		this->value = value;
		this->key = key;
	}
};

template <typename V>
class HashMap_OA {
private:
	HashNode<int, V>** arr;
	int capacity;
	int size;

public:
	HashMap_OA(int cap) : capacity(cap), size(0) {
		arr = new HashNode<int, V> * [capacity];
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;
	}

	~HashMap_OA() {
		delete[] arr;
	}

	int hashCode(V value) {
		return value % capacity;
	}

	int open_address(int hashIndex) {
		hashIndex++;
		hashIndex %= capacity;
		return hashIndex;
	}

	void insertNode(V value) {
		int hashIndex = hashCode(value);

		while (arr[hashIndex] != NULL) {
			hashIndex = open_address(hashIndex);
		}

		if (arr[hashIndex] == NULL) {
			size++;
		}
		HashNode<int, V>* temp = new HashNode<int, V>(hashIndex, value);
		arr[hashIndex] = temp;

		if (isFull()) {
			arr = expand(&capacity, arr);
		}
	}

	int deleteNode(V value) {
		int result = get(value);
		if (-1 == result) {
			cout << "해당하는 값이 없음" << endl;
			return NULL;
		}
		arr[result] = NULL;
		return result;
	}
	
	int get(V value) {
		int hashIndex = hashCode(value);
		int count = 0;

		while (arr[hashIndex]->value != value) {
			hashIndex = open_address(hashIndex);
			if (++count == size) {
				return -1;
			}
		}
		return hashIndex;
	}
	
	int getSize() {
		return size;
	}

	bool isFull() {
		return size == capacity;
	}

	bool isEmpty() {
		return size == 0;
	}

	void display() {
		for (int i = 0; i < capacity; i++) {
			if (arr[i] != NULL && arr[i]->key != -1) {
				cout << "key = " << arr[i]->key
					<< "   value = " << arr[i]->value << endl;
			}
		}
	}

	HashNode<int, V>** expand(int *capacity, HashNode<int, V>** arr){
		HashNode<int, V>** temp = new HashNode<int, V> * [*capacity * 2];
		HashNode<int, V>* _temp;

		for (int i = 0; i < *capacity; i++){
			_temp = new HashNode<int, V>(arr[i]->key, arr[i]->value);
			temp[i] = _temp;
		}

		for (int i = *capacity; i < *capacity * 2; i++) {
			temp[i] = NULL;
		}

		for (int i = 0; i < *capacity; i++) {
			delete[] arr[i];
		}

		*capacity = *capacity * 2;
		delete[] arr;
		return temp;
	}
};

int main() {
	int choice = -1, input = -1, hashKind = -1;
	bool check_out = false;

	cout << "초기 배열 크기를 설정하세요" << endl;
	while (input < 0) {
		cin >> input;
	}

	cout << "Seperate Chaining HashMap 이면 0, Open Addressing HashMap 이면 1 을 입력하세요" << endl;
	cin >> hashKind;

	if (hashKind == 0) {
		HashMap_SP<int>* h_sp = new HashMap_SP<int>(input);

		while (1) {
			cout << "1.삽입 2.삭제 3.출력 4.종료" << endl;
			cin >> choice;

			switch (choice) {
			case 1:
				cin >> input;
				h_sp->insertNode(input);
				break;

			case 2:
				cin >> input;
				h_sp->deleteNode(input);
				break;

			case 3:
				h_sp->display();
				break;

			case 4:
				check_out = true;
				break;
			}
			cout << endl;
			if (check_out) break;
		}
	}
	else {
		HashMap_OA<int>* h = new HashMap_OA<int>(input);

		while (1) {
			cout << "1.삽입 2.삭제 3.출력 4.종료" << endl;
			cin >> choice;

			switch (choice) {
			case 1:
				cin >> input;
				h->insertNode(input);
				break;

			case 2:
				cin >> input;
				if (h->isEmpty()) {
					cout << "empty";
				}
				else {
					cout << "삭제한 키: " << h->deleteNode(input) << endl;
				}
				break;

			case 3:
				if (h->isEmpty()) {
					cout << "empty";
				}
				else {
					h->display();
				}
				break;

			case 4:
				check_out = true;
				break;
			}
			cout << endl;
			if (check_out) break;
		}
	}
	return 0;
}
