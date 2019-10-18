#include <iostream>

using namespace std;

class Base {
public:
	Base() { cout << "Base()" << endl; }

	// derived 에만 virtual 적는 것은 의미 없음.
	// 그렇게 하면 Base에 가서 소멸자를 부름.
	virtual  ~Base() { cout << "~Base()" << endl; }
};

class Derived : public Base{
public:
	Derived() { cout << "Derived()" << endl; }
	 ~Derived() { cout << "~Derived()" << endl; }
};

int main()
{
	Base* p = new Derived;
	delete p;
}