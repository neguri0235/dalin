#include <iostream>
#include <type_traits>

using namespace std;

template<typename T> void foo(T a) {
	// T의 포인터 여부에 따라 다른 일 하기
	if (is_pointer<T>::value) {

		// *a = 10; 과 같은 역 참조하는 소스는 사용할 수 없음
		// 1. *a = 10 과 같은 소스를 사용하려면, if constexpr 사용
		// 2. true_type, false_type으로 오버로딩
	}
	else {

	}

	if constexpr (is_pointer<T>::value) {
		*a = 10;
	}

	foo_imp(a, is_pointer<T>());
}

template<typename T> void foo_imp(T a, true_type) {}
template<typename T> void foo_imp(T a, false_type) {}

// 3. 함수 템플릿을 2개 만들고 enable_if 로 조건에 따라 사용하도록 함.
template<typename T>
typename enable_if<is_pointer<T>::value>::type foo(T a) {}

template<typename T>
typename enable_if<!is_pointer<T>::value>::type foo(T a) {}

// 기술이 나온 순서는 true_type/false_type -> enable_if -> if const_expr

int main()
{

}