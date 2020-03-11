#include <cstdio>
#include <set>
#include <iostream>

using namespace std;

namespace stl_set {
	template <typename T>
	void show(set<T>& set_input) {
		cout << "[";
		for (typename std::set<T>::iterator itr = set_input.begin(); itr != set_input.end(); ++itr) {
			cout << *itr << " ";
		}
		cout << "]" << endl;
	}
}

int main() {
	using namespace stl_set;
	set<int> set_input;
	int choice = -1, input = -1;
	bool check_out = false;
	
	while(1){
		cout << "1.���� 2.�˻� 3.��� 4.���� 5.����" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cin >> input;
			set_input.insert(input);
			break;

		case 2:
			cin >> input;
			if (set_input.find(input) != set_input.end()) {
				cout << "�����Ѵ�" << endl;
			}
			else {
				cout << "�������� �ʴ´�" << endl;
			}
			break;

		case 3:
			show(set_input);
			break;

		case 4:
			cin >> input;
			set_input.erase(input);
			break;

		case 5:
			check_out = true;
			break;
		}
		cout << endl;
		if (check_out) break;
	}
	return 0;
}