#include <cstdio>
#include <iostream>
using namespace std;

#define INF 99999
namespace stack_space {
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
			delete[]arr;
		}

		void push(T value) {
			if (element_number >= arr_length) {
				T* temp = new T[arr_length];
				for (int i = 0; i < arr_length; i++) {
					temp[i] = arr[i];
				}
				delete[]arr;
				arr_length *= 2;
				arr = new T[arr_length];
				for (int i = 0; i < arr_length / 2; i++) {
					arr[i] = temp[i];
				}
				delete[]temp;

			}
			arr[element_number] = value;
			element_number += 1;
		}

		T pop() {
			element_number -= 1;
			if (element_number < 0) {
				return NULL;
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
}

namespace queue_space {
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

		node<T>* returnHead() {
			return head;
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
		}
	};
}

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

	node<T>* getHead() {
		return head;
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

	void show() const {
		node<T>* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->value << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};

template <typename T>
class graph_linked {
private:
	int size;
	singleLinked<T>* link;

public:
	graph_linked(int num) : size(num) {
		link = new singleLinked<T>[size];
	}

	void addEdge_undirected(int u, int v) {
		link[u].add(v);
		link[v].add(u);
	}

	void addEdge_directed(int u, int v) {
		link[u].add(v);
	}

	void show() {
		for (int i = 0; i < size; i++) {
			cout << "\n Adjacency list of vertex "
				<< i << "\n head ";
			link[i].show();
		}
		cout << endl;
	}

	void dfs_noRecursive() {
		node<T>* temp;
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
		cout << "Depth First Search - No Recursive : ";
		for (int i = 0; i < size; i++) {
			if (visited[i] == false) {
				visited[i] = true;
				cout << i << " ";
				temp = link[i].getHead();
				if (temp != nullptr) {
					if (visited[temp->value] == false) {
						visited[temp->value] = true;
						cout << temp->value << " ";
					}
				}
				else {
					continue;
				}
				temp = temp->next;
			}
		}
	}

	void dfs_recursive(int start) {
		if (start >= size || start < 0) {
			cout << "start error" << endl;
			return;
		}
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
		cout << "Depth First Search - Recursive : ";

		visited[start] = true;
		cout << start << " ";
		dfs_inner(visited, start);
	}

	void dfs_inner(bool* visited, int start) {
		node<T>* temp = link[start].getHead();

		while (temp != nullptr) {
			if (visited[temp->value] == false) {
				visited[temp->value] = true;
				cout << temp->value << " ";
				dfs_inner(visited, temp->value);
			}
			else {
				temp = temp->next;
			}
		}
	}
};

class graph_matrix {
private:
	int size = 0;
	int** arr;

public:
	graph_matrix(int num) : size(num){
		arr = new int* [size];
		for (int i = 0; i < size; i++) {
			arr[i] = new int[size];
			for (int j = 0; j < size; j++) {
				arr[i][j] = INF;
			}
		}
	}

	~graph_matrix() {
		for (int i = 0; i < size; i++) {
			delete[]arr[i];
		}
		delete[]arr;
	}

	void addEdge_undirected(int u, int v) {
		arr[u][v] = 1;
		arr[v][u] = 1;
	}

	void addEdge_directed(int u, int v) {
		arr[u][v] = 1;
	}

	void addEdge_undirected_weighted(int u, int v, int weight) {
		arr[u][v] = weight;
		arr[v][u] = weight;
	}

	void addEdge_directed_weighted(int u, int v, int weight) {
		arr[u][v] = weight;
	}

	void show() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << ((arr[i][j] == INF) ? 0 : arr[i][j]) << " ";;
			}
			cout << endl;
		}
		cout << endl;
	}

	void bfs_withQueue(int start) {
		queue_space::queue<int>* Queue = new queue_space::queue<int>();
		int temp;
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}

		cout << "Breadth First Search - With Queue : ";
		visited[start] = true;
		Queue->enqueue(start);

		while (Queue->returnHead() != nullptr) {
			temp = Queue->dequeue();
			cout << temp << " ";
			
			for (int j = 0; j < size; j++) {
				if (visited[j] == false) {
					if (arr[temp][j] != INF) {
						visited[j] = true;
						Queue->enqueue(j);
					}
				}
			}
		}

		delete Queue;
		delete[] visited;
		cout << endl;
	}


	void dfs_noRecursive(int start) {
		stack_space::arrayStack<int>* Stack = new stack_space::arrayStack<int>();
		bool* visited = new bool[size];
		int temp;
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}

		cout << "Depth First Search - With Stack : ";
		visited[start] = true;
		Stack->push(start);

		for (int i = 0; i < size; i++) {
			if (arr[start][i] != INF) {
				if (visited[i] == false) {
					visited[i] = true;
					Stack->push(i);
				}
			}
			temp = Stack->pop();
			cout << temp << " ";
			for (int j = 0; j < size; j++) {
				if (arr[temp][j] != INF) {
					if (visited[j] == false) {
						visited[j] = true;
						Stack->push(j);
					}
				}
			}
		}
	
		while ((temp = Stack->pop()) != NULL) {
			cout << temp << " ";
		}

		delete Stack;
		delete[] visited;
		cout << endl;
	}


	void dfs_inner(bool* visited, int i) {
		visited[i] = true;
		cout << i  << " ";

		for (int j = 0; j < size; j++) {
 			if (arr[i][j] != INF) {
				if (visited[j] == false) {
					dfs_inner(visited, j);
				}
			}
		}
	}

	void dfs_recursive(int start) {
		if (start >= size || start < 0) {
			cout << "start error" << endl;
			return;
		}

		cout << "Depth First Search - Recursive : ";
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}

		dfs_inner(visited, start);
		cout << endl;
		delete[]visited;
	}
};

int main() {
	graph_matrix* graph_m = new graph_matrix(8);
	graph_m->addEdge_undirected(0, 1);
	graph_m->addEdge_undirected(0, 2);
	graph_m->addEdge_undirected(1, 3);
	graph_m->addEdge_undirected(1, 4);
	graph_m->addEdge_undirected(2, 5);
	graph_m->addEdge_undirected(2, 6);
	graph_m->addEdge_undirected(3, 7);
	graph_m->addEdge_undirected(4, 7);
	graph_m->show();
	graph_m->dfs_recursive(0);
	graph_m->dfs_noRecursive(0);
	graph_m->bfs_withQueue(0);

	return 0;
}