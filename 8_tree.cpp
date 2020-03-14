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

// 삭제 과정에서 메모리 잔여 문제가 발생해서 다시 코드 작성
template <typename T>
class binary_tree {
private:
	node<T> *root;

public:
	binary_tree() : root(nullptr){

	}
	~binary_tree() {
		deleteTree();
	}

	node<T>* getRoot() {
		return root;
	}

	void add(T value) {
		node<T>* search_node = root;
		node<T>* temp = new node<T>;
		temp->left = nullptr;
		temp->right = nullptr;
		temp->value = value;

		if (root == nullptr) {
			root = temp;
		}
		else {
			while (1) {
				if (search_node->value < temp->value) {
					if (search_node->right == nullptr) {
						search_node->right = temp;
						break;
					}
					else {
						search_node = search_node->right;
					}
				}
				else if (search_node->value > temp->value){
					if (search_node->left == nullptr) {
						search_node->left = temp;
						break;
					}
					else {
						search_node = search_node->left;
					}
				}
				else {
					cout << "add error";
					break;
				}
			}
		}
	}

	T remove(T value) {
		bool leftFromParent = false;
		node<T>* parent = nullptr;
		node<T>* target = root;
		if (target == nullptr) {
			cout << "remove error : root nullptr";
			return NULL;
		}

		while (1) {
			if (target->value < value) {
				if (target->right == nullptr) {
					cout << "remove error : no child";
					return NULL;
				}
				parent = target;
				leftFromParent = false;
				target = target->right;
			}
			else if (target->value > value) {
				if (target->left == nullptr) {
					cout << "remove error : no child";
					return NULL;
				}
				parent = target;
				leftFromParent = true;
				target = target->left;
			}
			else {
				break;
			}
		}

		// 이제 target 이 바로 value 값을 가진 node
		
		// 고려해야 할 것 target = root 일 때 
		if (parent == nullptr) { // 즉 target == root
			if (target->left == nullptr && target->right == nullptr) { //무자식
				delete[]target;
				root = nullptr;
				cout << "empty tree" << endl;
			}
			else if (target->left != nullptr && target->right != nullptr){ //자식2
				node<T>* temp_child, * temp_parent;
				temp_child = target->right;
				temp_parent = target;			
				while (1) {
					if (temp_child->left != nullptr) {
						temp_parent = temp_child;
						temp_child = temp_child->left;
					}
					else {
						break;
					}
				}

				if (temp_parent == target) {
					target->value = temp_child->value;
					temp_parent->right = temp_child->right;
					delete[] temp_child;
				}
				else {
					if (temp_child->right == nullptr) {
						target->value = temp_child->value;
						temp_parent->left = nullptr;
						delete[]temp_child;
					}
					else {
						target->value = temp_child->value;
						temp_parent->left = temp_child->right;
						delete[]temp_child;
					}
				}
			}
			else { // 자식1
				if (target->left == nullptr) {
					root = target->right;
					delete[] target;
				}
				else {
					root = target->left;
					delete[] target;
				}
			}
			return value;
		}



		// 고려해야 할 것 : 무자식, 자식2, 자식1
		if (target->left == nullptr && target->right == nullptr) { // 무자식
			if (leftFromParent == true) {
				parent->left = nullptr;
				delete[] target;
			}
			else {
				parent->right = nullptr;
				delete[] target;
			}
		}
		else if (target->left != nullptr && target->right != nullptr) { // 자식2
			node<T>* temp_child, *temp_parent;
			temp_child = target->right;
			temp_parent = target;
			while (1) {
				if (temp_child->left != nullptr) {
					temp_parent = temp_child;
					temp_child = temp_child->left;
				}
				else {
					break;
				}
			}

			if (temp_parent == target) {
				target->value = temp_child->value;
				temp_parent->right = temp_child->right;
				delete[] temp_child;
			}
			else {
				if (temp_child->right == nullptr) {
					target->value = temp_child->value;
					temp_parent->left = nullptr;
					delete[]temp_child;
				}
				else {
					target->value = temp_child->value;
					temp_parent->left = temp_child->right;
					delete[]temp_child;
				}
			}
		}
		else { // 자식1
			if (leftFromParent == true) {
				if (target->left == nullptr) {
					parent->left = target->right;
					delete[] target;
				}
				else {
					parent->left = target->left;
					delete[] target;
				}
			}
			else {
				if (target->left == nullptr) {
					parent->right = target->right;
					delete[] target;
				}
				else {
					parent->right = target->left;
					delete[] target;
				}
			}
		}
		return value;
	}

	void deleteTree() {
		node<T>* temp;
		while (1) {
			temp = getRoot();
			if (temp == nullptr) {
				break;
			}
			else {
				remove(temp->value);
			}
		}
	}

	void preorder(node<T>* root) {
		if (root == nullptr) return;
		cout << root->value << " ";
		preorder(root->left);
		preorder(root->right);
	}
	void inorder(node<T>* root) {
		if (root == nullptr) return;
		preorder(root->left);
		cout << root->value << " ";
		preorder(root->right);

	}
	void postorder(node<T>* root) {
		if (root == nullptr) return;
		preorder(root->left);
		preorder(root->right);
		cout << root->value << " ";
	}
	void levelorder(node<T>* root) {
		node<T>* temp;
		queue_space::queue<node<T>*> *queue = new queue_space::queue<node<T>*>;
		queue->enqueue(root);
		while (queue->returnHead() != nullptr) {
			temp = queue->dequeue();
			cout << temp->value << " ";
			if (temp->left != nullptr) {
				queue->enqueue(temp->left);
			}
			if (temp->right != nullptr) {
				queue->enqueue(temp->right);
			}
		}
	}

};

int main() {

	//red_black_tree<int> tree = red_black_tree<int>();
	binary_tree<int> tree = binary_tree<int>();
	node<int>* root;
	int choice = -1, input = -1;
	bool check_out = false;

	while (1) {
		//1 6 1 2 1 8 1 1 1 4 1 3 1 5 1 7 1 10 1 9
		cout << "1.삽입 2.삭제 3.출력 4.종료" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cin >> input;
			tree.add(input);
			break;

		case 2:
			cin >> input;
			root = tree.getRoot();
			if (root == nullptr) {
				cout << "empty";
			}
			else {
				cout << tree.remove(input);
			}
			break;

		case 3:
			root = tree.getRoot();
			if (root == nullptr) {
				cout << "empty";
			}
			else {
				cout << "preorder : ";
				tree.preorder(root);
				cout << endl;

				cout << "inorder : ";
				tree.inorder(root);
				cout << endl;
				
				cout << "postorder : ";
				tree.postorder(root);
				cout << endl;
				
				cout << "levelorder : ";
				tree.levelorder(root);
				cout << endl;
			}
			break;

		case 4:
			check_out = true;
			break;
		}
		cout << endl;
		if (check_out) break;
	}
	return 0;
}