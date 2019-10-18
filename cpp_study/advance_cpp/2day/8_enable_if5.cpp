#include <iostream>
#include <type_traits>
using namespace std;
/*
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
	printv_imp(v, is_pointer<T>());
}
*/

// 사용자가 호출 했을 때 함수 3개를 만들지 않고, 
// 단지2개만 만들어서 사용
template<typename T> 
typename enable_if<is_pointer<T>::value, void>::type
printv(T v) {
	cout << v << " : " << *v << endl;
}

template<typename T>
typename enable_if<!is_pointer<T>::value, void>::type
printv(T v) {
	cout << v << endl;
}


int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}