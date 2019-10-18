#include <iostream>

using namespace std;

class Rect {
public:
	int x = 0, y = 0, w = 10, h = 10;
public:
	int setY(int a) { y = a; }
	//int getArea() {  // 상수 멤버 함수!! . 
	int getArea() const {  // 상수 멤버 함수!! . 
		//w = 20;  // error  . 상수 멤버 함수이기 때문에 읽기만 가능
		return w * h;
	}
};

int main( )
{
     const Rect r;	// 생성자로 초기화
	//r.x = 10;				// error. const 객체 이므로
	//r.setY(10);		// error. const 로 만든 객체가 변경되는 것이므로 에러

	r.getArea();  // getArea( ) 함수 뒤에 const가 없으면 빌드 에러 발생. 
}