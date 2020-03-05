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

		// 정규직 등록
		handler.AddEmployee(new PermanentWorker("A", 1000));
		handler.AddEmployee(new PermanentWorker("B", 2000));

		// 임시직 등록
		TemporaryWorker* alba = new TemporaryWorker("C", 700);
		alba->AddWorkTime(5);
		handler.AddEmployee(alba);

		// 영업직 등록
		SalesWorker* seller = new SalesWorker("D", 1000, 0.1);
		seller->AddSalesResult(7000);
		handler.AddEmployee(seller);

		PermanentWorker* seller_permanent = new SalesWorker("E", 3000, 0.2);
		seller_permanent->ShowSalaryInfo();
		delete seller_permanent;
		seller_permanent = new PermanentWorker("F", 4000);
		seller_permanent->ShowSalaryInfo();
		delete seller_permanent;

		// 이번 달에 지불해야 할 급여의 정보
		handler.ShowAllSalaryInfo();

		// 이번 달에 지불해야 할 급여의 총합
		handler.ShowTotalSalary();

		return 0;
	}
}


namespace OperatorControl {
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
	};

	Point operator+=(const Point pos1, const Point pos2) {
		Point pos(pos1.xpos - pos2.xpos, pos1.ypos - pos2.ypos);
		return pos;
	}

	int main(void) {
		Point pos1(3, 4);
		Point pos2(10, 20);
		Point pos3 = (pos1 += pos2);

		pos1.ShowPosition();
		pos2.ShowPosition();
		pos3.ShowPosition();
		return 0;
	}
}

namespace referenceControl {
	class temp_class {
	private:

	public:
		void func() {
			int a = 10;
			int* b = &a;
			int& c = a;

			cout << "int a = 10일 때\n" << "a = " << a << "\n*a = " << "오류" << "\n&a = " << &a << endl;
			cout << "\nint* b = &a일 때\n" << "b = " << b << "\n*b = " << *b << "\n&b = " << &b << endl;
			cout << "\nint& c = a일 때\n" << "c = " << c << "\n*c = " << "오류" << "\n&c = " << &c << endl;

			// &c = a 를 하는 것은 결국 뿌리를 같이 하겠다는 의미 : c 랑 a 랑은 같은 사람
			// int*b = &a 는, b* 은 a의 값을 나타내고, b 는 a 의 주소를 나타내고, &b 는 b 자기 자신의 공간을 나타내는 주소를 의미한다
		}
	};
}



int main() {
	referenceControl::temp_class ref;
	ref.func();
	return 0;
}