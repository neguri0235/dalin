#include <iostream>
#include <type_traits>

using namespace std;

template<typename T> void foo(T a)
{
	// type traits 기술의 종류

	// 1. 타입 질의 - T의 타입을 구할 수 있다.
	bool b1 = is_pointer<T>::value;     // C++11
	bool b2 = is_pointer_v<T>;				// C++ 14

	//2. 변경된 타입 얻기 - 포인터 이전의 타입을 구하기.
	//remove_pointer<T>::type n;  -> type이 값인지, type인지 모르니 typename을 적어야 함.
	typename remove_pointer<T>::type n;
	remove_pointer_t<T> n2;    //C++ 11
}

int main()
{

}