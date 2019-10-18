#include <iostream>

template<typename T> class Test {
public:
	void foo(T&& arg) {}

	template<typename U> void goo(U&& arg) {}
};

int main()
{
	int n = 0;

	Test<int> t; //  이 순간 T의 타입이 결정됨. int

	t.foo(n); // error .forwarding reference가 되려면, 호출하는 순간 타입이 결정되어야 함. 
					// 하지만 지금은 호출하기 이전에 T가int로 타입이 결정되어 있음
					// Test 가 class template이고  foo( )는 함수가 템플릿이 아님. 
					//&&가 모든 타입을 다 받으려면, 빌드 시점이 아니라 실행 시점에 값이 전달 되어야 함.
	t.foo(10);

	t.goo(n);  // goo는 함수가 템플릿 임.  goo는 & 와 && 두개의 함수가 생성됨
	t.goo(10);
}