#include <iostream>
using namespace std;


template<typename T> struct xis_reference {
	static constexpr bool value = false;
};

template<typename T> struct xis_reference <T&> {
	static constexpr bool value = true;
};

template<typename T> struct xis_reference <T&&>{
	static constexpr bool value = false;
};

/*
int main()
{
	cout << xis_reference<int>::value << endl;		// false
	cout << xis_reference<int&>::value << endl;	// true
}
*/
//그런데 복잡해서 보기 안좋음

template<typename T> 
bool xis_reference_v = xis_reference<T>::value;

int main()
{
	cout << xis_reference<int>::value << endl;		// false
	cout << xis_reference<int&>::value << endl;	// true
	cout << xis_reference_v<int&><< endl;	// true
}


//----------------------------
// Template은 4가지 종류가 있음.
template<typename T> class list {};						// 클래스 템플릿
template<typename T> void foo(T a) {} ;	// 함수 템플릿
template<typename T> using List = list<T>; // using 템플릿
template<typename T> bool v = xis_reference<T>::value // variable template (변수 템플릿)
//v<int> // == xis_pointer<int>::value 와 같은 의미
