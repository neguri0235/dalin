#include <iostream>

using namespace std;

class Car {
	int speed;
public:
	~Car() { cout << "car ctor" << endl; }
};

Car* p;

void foo() {
	Car* p1 = new Car;
	p = p1;
	delete p1;
}

int main()
{
	foo();
}
