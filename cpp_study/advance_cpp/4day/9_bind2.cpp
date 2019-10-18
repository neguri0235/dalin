#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

void foo(int a, int b, int c, int d) {
	printf("%d %d %d %d\n", a, b, c, d);
}

void goo(int) { cout << "goo" << endl; }

int main()
{
	// 일반 함수 포인터 단점
	// 1. 함수만 담는다. 함수 객체를 담을 수 없다. 
	// 2. 인자의 갯수가 다른 함수를 담을 수 없다. 
	void(*func)(int);


	// C++ : 함수 포인터 대신 function을 사용하자 C++11
	function<void(int)> f;   
	f = bind(&foo, 1, 2, 3, _1); // 호출은 아니고 f 라는 함수를 만든 것임.
	f(10);
	
	f = [](int a) { cout << "lambda" << endl; };
	f(10);

	// C++ GUI 라입러리 : nana (C++11/14를 활용한 라이브러리)

}