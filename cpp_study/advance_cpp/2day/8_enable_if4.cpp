#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
typename enable_if<is_integral<T>::value, void> ::type
 foo(T a) {
	cout << "T" << endl;
}

void foo(...) { cout << "..." << endl; }

int main()
{
	// 정수 일때만 T, 정수가 아니면 ... 를 출력
	foo(10);
	foo(3.4);
	foo(3.4f);
}