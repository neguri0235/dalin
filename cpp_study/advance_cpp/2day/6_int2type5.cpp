#include <iostream>
#include <type_traits>
using namespace std;

template<int N> struct int2type {
	enum { value = N };
};

template<typename T> void printv_imp(T v, int2type<1>) {
	cout << v << " : " << *v << endl;
}

template<typename T> void printv_imp(T v, int2type<0>) {
	cout << v << endl;
}

template<typename T> void printv(T v){
	printv_imp(v,		int2type<is_pointer<T>::value>());
							// int2type<0> 만 하면 타입이 되므로, ( ) 를 붙여서 임시 객체를 만듬.
							// 함수로 전달되려면 type이 아니라 값이나 객체가 넘어가야 함.
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}

// 결국 변수를 타입으로 만들어서 사용함
// 숫자로 함수를 오버로딩 하게 됨.