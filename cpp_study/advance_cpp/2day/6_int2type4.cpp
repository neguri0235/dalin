#include <iostream>
#include <type_traits>
using namespace std;

// 이렇게 만들어도 빌드 에러가 발생함.
// 컴파일러는 printv_pointer( ) 사용할지 안할지 모름

template<typename T> void printv_imp(T v, YES)
{
	cout << v << " : " << *v << endl;
}

template<typename T> void printv_imp(T v, NO)
{
	cout << v << endl;
}

template<typename T> void printv(T v)
{
	// if 문에 의한 분기 : 실행 시간 분기 (컴파일 할때는 실행한다고 가정)
	/*
	if (std::is_pointer<T>::value) {
		printv_pointer(v);
	}
	else {
		printv_not_pointer(v);
	}
	*/

	// 함수 오버로딩에 의한 분기 : 컴파일 시간 분기
	printv_imp(v, ? );

}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}