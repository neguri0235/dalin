#include <iostream>

using namespace std;

class Rect {
public:
	int x = 0, y = 0, w = 10, h = 10;
public:
	int setY(int a) { y = a; }
	int getArea()  const {  // 상수 멤버 함수!! . 
		//w = 20;  // error  . 상수 멤버 함수이기 때문에 읽기만 가능
		return w * h;
	}
};

//void foo(Rect r) {
void foo(const Rect& r) {   // 복사상의 오버헤드를 줄이기 위해 const &로 전달하게 되는데,
													//  getArea( ) const { 가 되어야 함.
													// 즉 const refence 를 보내려면, 멤버 함수가 상수 멤버 함수여야 함.
	int n = r.getArea();
}

int main()
{
	 Rect r;	// 생성자로 초기화
	foo(r);
}