#include <iostream>
#include <type_traits>

using namespace std;

class Shape {
	virtual void Draw() {};
};

// 1. 조건을 만족하는 경우에만 함수를 호출

// 추상 클래스
// 1. 객체는 만들 수 없다
// 2. 포인터 변수는 만들 수 있다.
// 3. 배열을 가르키는 포인터는 만들 수 없다.
//template<typename T> char check(T a);
template<typename T> int check(T(*)[1] );
template<typename T> char check(...);


int main()
{
	if (sizeof(check<Shape>(0)) == sizeof(char)) {
		cout < "추상 아님" << endl;
	}
	else {
		cout << "추상" << endl;
	}
}