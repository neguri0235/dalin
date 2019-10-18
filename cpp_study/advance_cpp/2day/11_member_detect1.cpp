#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

class Test {
public:
	Test(int n) {}
	void resize(int n ) {}
};

template<typename T> T xdeclval();  // declval 이 표준임. 핵심 구현이 없음.
// T&& 이 맞는 표현임
// https://en.cppreference.com/w/cpp/utility/declval


template<typename U> struct has_resize_function {
	typedef char YES[1];
	typedef char NO[2];

	// template<typename T> static YES& check(decltype(T().resize(0) )* n);  (2)
	// template<typename T> static YES& check(decltype(T().resize(0) )* n);  * 를 붙이는 이유는 void 타입인 경우를 대비해서. 
	// T() 는 default 생성자가 있어야 함.
	template<typename T> static YES& check(decltype(xdeclval<T>().resize(0))* n);
	template<typename T> static NO& check(...);

	static constexpr bool value = (sizeof(check<U>(0)) == sizeof(YES));
};

int main()
{
	cout << has_resize_function<vector<int> >::value << endl;
	cout << has_resize_function<Test>::value << endl; // (3) Test의 경우 default 생성자가 없어서 0 이 나옴
}