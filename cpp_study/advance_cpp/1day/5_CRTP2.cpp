#include <iostream>

using namespace std;


class Car {
	static int cnt;
public:
	Car() { if (++cnt > 5) throw 1; }
	~Car() { --cnt; }
};

int Car::cnt = 0;

int main() {
	Car c1[5];
	Car c2;
}