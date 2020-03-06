#include <iostream>
#include <cstring>

using namespace std;

namespace ObjectControl {
	class Employee {
	private:
		char name[100];
	public:
		Employee(const char* name) {
			cout << "name: " << name << " constructor : Employee" << endl;
			strcpy_s(this->name, strlen(name) + 1, name);
		}

		void ShowYourName() const {
			cout << "name: " << this->name << endl;
		}

		virtual int GetPay() const = 0;
		virtual void ShowSalaryInfo() const = 0;

		virtual ~Employee() {
			cout << "destructor : Employee" << endl;
		}
	};

	class PermanentWorker : public Employee {
	private:
		int salary;

	public:
		PermanentWorker(const char* name, int money) : Employee(name), salary(money) {
			cout << "name: " << name << " constructor : PermanentWorker" << endl;
		}

		int GetPay() const {
			return salary;
		}

		void ShowSalaryInfo() const {
			ShowYourName();
			cout << "salary: " << GetPay() << endl << endl;
		}

		virtual ~PermanentWorker() {
			cout << "destructor : PermanentWorker" << endl;
		}
	};


	class TemporaryWorker : public Employee {
	private:
		int workTime;
		int payPerHour;

	public:
		TemporaryWorker(const char* name, int pay) : Employee(name), workTime(0), payPerHour(pay) {
			cout << "name: " << name << " constructor : TemporaryWorker" << endl;
		}

		void AddWorkTime(int time) {
			this->workTime += time;
		}

		int GetPay() const {
			return this->workTime * this->payPerHour;
		}

		void ShowSalaryInfo() const {
			ShowYourName();
			cout << "salary: " << GetPay() << endl << endl;
		}

		virtual ~TemporaryWorker() {
			cout << "destructor : TemporaryWorker" << endl;
		}
	};

	class SalesWorker : public PermanentWorker {
	private:
		int salesResult;
		double bonusRatio;

	public:
		SalesWorker(const char* name, int pay, double ratio) : PermanentWorker(name, pay), salesResult(0), bonusRatio(ratio) {
			cout << "name: " << name << " constructor : SalesWorker" << endl;
		}

		void AddSalesResult(int value) {
			salesResult += value;
		}

		int GetPay() const {
			return PermanentWorker::GetPay() + (int)(salesResult * bonusRatio);
		}

		void showSalaryInfo() const {
			ShowYourName();
			cout << "salary: " << GetPay() << endl << endl;
		}

		virtual ~SalesWorker() {
			cout << "destructor : SalesWorker" << endl;
		}
	};

	class EmployeeHandler {
	private:
		Employee* empList[50];
		int empNum;

	public:
		EmployeeHandler() : empNum(0) {
			cout << "constructor : EmployeeHandler" << endl;
		}

		void AddEmployee(Employee* emp) {
			empList[empNum++] = emp;
		}

		void ShowAllSalaryInfo() const {
			for (int i = 0; i < empNum; i++) {
				empList[i]->ShowSalaryInfo();
			}
		}

		void ShowTotalSalary() const {
			int sum = 0;
			for (int i = 0; i < empNum; i++) {
				sum += empList[i]->GetPay();
			}

			cout << "salary sum: " << sum << endl;
		}

		virtual ~EmployeeHandler() {
			cout << "destructor : EmployeeHandler" << endl;

			for (int i = 0; i < empNum; i++) {
				cout << "delete EmployeeHandler : " << i << endl;
				delete empList[i];
			}
		}
	};

	int main() {
		EmployeeHandler handler;

		// ������ ���
		handler.AddEmployee(new PermanentWorker("A", 1000));
		handler.AddEmployee(new PermanentWorker("B", 2000));

		// �ӽ��� ���
		TemporaryWorker* alba = new TemporaryWorker("C", 700);
		alba->AddWorkTime(5);
		handler.AddEmployee(alba);

		// ������ ���
		SalesWorker* seller = new SalesWorker("D", 1000, 0.1);
		seller->AddSalesResult(7000);
		handler.AddEmployee(seller);

		PermanentWorker* seller_permanent = new SalesWorker("E", 3000, 0.2);
		seller_permanent->ShowSalaryInfo();
		delete seller_permanent;
		seller_permanent = new PermanentWorker("F", 4000);
		seller_permanent->ShowSalaryInfo();
		delete seller_permanent;

		// �̹� �޿� �����ؾ� �� �޿��� ����
		handler.ShowAllSalaryInfo();

		// �̹� �޿� �����ؾ� �� �޿��� ����
		handler.ShowTotalSalary();

		return 0;
	}
}


