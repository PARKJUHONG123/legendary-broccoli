#include <cstdio>
#include <iostream>

#define RED 0
#define BLACK 1

using namespace std;

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

template <typename T>
class red_black_tree {
private:

public:

};

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