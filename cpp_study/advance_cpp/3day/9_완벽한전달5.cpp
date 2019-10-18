#include <iostream>

using namespace std;

void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}
// 완벽히 전달하려면
// 1. 인자는 복사본이 생성되면 안된다 - 참조
// 2. const를 붙여도 안된다.
// 3. int& 와 int&& 버전의 함수를 2개 제공한다.
// const int&, const volatime int& 도 만들어야 한다.

// => 아래 두 코드는 perfect forwarding 을 거의 비슷하게 구현한것. 

template<typename F> void chronometry(F f, int & arg) {
	f(arg);
}


// main -						chronometry -					hoo(int&&)
// 10(rvalue) 전달 -> int&& arg (lvalue)  ->		다시 rvalue로 석성 변경
template<typename F> void chronometry(F f, int&& arg) {
	// int&& arg = 10;
	// 10 : rvalue, arg: lvalue	
	//f(arg);
	f(static_cast<int&&>(arg));
}


int main()
{
	int n = 10;
	hoo(10);
	chronometry(hoo, n);
	chronometry(hoo, 10);
}