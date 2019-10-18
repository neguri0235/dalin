#include <iostream>
#include <type_traits>
using namespace std;
#define CHECK_VALUE_CATEGORY(...)											\
if (is_lvalue_reference<decltype ((__VA_ARGS__)) >::value)  \
	cout << __VA_ARGS__<<" : lvalue" << endl;								\
else																													\
		cout << __VA_ARGS__<<" : rvalue" << endl;																			

int main()
{
	// value category를 조사하는 방법
	int n = 0;
	CHECK_VALUE_CATEGORY(10)
	CHECK_VALUE_CATEGORY(n)
	CHECK_VALUE_CATEGORY(n+n)
	CHECK_VALUE_CATEGORY("Hello")  // 문자열은 조금 특이항 경우
}