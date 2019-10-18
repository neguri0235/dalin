#include <iostream>
using namespace std;

void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}

// 결론
// 1. int&, int&& 로 2개를 만들어야 한다
// 2. int&& 버전에서 다른 함수로 전달할때 rvalue로 캐스팅해서 전달
/*
template<typename F> void chronometry(F f, int & arg) {
	//f(arg);
	f(static_cat<int&>(arg)); // 필요 없는 캐스팅, 있어도 문제 되지 않음.
}

template<typename F> void chronometry(F f, int&& arg) {
	f(static_cast<int&&>(arg));
}
*/

// n (lvalue) 전달 => T: int& t&& :int&
// 10(rvalue) 전달 => T: int, T&& : int&&
// 즉, 아래 템플릿은 2번째 인자가 n 인지 10인지에 따라 위의 2개 함수 생성
template<typename F, typename T> void chronometry(F f, T&& arg) {
	
	// 아래 캐스팅은 ?
	// 2번째 인자에 따라서 다른 캐스팅이 됨

	// 2번째 인자가 10(rvalue)를 보내면 rvalue로 캐스팅
	// 2번째 인자로 n(lvalue)를 보내면 lvalue로 캐스팅
	//f(static_cast<T&&>(arg)); 

	//위 기능을 해주는 함수가 있음
	f(std::forward<T>(arg));
}

int main()
{
	int n = 10;
	//hoo(10);
	chronometry(hoo, 10);
	chronometry(goo, n);
}