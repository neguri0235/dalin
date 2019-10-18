#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

void goo(int a, int b) { cout << "goo" << endl; }

template<typename T, typename... ARGS> 
void foo(T&& f, ARGS&& ... args) {
	f(std::forward<ARGS>(args)...);
}


int main()
{
	foo(goo,1,2);

	// 멤버 함수 포인터 만드는 방법
	//void(Test::*f)(int) = &Test::hoo; // 핵심 1

	// f(1,2); // error 객체가 없다

	Test test;
	// test.f(10); // error. f라는 멤버 함수가 없다.
}