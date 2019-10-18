// page 77
#include <iostream>

using namespace std;

// C++11 부터 enable_if 는 표준임

template<bool b, typename T = void> struct enable_if {
	typedef T type;
};

// 부분 특수화 할때는 T = void 와 같은 default 는 사용할 수 없다.
template< typename T> struct enable_if <false, T>{
	
};

int main()
{
	enable_if<true, int>::type				n1;	// int 가 됨.
	enable_if<true, double>::type		n2;	 // double 이 됨
	enable_if<true>::type						n3;  // void 타입이 됨. 하지만 void 변수는 만들 수 없으므로 error

	enable_if<false, int>::type				n4;  //error. type 자체가 존재하지 않음.
}