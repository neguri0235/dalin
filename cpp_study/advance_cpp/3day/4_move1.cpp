#include <iostream>

using namespace std;

class Point {
	int x, y;
public:
	Point(int a = 0, int b = 0) : x(a), y(b) {}
	
	// 1. 복사 생성자 모양 1. call by value
	// 이렇게 만들 수 없음. 재귀적으로 무한히 복사하게 됨
	// 인자가 넘어갈때 복사가 되고, 다시 복사 생성자 불리고, 다시 복사 , 다시 복사 생성자..무한 반복
	//Point(Point pt) {}

	// 2. 복사 생성자 모양 1. call by reference
	// 사용 가능. 에러 없음
	// 단점: rvalue를 받을 수 없다.
	// 값을 반환하는 함수의 반환값을 받을 수 없다. 
	Point(Point&) {}

	// 3. 복사 생성자 모양  call by const lvalue reference
	// lvalue 뿐 아니라 rvalue 모두 받을 수 있다.
	Point(const Point& pt) : x(pt.x), y(pt.y) {}
};

Point foo() {
	Point p;
	return p;
}

int main()
{
	Point p1;					// 디폴트 생성자 (인자없는 default 값으로 생성)
	Point p2(1, 2);		// 인자 2개인 생성자
	Point p3(p2);			// Point(Point)의 생성자 필요
	Point p4(Point(0,0));			// Point(Point)의 생성자 필요

	Point ret = foo();	// foo에서 리턴되는 값은 임시 객체, rvalue. 2번 복사 생성자로는 이 코드를 처리 못함.
}