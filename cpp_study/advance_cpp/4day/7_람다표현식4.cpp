#include <iostream>
using namespace std;

void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}
void koo(int a, int b, int c) {}
void joo() {}

// C++11 가변인자 템플릿
// return 이있을 수도 있고, 없을 수도 있고. 그래서 decltype(aut0)를 붙여줌
template<typename F, typename ... T>
decltype(auto) chronometry(F&&  f, T&& ...arg) {
	return invoke(std::forward<F> (f),
								std::forward<T>(arg)...);
}

int main()
{ 
	hoo(1);
	chronometry(hoo, 10);
	chronometry(koo, 10, 20, 30);
	chronometry(joo);
}