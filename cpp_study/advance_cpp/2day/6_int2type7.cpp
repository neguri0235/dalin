#include <iostream>
#include <type_traits>
using namespace std;

// int2type : int 형 상수를 독립된 타입으로 만드는 도구
/*
template<typename T, T  N> struct xintegral_constant {
		static constexpr T value = N;
};

// true, false	:  서로 같은 타입
// true_type, false_type : 서로 다른 타입

typedef xintegral_constant<bool, true > true_type;
typedef xintegral_constant<bool, false> false_type;


// is_pointer 등의 traits는 아래처럼 만든다 (표준에서)
template<typename T> struct is_pointer :  false_type {};
template<typename T> struct is_pointer<T*> : true_type {};

*/

template<int N> struct int2type {
	enum { value = N };
};

template<typename T> void printv_imp(T v, true_type) {
	cout << v << " : " << *v << endl;
}

template<typename T> void printv_imp(T v, false_type) {
	cout << v << endl;
}
template<typename T> void printv(T v) {
	printv_imp(v,  is_pointer<T>());
}
int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}