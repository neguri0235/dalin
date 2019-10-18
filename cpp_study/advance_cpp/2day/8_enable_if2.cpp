#include <iostream>
#include <type_traits>
using namespace std;

// 최대 공약수를 구하는 함수
// 단, 정수 계열 타입만 사용가능하게 하고 싶다.


// 방법 1: C++11 static_assert ( ) 사용
// 조건을 만족하지 않으면 무조건 error
template<typename T> 
T gcd(T a, T b) {
	static_assert(is_integral<T>::value, "T is no integral");
	return a;
}

// 실수 계열은 아래 함수가 호출되게 하고 싶다
double gcd(double a, double b)
{
	cout << "double" << endl; return 0;
}

int main()
{
	gcd(3, 6);				// T 사용
	gcd(3.4, 2.8);		// double 사용
	gcd(3.4f, 2.8f);	// T 사용 - static assert error
}