#include <iostream>
#include <type_traits>
using namespace std;

// 이렇게 만들어도 빌드 에러가 발생함.
// 컴파일러는 printv_pointer( ) 사용할지 안할지 모름

template<typename T> void printv_pointer(T v)
{
	cout << v << " : " << *v << endl;
}

template<typename T> void printv_not_pointer(T v)
{
	cout << v << endl;
}

template<typename T> void printv(T v)
{
	if (std::is_pointer<T>::value) {
		printv_pointer(v);
	}
	else {
		printv_not_pointer(v);
	}
}

int main()
{
	int n = 10;

	printv(n);
	printv(&n);
}