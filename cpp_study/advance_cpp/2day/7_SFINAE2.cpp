// 215 page
#include <iostream>
using namespace std;

// 1. foo(10) -> template 버젼을 사용하기로 결정
// 2. T::type 을 int::type으로 치환하게 되면 , 잘못된 표현식 등장
// 컴파일 에러가 아니라 후보군에서 제외

// 3. 다른 버전의 foo 가 있으면 사용 가능
// "치환 실패는 에러가 아니다", substitution failure is not an error. (SFINAE)

// T가 int이면 T::type 이란 표현은 없음
template<typename T> typename T::type foo(T a) { cout << "T" << endl;  return 0; }
template<typename T> void foo(T a) { cout << "T" << endl;  }
 
//void foo(int	 a) {	cout << "int" << endl; }
void foo(...) { cout << "..." << endl; }



int main()
{
	foo(10);
	// 1. int
	// 2. T -> template 
	// 3. ..
}