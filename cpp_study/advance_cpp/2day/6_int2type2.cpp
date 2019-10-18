#include <iostream>
#include <type_traits>
using namespace std;
/*
template<typename T> void printv(T v)
{
	if (std::is_pointer<T>::value) {
		cout << v << " : " << *v << endl;
	}
	else {
		cout << v << endl;
	}
}
*/

template<typename T> void printv(T v)
{
	if (std::is_pointer<T>::value) {
		cout << v << " : " << *v << endl;
	}
	else {
		cout << v << endl;
	}
}

/*
이렇게 컴파일러가 만드는데, int에 대해서 *v를 할수 없음. 빌드 에러. 
이를 해결해야 함.
3가지 방법이 있음 (첫번째는 c++17에 있는 if constexpr)
void printv(int v)
{
	if (false) {
		cout << v << " : " << *v << endl;
	}
	else {
		cout << v << endl;
	}
}
*/

int main()
{
	int n = 10;

	//printv(n);
	printv(&n);
}