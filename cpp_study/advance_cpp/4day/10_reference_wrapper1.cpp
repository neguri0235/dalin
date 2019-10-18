#include <iostream>

using namespace std;

// C++ 참조: 한번 가르킨 메모리는 변경할 수 없다 . 
// 일종의 상수 대입 연산 시 값이 이동한다.
/*
int main()
{
	int n1 = 10;
	int n2 = 20;

	int& r1 = n1;
	int& r2 = n2;

	r1 = r2;

	cout << n1 << endl;
	cout << n2 << endl;
	cout << r1 << endl;
	cout <<r2 << endl;
}
// 출력하면 모두 20
*/

/*
int main()
{
	int n1 = 10;
	int n2 = 20;

	// reference wrapper : 이동 가능한 참조. 원래는 참조는 이동하지 않고, 값만 변경됨.
	reference_wrapper<int> r1 = n1;
	reference_wrapper<int> r2 = n2;

	r1 = r2;

	cout << n1 << endl;
	cout << n2 << endl;
	cout << r1 << endl;
	cout << r2 << endl;
}

*/

// 어떤 객체를 가르킬 수 있는것은 포인터 밖에 없다.
// 1. 주소를 보관
// 2. 진짜 참조타입으로 변환 가능

template<typename T> struct xreference_wrapper {
	T* obj;
public:
	xreference_wrapper(T& r) : obj(&r) {}

	// 진짜 참조화 호환 되어야 함.  - reference 처럼 동작하는 것을 하나 만드는 것임
	// 대입 하는 것은 컴파일러가 알아서 만들어줌
	operator T&() { return *obj; }
};

int main()
{
	int n1 = 10;
	int n2 = 20;

	// reference wrapper : 이동 가능한 참조. 원래는 참조는 이동하지 않고, 값만 변경됨.
	xreference_wrapper<int> r1 = n1;
	xreference_wrapper<int> r2 = n2;

	r1 = r2;

	cout << n1 << endl;
	cout << n2 << endl;
	cout << r1 << endl;
	cout << r2 << endl;
}
