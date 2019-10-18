#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

// C++의 4개 캐스팅
// static_cast : 기본 캐스팅
//							1. 표준 타입을 값으로 캐스팅
//							2. void* => 다른 타입으로 변환 허용
//							3. 관련성이 없는 타입의 주소는 캐스팅 안됨.
// reinterpret_cast
// const_cast
// dynamic_cast

int main()
{
	double  d = 3.4;
	int			n = d; // double 이라서 data 손실이 있을 수 있음
	int			n_s = static_cast<int>(d);  // 표준 타입을 값으로 캐스팅 하는 것은 허용

//	int* p1 = malloc(100);  // C언어는 가능 void *가 다른 포인터로 암시적으로 형 변환됨
	                                             // C++ 는 안됨

	int* p2 = static_cast<int*> (malloc(100));  // C++에서는 이렇게 형 변환 하도록 함.

	//int* p3 = static_cast<int*> (&d); // double* -> int* 로 변환. 관련이 없는 type이기 때문에 안됨. 
																	 //  꼭 해야 한다면 ,reinterpret_cast를 사용해야 함

	// int&& 	r1 = n;
	int&& r1 = static_cast<int&& >(n);  // rvalue를 lvalue로 변경, 즉 속성을 변경하는 캐스팅
	int&		r2 = 10;
	int&		r2 = static_cast<int&> (10); // 에러. lvalue를 r value로 변경 불가

	// =>> 결론은 c++에서는 static_cast<> 를 사용하자.
}