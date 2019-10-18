#include <iostream>

using namespace std;

// C++의 4개 캐스팅
// reinterpret_cast
// 1. 서로 다른 타입의 주소를 캐스팅
// 2. 정수 <-> 포인터 캐스팅
// 3. 서로 다른 타입을 참조 형식으로 캐스팅
int main()
{
	double  d = 3.4;
	int*		p1 = (int*)&d;											// ok. 하지만 실수 인지, 의도인지 알 수 없음.
	//int*		p2 = static_cast<int*>(&d);					// double과 int는 연관이 없어서 casting 불가. 
	int*		p3 = reinterpret_cast<int*>(&d);		// ok, casting 하는 의도를 확인 가능

	//int*		p4 = 10;							// c에서는 되지만, c++에서 안됨
	int*		p5 = (int*) 10;				//   c++에서 이렇게 강제로
	//int*		p6 = static_cast<int*> (10);				// error 발생
	int*		p7=  reinterpret_cast<int*> (10);	// ok


}