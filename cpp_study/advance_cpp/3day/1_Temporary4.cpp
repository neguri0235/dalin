//  Temporary와 함수 반환 타입
#include <iostream>

using namespace std;

//[1_Temporary4.cpp](1_Temporary4.cpp)
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


// 1. 함수 인자
// void foo(Point pt) {} // call by value : 복사본 객체를 생성
void foo(Point& pt) {} // call by reference  : 복사본  생성 안됨

Point pt(0, 0);
// 2. 함수 반환 타입
// 복사본의 객체가 반환됨. 리턴 객체는 타입만 있고 이름이 없음. (임시 객체)
// 그래서 goo().x = 10;  이 컴파일 에러 발생 (임시 객체에 값을 변경 할 수 없으므로)
Point goo() { return pt; }	

// 레펀스를 반환함.
Point& hoo() { return pt; }

Point& koo()
{
	Point p(0, 0);
	// !!! 절대 지역 변수의 참조를 반환하면 안됨
	return p;	
}

int main()
{
	Point p;
	foo(p);
	// 레퍼런스를 반환하는데, 반화하는 것에 이름이 없음. 
	// 하지만Global로 선언된 객체를 반환한 것이고 값을 유지하고 있음
	hoo().x = 10, hoo().print();
	pt.print();
}	