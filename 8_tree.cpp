#include <cstdio>
#include <iostream>

#define RED 0
#define BLACK 1

using namespace std;

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
			cout << "큐가 삭제됨" << endl;
		}
	};
}


template <typename T>
struct node {
	T value;
	int color = -1;
	node<T>* left = nullptr;
	node<T>* right = nullptr;
};

template <typename T>
class binary_tree{
private:
	node<T>* root;
public:
	binary_tree() : root(nullptr){

	}
	~binary_tree() {

	}

	node<T>* getRoot() {
		return root;
	}

	void add(T value) {
		node<T>* index = root;
		node<T>* temp = new node<T>;
		temp->value = value;

		while (1) {
			if (index == nullptr) {
				root = temp;
				break;
			}
			else {
				if (index->value > temp->value) {
					if (index->left == nullptr) {
						index->left = temp;
						break;
					}
					else {
						index = index->left;
					}
				}
				else if (index->value < temp->value) {
					if (index->right == nullptr) {
						index->right = temp;
						break;
					}
					else {
						index = index->right;
					}
				}
				else {
					cout << "중복된 값 발견 : " << index->value << " = "<< temp->value << endl;
					delete[]temp;
					break;
				}
			}
		}
	}

	T remove(T value, node<T>* parent, node<T>* index) {
		if (index == root) {

		}
		else {
			if (parent->left == index) {

			}
			else {

			}
		}

		if (index->left != nullptr) {
			remove(value, index, index->left);
		}

		if (index->right != nullptr) {
			remove(value, index, index->right);
		}
		
	}

	void preorder(node<T>* index) {
		cout << index->value << " ";
		if (index->left != nullptr) {
			preorder(index->left);
		}
		if (index->right != nullptr) {
			preorder(index->right);
		}
	}

	void inorder(node<T>* index) {
		if (index->left != nullptr) {
			inorder(index->left);
		}
		cout << index->value << " ";
		if (index->right != nullptr) {
			inorder(index->right);
		}
	}

	void postorder(node<T>* index) {
		if (index->left != nullptr) {
			postorder(index->left);
		}
		if (index->right != nullptr) {
			postorder(index->right);
		}
		cout << index->value << " ";

	}

	void levelorder(node<T>* index) {
		queue_space::queue<node<T>> queue = queue_space::queue<node<T>>();
		queue.enqueue(*index);
		node<T> node;

		while (queue.returnHead() != nullptr) {
			node = queue.dequeue();
			cout << node.value << " ";
			if (node.left != nullptr) {
				queue.enqueue(*(node.left));
			}
			if (node.right != nullptr) {
				queue.enqueue(*(node.right));
			}
		}
	}
};

template <typename T>
class red_black_tree {
private:

public:

};

int main() {
	binary_tree<char> tree = binary_tree<char>();
	node<char>* root;

	tree.add('F');
	tree.add('B');
	tree.add('A');
	tree.add('D');
	tree.add('C');
	tree.add('E');
	tree.add('G');
	tree.add('I');
	tree.add('H');
	
	root = tree.getRoot();
	if (root == nullptr) {
		cout << "error";
	}
	else {
		tree.preorder(root);
		cout << endl;
		tree.inorder(root);
		cout << endl;
		tree.postorder(root);
		cout << endl;
		tree.levelorder(root);
		cout << endl;
	}

	return 0;
}