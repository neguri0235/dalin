
#include <iostream>
using namespace std;

class Base {

public:
	void foo() {}
};

class Point : public Base {

	int x, y;
public:
	void set(int a, int b) { x = a, y = b; }   // void set(Point* this, int a, int b) 
	int getX() const { return x; }  // int getX(const Point* this) 로 변경되는 것임. 그래서 함수 내에서 값을 변경하면 에러남.
};

int main()
{
	Point p1, p2;
	p1.set(10, 20);		// set( ) 함수는 한개만 만들어 지므로, set(&p1, 10, 20) 으로 컴파일 됨
	p2.set(30, 40);		// set(&p2, 30,40)
	p1.getX();
}