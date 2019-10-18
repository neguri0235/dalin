//1_temporary.cpp

//https://github.com/WebKit/webkit/blob/master/Source/WTF/wtf/Scope.h
/*
	ScopeExit(const ScopeExit&) = delete;
	ScopeExit& operator=(const ScopeExit&) = delete;
	ScopeExit& operator=(ScopeExit&&) = delete;
*/

#include <iostream>

using namespace std;

class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {
		cout << "Point()" << endl;
	}
	~Point() { cout << "~Point()" << endl; }
	void set(int a, int b) { x = a;  y = b; }
	void print() { cout << x << ' ' << y << endl; }
};

// Temporary의 특징

int main()
{
	Point p(0, 0);
	p.x = 10;

	//Point(0, 0).x = 10;  // (1) 특징 1. temporary는 lvalue가 될 수 없다 ( = 의 왼쪽에 올 수 없음)
											// temporary는 상수 ? 상수는 아님
	Point(0, 0).set(10, 20); // (2) 상수가 아니기 때문에 가능. 이렇게 쓰는 이유는 vector에서 BitProxy와 같은 방법

	Point* p1 = &p;
	Point* p2 = &Point(0, 0);  //(3) tempory는 주소를 구할 수 없다. 다음줄에 넘어가면 객체가 없으므로

	// 특징 3
	Point& r1 = p;			// 이름이 있는 객체는 참조로 가르킬 수 있다.
	
	//Point& r2 = Point(0, 0);		// 이름이 없는 객체는 다음줄에서 없어지므로 참조로 가르킬 수 없다.
	
	const Point& r3 = Point(0, 10); // (4)  const 참조는 temporary를 가르킬 수 있음. 수명은 r3의 수명과 같다
																// temporary materialization 이라는 개념
	
	// 위 코드의 문제점 : temporary는 상수가 아닌데 상수 참조로만 가르킬 수 있다.
	// C++11에서 비상 수 참조로 가르키게 함
	Point&& r4 = Point(0, 0);
	r4.x = 10;

}