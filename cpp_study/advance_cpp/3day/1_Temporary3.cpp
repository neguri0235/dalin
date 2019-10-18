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

// (3) 여기서 const 를 빼면 에러 발생. 임시 객체를 받기 위해서 const를 붙임
// (4) 혹시라도 foo( ) 내에서 객체를 변경 할 수도 있어서 const를 붙이기도 함.
void foo( const Point& p) {}  

int main()
{
	Point p(0, 0);
	// (1)  p는 foo( ) 함수에서만 필요함. 블록 전체에서 필요한게 아님
	foo(p);
	cout << "--------" << endl;
	// (2) 임시 객체로 보내면 foo( )함수에서만 사용. 
	// 함수 인자로만 사용하려면 임시 객체를 만들어서 전달하는 것이 좋음
	foo(Point(1, 2)); 
}