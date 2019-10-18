#include <iostream>
#include <type_traits>
using namespace std;
// "Modern C++ Design" 에 나오는 기법

// int를 type으로 만드는 
template<int N> struct int2type {
	enum { value = N};
};

int main()
{
	foo(0);
	foo(1);

	// 0 과 1은 같은 타입(int), foo(0), foo(1)은 같은 함수 호출

	int2type<0> t0; 
	int2type<1> t1;

	foo(t0);
	foo(t1);
	// t0와  t1은 서로 다른 타입, foo(t0), foo(t1)서로 다른 함수를 호출
}