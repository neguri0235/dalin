#include <iostream>

using namespace std;

int main()
{
	// 레퍼런스 규칙
	// 1. non const lvalue reference는 lvalue만 가리킨다
	int n = 0;
	int& r1 = n;					// 0k
	int& r2 = 10;				// error

	// 2. const reference는 lvalue 와 rvalue 모두 가리킨다
	// 단점 : rvalue가 항상 const 인 것은 아니다 . Point(0, 0)란 임시 객체를 생성한 경우
	const int& r3 = n;			//ok
	const int& r4 = 10;		// ok
	//ARM(annotated reference manual)에 나온 내용

   // 3. C++11 . const 없이 rvalue 가리키는 참조가 필요했다.
	// rvalue reference는 rvalue만 가르킬 수 있다.
	int&& r5 = n;			// error 
	int&& r6 = 10;		// ok
}