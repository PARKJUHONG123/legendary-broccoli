#include <cstdio>
#include <iostream>
using namespace std;

namespace self_made {
	class arrays {
	private:
		int size;
		int* arr;

	public:
		void setSize(int num) {
			this->size = num;
		}
		int getSize() {
			return this->size;
		}

	};
}

int main() {
	self_made::arrays array_class;
	array_class.setSize(5);
	cout << array_class.getSize();

	return 0;
}