namespace OperatorControl {
	namespace mystd {
		using namespace std;
		class ostream {
		public:
			ostream& operator<< (const char* str) {
				printf("%s", str);
				return *this;
			}

			ostream& operator<< (char str) {
				printf("%c", str);
				return *this;
			}
			ostream& operator << (ostream& (*fp)(ostream& ostm)) {
				return fp(*this);
			}
		};
		ostream& endl(ostream& ostm) {
			ostm << '\n';
			fflush(stdout);
			return ostm;
		}

		ostream cout2;
	}
	
	class Point {
	private:
		int xpos, ypos;

	public:
		Point(int x = 0, int y = 0) : xpos(x), ypos(y) {

		}

		void ShowPosition() const {
			cout << xpos << " " << ypos << endl;
		}

		friend Point operator+=(const Point pos1, const Point pos2);

		Point& operator++(){ //++pos 
							// ��ü �ڽ��� ������ �� �ִ� ���� ���� ��ȯ�ȴ�
							// ���࿡ Point ���� ����ȴٸ� ��ü �ڽ��� ���纻�� ���� ��ȯ�Ѵ�
							// ������ Point ������ ����Ǹ� �����ؼ� ++(++pos); �� �������� �� ���� ��ȭ�� ���� �ȴ�
			this->xpos += 1;
			this->ypos += 1;
			return *this;
		}

		const Point operator++(int) { //pos++
			//����� C++ ������ (pos++)++ �� (pos--)-- �� ������� ����
			const Point retobj(xpos, ypos); //retobj ��ü�� ���ȭ�ؼ� retobj ��ü�� ����� ���� ������ ������� �ʰڴ� (retobj �� ��ȯ�� ���� �ӽ� ��ü)
			xpos += 1;
			ypos += 1;
			return retobj; //�����ϱ� ���� ��ü�� ���� return �����μ� �������� �����ϰ�
		}

		friend Point& operator--(Point& ref); //--pos
		friend const Point operator--(Point& ref, int); //pos--


		Point operator*(int times) { // ref * 3
			Point pos(xpos * times, ypos * times);
			return pos;
		}
		friend Point operator*(int times, Point& ref); // 3 * ref
	};

	//Point& ref �� ������ ������ �� ������ ������ ���Ա� ������ �� �ܿ��� ��� ������
	Point& operator--(Point& ref) { //--pos
		ref.xpos -= 1;
		ref.ypos -= 1;
		return ref;
	}

	const Point operator--(Point& ref, int) { //pos--
		const Point retobj(ref);
		ref.xpos -= 1;
		ref.ypos -= 1;
		return retobj;
	}

	Point operator+=(const Point pos1, const Point pos2) {
		Point pos(pos1.xpos - pos2.xpos, pos1.ypos - pos2.ypos);
		return pos;
	}

	Point operator*(int times, Point& ref) {
		return ref * times;
	}

	int main(void) {
		Point pos1(3, 4);
		Point pos2(10, 20);
		Point pos3 = (pos1 += pos2);
		Point pos4(3, 5);
		Point pos5(3, 5);

		pos1.ShowPosition();
		pos2.ShowPosition();
		pos3.ShowPosition();
		cout << endl;

		--(--pos4);
		pos4.ShowPosition();
		++(++pos4);
		pos4.ShowPosition();

		Point cpy = 3 * pos5 * 2;
		cpy.ShowPosition();
		return 0;
	}
}

namespace ReferenceControl {
	class temp_class {
	private:

	public:
		void func() {
			int a = 10;
			int* b = &a;
			int& c = a;

			cout << "int a = 10�� ��\n" << "a = " << a << "\n*a = " << "����" << "\n&a = " << &a << endl;
			cout << "\nint* b = &a�� ��\n" << "b = " << b << "\n*b = " << *b << "\n&b = " << &b << endl;
			cout << "\nint& c = a�� ��\n" << "c = " << c << "\n*c = " << "����" << "\n&c = " << &c << endl;

			// &c = a �� �ϴ� ���� �ᱹ �Ѹ��� ���� �ϰڴٴ� �ǹ� : c �� a ���� ���� ���
			// int*b = &a ��, b* �� a�� ���� ��Ÿ����, b �� a �� �ּҸ� ��Ÿ����, &b �� b �ڱ� �ڽ��� ������ ��Ÿ���� �ּҸ� �ǹ��Ѵ�
		}
	};
}



int main() {
	using OperatorControl::mystd::cout2;
	using OperatorControl::mystd::endl;

	cout2 << "asd" << endl << 'a' << endl;
	return 0;
};
