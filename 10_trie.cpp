#include <cstdio>
#include <iostream>
#include <String>
#include <stack>

using namespace std;

const int ALPHA_SIZE = 26;

struct node {
	node* child[ALPHA_SIZE];
	bool endWord = false;
};

class trie {
private:
	node* root = nullptr;
	stack<int> s, t, r;

public:
	trie() : root(nullptr){

	}

	~trie() {
		cout << "DELETE TRIE" << endl;
		deleteTrie(root);
	}

	node* getRoot() {
		return root;
	}

	void add(string key) {
		if (root == nullptr) {
			root = new node;
			memset(root->child, NULL, sizeof(node*) * ALPHA_SIZE);
		}

		node* temp = root;
		node* new_node = nullptr;
		int index;

		for (int i = 0; i < key.length(); i++) {
			index = key[i] - 'a';
			if (temp->child[index] == NULL) {
				new_node = new node;
				memset(new_node, NULL, sizeof(node*) * ALPHA_SIZE);
				temp->child[index] = new_node;
			}
			temp = temp->child[index];
		}
		temp->endWord = true;
	}

	bool find(string input) {
		node* temp = root;
		if (temp == nullptr) {
			return false;
		}

		if (temp->endWord == true) {
			return true;
		}
		else {
			for (int i = 0; i < input.size(); i++) {
				if (temp->child[input[i] - 'a'] != NULL) {
					temp = temp->child[input[i] - 'a'];
				}
				else{
					return false;
				}
			}
		}
	}

	void print(node* temp) {
		int temp_top;
		for (int i = 0; i < ALPHA_SIZE; i++) {
			
			if (temp->child[i] != NULL) {
				s.push(i);

				print(temp->child[i]);

				while (s.empty() == false) {
					if (i != s.top()) {
						t.push(s.top());
					}
					r.push(s.top());
					s.pop();
				}

				if (temp->child[i]->endWord == true) {
					cout << "result : ";
					while (r.empty() == false) {
						cout << char('a' + r.top());
						r.pop();
					}
					cout << endl;
				}
				else {
					while (r.empty() == false) {
						r.pop();
					}
				}

				while (t.empty() == false) {
					s.push(t.top());
					t.pop();
				}
			}
		}
	}


	void deleteTrie(node* temp) {
		if (temp != nullptr) {
			for (int i = 0; i < ALPHA_SIZE; i++) {
				if (temp->child[i] != NULL) {
					deleteTrie(temp->child[i]);
					delete[]temp->child[i];
					temp->child[i] = NULL;
				}
			}
		}
	}
};

int main() {
	trie* Trie = new trie();
	bool check_out = true;
	int choice = -1;
	string input = "";

	while (check_out) {
		cout << "1.삽입 2.검색 3.출력 4.종료" << endl;
		cin >> choice;
		// 1 abk 1 abt 1 ac 1 spq 1 f
		switch (choice) {
		case 1:
			cin >> input;
			Trie->add(input);
			break;

		case 2:
			cin >> input;
			cout << ((Trie->find(input)) ? "YES" : "NO") << endl;
			break;

		case 3:
			Trie->print(Trie->getRoot());
			break;

		case 4:
			check_out = false;
			delete Trie;
			break;
		}
	}

	return 0;
}