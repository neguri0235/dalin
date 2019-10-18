#include <iostream>
#include <type_traits>

using namespace std;

class Shape {
	virtual void Draw() {};
};

/*
template<typename U> struct xis_abstract {
	template<typename T> static char check(T(*)[1]);  // static 붙이는 이유는 멤버 함수 이므로 객체 없이 부르기 위해
	template<typename T> static int check(...);

	static constexpr bool value = (sizeof(check<U>(0)) == sizeof(char));
};
*/
// int 와 char 이 크기가 같은 수 있으므로( int는 char보다 크거나 같다)

template<typename U> struct xis_abstract {
	typedef char YES[1];
	typedef char NO[2];

	template<typename T> static NO& check(T(*)[1]);  // static 붙이는 이유는 멤버 함수 이므로 객체 없이 부르기 위해
	template<typename T> static YES& check(...);

	static constexpr bool value = (sizeof(check<U>(0)) == sizeof(YES));
};

int main()
{
	cout << xis_abstract<Shape>::value << endl;
}