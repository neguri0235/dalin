// 143 page
#include <iostream>
using namespace std;

/*
(1) . 실행안되는 함수
int foo(int a) {
	cout << "foo" << endl;
	return 0;
}
*/
// (2) 이렇게 함수 바디가 없이 선언만 있어도 실행이된다.
int foo(int a);

int main()
{
	int n = 0;
	cout << sizeof(n) << endl;				// 4 byte
	cout << sizeof(&foo) << endl;		// 주소의 크기 32bit 환경 4
	//cout << sizeof(foo) << endl;		// error. 함수가 사용하는 코드 메모리는 구할 수 없다
	cout << sizeof(foo(n)) << endl;	// 반환값의 크기. "foo" 라고 출력되지 않음. (평가되지 않음)

	// 평가되지 않는 표현식
	// unevaluated expression 
	// 함수 호출식이 실제로 함수를 호출하지 않는 것
	sizeof(foo(0));
	decltype(foo(0)) m;  // foo(0) 호출 후 반환하는 타입과 같은 타입의 m
	const type_info& r = typeid(foo(0));   // 
	bool b = noexcept(foo(0));   // 예외 가능성이  없으면 true, 있으면 false

}