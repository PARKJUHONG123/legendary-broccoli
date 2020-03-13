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
class binary_tree {
private:
	node<T>* root;
public:
	binary_tree() : root(nullptr) {

	}
	~binary_tree() {
		if (root != nullptr) deleteTree(root);
		cout << "트리 삭제" << endl;
	}

	void deleteTree(node<T>* root) {
		if (root->left != nullptr) deleteTree(root->left);
		if (root->right != nullptr) deleteTree(root->right);
		delete []root;
		return;
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
					cout << "중복된 값 발견 : " << index->value << " = " << temp->value << endl;
					delete[]temp;
					break;
				}
			}
		}
	}

	node<T>* search(node<T>* root) {
		if (root == nullptr) {
			return nullptr;
		}
		if (root->left == nullptr) { //자기 자신이 왼쪽 끝이라면
			return root;
		}
		else {
			return search(root->left); //더 왼쪽 끝이 있다면
		}
	}

	node<T>* remove(node<T>* root, node<T>* parent, T target) {
		node<T>* curr = nullptr;
		if (root == nullptr) {
			return nullptr;
		}
		
		if (root->value > target) { // 타겟보다 값이 크거나
			curr = remove(root->left, root, target);
		}
		else if (root->value < target) { // 타켓보다 값이 작거나
			curr = remove(root->right, root, target);
		}
		else { // 타겟일 경우
			curr = root;

			// 자식 노드 없음
			if (root->left == nullptr && root->right == nullptr) {
				// 똑 때버림
				if (parent->left == root) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
				delete[]root;
				cout << "no child node delete" << endl;
			}

			// 자식 노드 두개
			else if (root->left != nullptr && root->right != nullptr) {
				// 오른쪽 중에서 가장 왼쪽에 있는 값을 선택한다
				node<T>* min_node = search(root->right);
				min_node = remove(root, nullptr, min_node->value);
				root->value = min_node->value;
				delete[]min_node;
				cout << "two child node delete" << endl;
			}

			// 자식 노드 한개
			else {
				node<T>* temp = (root->left != nullptr) ? root->left : root->right;
				if (parent == nullptr) {
					root->left = temp->left;
					root->right = temp->right;
					root->value = temp->value;
					delete[]temp;
				}
				else {
					if (parent->left == root) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
					delete[]root;
				}
				cout << "one child node delete" << endl;
			}
		}
		return curr;
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


/*
1. Root Property : Root 노드의 색깔은 검정이다
2. External Property : Leaf 노드의 색깔은 검정이다
3. Internal Property : Red 노드의 자식은 검정이다
4. Depth Property : 모든 Leaf 노드에서 Black depth 는 같다
*/

template <typename T>
class red_black_tree {
private:
	node<T>* root;
public:
	red_black_tree() {
		root = nullptr;
	}

	node<T>* getRoot() {
		return root;
	}

	void add(T value) {
		node<T>* v = root;
		node<T>* wv_parent = nullptr;
		node<T>* w = nullptr;
		node<T>* z = new node<T>;
		z->value = value;
		z->color = RED;

		while (1) {
			if (v == nullptr) {
				z->color = BLACK;
				root = z;
				break;
			}
			else {
				if (v->value > z->value) {
					if (v->left == nullptr) { // 집어넣기

						if (wv_parent != nullptr) {
							if (wv_parent->left == v) {
								w = wv_parent->right;
								if (w == nullptr || w->color == BLACK) {
									restructing(z, v, wv_parent);
								}
								else {
									recoloring(w, z, v, wv_parent);
								}
							}
							else {
								w = wv_parent->left;
								if (w == nullptr || w->color == BLACK) {
									restructing(z, v, wv_parent);
								}
								else {
									recoloring(w, z, v, wv_parent);
								}
							}
						}
						v->left = z;
						break;
					}
					else {
						wv_parent = v;
						v = v->left;
					}
				}
				else if (v->value < z->value) {
					if (v->right == nullptr) { // 집어넣기

						if (wv_parent != nullptr) {
							if (wv_parent->left == v) {
								w = wv_parent->right;
								if (w == nullptr || w->color == BLACK) {
									restructing(z, v, wv_parent);
								}
								else {
									recoloring(w, z, v, wv_parent);
								}
							}
							else {
								w = wv_parent->left;
								if (w == nullptr || w->color == BLACK) {
									restructing(z, v, wv_parent);
								}
								else {
									recoloring(w, z, v, wv_parent);
								}
							}
						}

						v->right = z;
						break;
					}
					else {
						wv_parent = v;
						v = v->right;
					}
				}
				else {
					cout << "중복된 값 발견 : " << v->value << " = " << z->value << endl;
					delete[]z;
					break;
				}
			}
		}
	}

	void restructing(node<T>* z, node<T>* v, node<T>* wv_parent) {
		node<T> *left = nullptr, *right = nullptr, *parent = nullptr;
		node<T>* wv = new node<T>;

		wv->color = wv_parent->color;
		wv->left = wv_parent->left;
		wv->right = wv_parent->right;
		wv->value = wv_parent->value;

		if (z->value < v->value && v->value < wv->value) {
			left = z;
			parent = v;
			right = wv;
		}
		else if (z->value < wv->value && wv->value < v->value) {
			left = z;
			parent = wv;
			right = v;
		}
		else if (v->value < z->value && z->value < wv->value) {
			left = v;
			parent = z;
			right = wv;
		}
		else if (v->value < wv->value && wv->value < z->value) {
			left = v;
			parent = wv;
			right = z;
		}
		else if (wv->value < z->value && z->value < v->value) {
			left = wv;
			parent = z;
			right = v;
		}
		else  { // if (wv->value < v->value && v->value < z->value)
			left = wv;
			parent = v;
			right = z;
		}


		if (wv->left == v) {
			left->left = nullptr;
			right->right = wv->right;
		}
		else {
			left->left = wv->left;
			right->right = nullptr;
		}
		left->right = nullptr;
		right->left = nullptr;

		left->color = RED;
		right->color = RED;
		parent->color = BLACK;

		parent->left = left;
		parent->right = right;

		wv_parent->color = parent->color;
		wv_parent->left = parent->left;
		wv_parent->right = parent->right;
		wv_parent->value = parent->value;
		delete[]parent;
	}

	void recoloring(node<T>* w, node<T>* z, node<T>* v, node<T>* wv_parent) {
		w->color = BLACK;
		v->color = BLACK;
		wv_parent->color = RED;

		if (wv_parent != root) {
			if (w->color == RED) {
				recoloring(w, z, v, wv_parent);
			}
			else {
				restructing(z, v, wv_parent);
			}
		}
		else {
			wv_parent->color = BLACK;
		}
	}

	node<T>* remove(node<T>* root, node<T>* parent, T target) {
		node<T>* curr = nullptr;
		if (root == nullptr) {
			return nullptr;
		}

		if (root->value > target) { // 타겟보다 값이 크거나
			curr = remove(root->left, root, target);
		}
		else if (root->value < target) { // 타켓보다 값이 작거나
			curr = remove(root->right, root, target);
		}
		else { // 타겟일 경우
			curr = root;

			// 자식 노드 없음
			if (root->left == nullptr && root->right == nullptr) {
				// 똑 때버림
				if (parent->left == root) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
				delete[]root;
				cout << "no child node delete" << endl;
			}

			// 자식 노드 두개
			else if (root->left != nullptr && root->right != nullptr) {
				// 오른쪽 중에서 가장 왼쪽에 있는 값을 선택한다
				node<T>* min_node = search(root->right);
				min_node = remove(root, nullptr, min_node->value);
				root->value = min_node->value;
				delete[]min_node;
				cout << "two child node delete" << endl;
			}

			// 자식 노드 한개
			else {
				node<T>* temp = (root->left != nullptr) ? root->left : root->right;
				if (parent == nullptr) {
					root->left = temp->left;
					root->right = temp->right;
					root->value = temp->value;
					delete[]temp;
				}
				else {
					if (parent->left == root) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
					delete[]root;
				}
				cout << "one child node delete" << endl;
			}
		}
		return curr;
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
/*
int main() {
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
				tree.remove(root, nullptr, input);
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
*/

int main() {
	red_black_tree<int> tree = red_black_tree<int>();
	tree.add(1);
	tree.add(2);
	tree.add(3);
	tree.add(4);
	tree.add(5);

	tree.preorder(tree.getRoot());
	cout << endl;
	tree.inorder(tree.getRoot());
	cout << endl;
	tree.postorder(tree.getRoot());
	cout << endl;
	tree.levelorder(tree.getRoot());
	cout << endl;

	return 0;
}
