#include <iostream>
#include <cstdio>
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

enum COLOR {red, black};

template <typename T>
class node {
public:
	T value;
	COLOR color;
	node* left, * right, * parent;

	node(T val) : value(val) {
		left = right = parent = nullptr;
		color = red;
	}

	node* uncle() {
		if (parent == nullptr || parent->parent == nullptr) return nullptr;
		if (parent == parent->parent->left) return parent->parent->right;
		else return parent->parent->left;
	}

	node* sibling() {
		if (parent == nullptr) return nullptr;
		if (this == parent->left) return parent->right;
		else return parent->left;
	}


	//	this->parent		this->parent		nParent->parent
	//	this				nParent				this->parent == nParent
	//						this				this
	void moveDown(node* nParent) { 
		if (parent != nullptr) {
			if (this == parent->left) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild() {
		return (left != nullptr && left->color == red) ||
			(right != nullptr && right->color == red);
	}
};

template <typename T>
class red_black_tree {
private:
	node<T>* root;

	void leftRotate(node<T>* x) {
		node<T>* nParent = x->right;

		if (x == root) root = nParent;
		x->moveDown(nParent); // nParent 의 left 와 right 값을 설정하지 않기에 가능
		x->right = nParent->left;

		if (nParent->left != nullptr) nParent->left->parent = x;
		nParent->left = x;
	}

	void rightRotate(node<T>* x) {
		node<T>* nParent = x->left;

		if (x == root) root = nParent;
		x->moveDown(nParent);
		x->left = nParent->right;

		if (nParent->right != nullptr) nParent->right->parent = x;
		nParent->right = x;
	}

	void swapColor(node<T>* x1, node<T>* x2) {
		COLOR temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValue(node<T>* x1, node<T>* x2) {
		T temp;
		temp = x1->value;
		x1->value = x2->value;
		x2->value = temp;
	}

	void fixDoubleRed(node<T>* x) {
		if (x == root) {
			x->color = black;
			return;
		}
		
		node<T>* parent = x->parent,
			* grandparent = parent->parent,
			* uncle = x->uncle();
		
		if (parent->color != black) {
			if (uncle != nullptr && uncle->color == red) {
				parent->color = black;
				uncle->color = black;
				grandparent->color = red;
				fixDoubleRed(grandparent);
			}
			else {
				if (parent == parent->parent->left) {
					if (x == x->parent->left) {
						swapColor(parent, grandparent);
					}
					else {
						leftRotate(parent);
						swapColor(x, grandparent);
					}
					rightRotate(grandparent);
				}
				else {
					if (x == x->parent->left) {
						rightRotate(parent);
						swapColor(x, grandparent);
					}
					else {
						swapColor(parent, grandparent);
					}
					leftRotate(grandparent);
				}
			}
		}
	}

	void fixDoubleBlack(node<T>* x) {
		if (x == root) {
			return;
		}
		node<T>* sibling = x->sibling(),
			* parent = x->parent;

		if (sibling == nullptr) {
			fixDoubleBlack(parent);
		}
		else {
			if (sibling->color == red) {
				parent->color = red;
				sibling->color = black;
				if (sibling == sibling->parent->left) {
					rightRotate(parent);
				}
				else {
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			}
			else {
				if (sibling->hasRedChild()) {
					if (sibling->left != nullptr && sibling->left->color == red) {
						if (sibling == sibling->parent->left) {
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						}
						else {
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else {
						if (sibling == sibling->parent->left) {
							sibling->right->color = parent->color;
							leftRotate(sibling);
							rightRotate(parent);
						}
						else {
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = black;
				}
				else {
					sibling->color = red;
					if (parent->color == black) {
						fixDoubleBlack(parent);
					}
					else {
						parent->color = black;
					}
				}
			}
		}
	}

	node<T>* successor(node<T>* x) {
		node<T>* temp = x;
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		return temp;
	}

	node<T>* replace(node<T>* x) {
		if (x->left != nullptr && x->right != nullptr) {
			return successor(x->right);
		}

		if (x->left == nullptr && x->right == nullptr) {
			return nullptr;
		}

		if (x->left != nullptr) {
			return x->left;
		}
		else {
			return x->right;
		}
	}

	void removeNode(node<T>* v) {
		node<T>* u = replace(v);

		bool uv_black = ((u == nullptr || u->color == black) && (v->color == black));
		node<T>* parent = v->parent;

		if (u == nullptr) {
			if (v == root) {
				root = nullptr;
			}
			else {
				if (uv_black) {
					fixDoubleBlack(v);
				}
				else {
					if (v->sibling() != nullptr) {
						v->sibling()->color = red;
					}
				}

				if (v == v->parent->left) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			delete v;
			return;
		}

		if (v->left == nullptr || v->right == nullptr) {
			if (v == root) {
				v->value = u->value;
				v->left = v->right = nullptr;
				delete u;
			}
			else {
				if (v == v->parent->left) {
					parent->left = u;
				}
				else {
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uv_black) {
					fixDoubleBlack(u);
				}
				else {
					u->color = black;
				}
			}
			return;
		}

		swapValue(u, v);
		removeNode(u);
	}

public:
	red_black_tree() : root(nullptr) {

	}

	node<T>* getRoot() {
		return root;
	}

	node<T>* search(T value) {
		node<T>* temp = root;
		while (temp != nullptr) {
			if (value < temp->value) {
				if (temp->left == nullptr) {
					break;
				}
				else {
					temp = temp->left;
				}
			}
			else if (value == temp->value) {
				break;
			}
			else {
				if (temp->right == nullptr) {
					break;
				}
				else {
					temp = temp->right;
				}
			}
		}
		return temp;
	}

	void add(T value) {
		node<T>* nNode = new node<T>(value);

		if (root == nullptr) {
			nNode->color = black;
			root = nNode;
		}
		else {
			node<T>* temp = search(value);

			if (temp->value == value) {
				cout << "already exists";
				return;
			}
			nNode->parent = temp;

			if (value < temp->value) {
				temp->left = nNode;
			}
			else {
				temp->right = nNode;
			}
		}
		fixDoubleRed(nNode);
	}

	void remove(T value) {
		if (root == nullptr) {
			cout << "tree is empty";
			return;
		}
		node<T>* v = search(value);

		if (v->value != value) {
			cout << "No node found to delete with value:" << value << endl;
			return;
		}
		removeNode(v);
	}

	void preorder(node<T> *temp) {
		if (temp == nullptr) {
			return;
		}
		cout << temp->value << " ";
		preorder(temp->left);
		preorder(temp->right);
	}

	void inorder(node<T> *temp) {
		if (temp == nullptr) {
			return;
		}
		inorder(temp->left);
		cout << temp->value << " ";
		inorder(temp->right);
	}

	void postorder(node<T> *temp) {
		if (temp == nullptr) {
			return;
		}
		postorder(temp->left);
		postorder(temp->right);
		cout << temp->value << " ";
	}

	void levelorder(node<T> *root) {
		node<T>* temp = nullptr;
		queue_space::queue<node<T>*>* queue = new queue_space::queue<node<T>*>;
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
	red_black_tree<int> tree = red_black_tree<int>();

	node<int>* root;
	int choice = -1, input = -1;
	bool check_out = false;

	while (1) {
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
				tree.remove(input);
				cout << "삭제 완료";
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