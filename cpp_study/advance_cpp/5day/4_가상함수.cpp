#include <iostream>
using namespace std;

class Shape {
public:
	
	void foo() { cout << "foo" << endl; }
	virtual void Draw() { cout << "Shape" << endl; }
};

class Rect : public Shape {
public:
	virtual void Draw() { cout << "Rect" << endl; }
};

int main() {
	void (Shape::*f1)() = &Shape::foo;
	void (Shape::*f2)() = &Shape::Draw;
	// f2에는 뭐가 들어 있나?
	// 함수 주소가 아닌, 가상함수 테이블에 대한 index 정보

	Rect r;
	(r.*f2)();
	(((Shape&)r).*f2)();
}