#include <iostream>

using namespace std;


// template 은 두번 컴파일 한다.
// 1. T와 관련 없는 부부의 오류를 조사한다.
//		T와 관련이 있는 코드는 조사하지 않는다.

// 2. 실제 사용하면 T 타입이 결정되고, 실제 함수(클래스)의 코드가 생성
//		생성된 함수를 다시 컴파일(오류조사)한다.
//		참고: c++ template guide 2nd edition

template <typename T> void foo(T a)
{
	*a = 10;
	goo(a);  // 오류 아님
	goo();	// 오류 
}

int main()
{
	
}