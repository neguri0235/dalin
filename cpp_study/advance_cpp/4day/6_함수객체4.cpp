#include <iostream>
#include <bitset>
using namespace std;

			int Add1(int a, int b)	{ return a + b; }
inline int Add2(int a, int b)	{ return a + b; }
inline int Sub(int a, int b)		{ return a - b; }

// 1. 인라인 함수는 컴파일 시간에 이루어지는 문법이다.
// 2. 인라인 함수라도 함수 포인터에 담아서 호출하면 치환될 수 없다.

void foo(int(*f)(int, int))  // 어떤 함수가 오는지 알 수 없다.
{
	int n = f(1, 2);
}

int main()
{
	Add1(1, 2);			//	호출
	Add2(1, 2);			// 치환. 빠르다

	foo(Add2);			// 호출
	int(*f)(int, int) = &Add2;
	f(1, 2);


}