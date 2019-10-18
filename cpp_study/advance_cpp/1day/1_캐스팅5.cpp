#include <iostream>

using namespace std;
/*
int main()
{
	const int c = 10;

	// int* p1 = &c;   error
	int* p1 = (int*)&c;
	//int* p1 = static_cast<int*>(&c);   //error
	//int* p1 = reinterpret_cast<int*>(&c);   //error
	int* p2 = const_cast<int*>(&c);   // 동일 타입의 const 속성을 제거

	volatile int n = 10;   // volatile : 최적화 하지 말것
	//int* p3 = &n;
	volatile int* p3 = &n;
	int* p2 = const_cast<int*>(&n);
}
*/

int main()
{
	// c의 주소를 p에 담으려고 할때,
	const int c = 10;
	// char* p = &c; // error
	// char* p = static_cast<char*>(&c);  //error
	//char* p1 = reinterpret_cast<char*>(&c);   // const 제거가 안되어서 에러
	char* p2 = reinterpret_cast<char*>(const_cast<int*>(&c));   //  한번의 캐스트를 하지 않고, 두번의 캐스팅을 해야함.
}
