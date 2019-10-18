// 215 page
#include <iostream>
using namespace std;

void foo(...) { cout << "..." << endl; }
template<typename T> void foo(T a) { 
	typename T::type n;   // T 가 int 이면 에러 발생
}


// SFINAE 는 아래 3가지 경우만 사용 가능
// 1. 함수 반환 타입 - 가장 널리 사용
template <typename T> typename T::type foo(T a) { return 0; }

// 2. 함수 인자 : 생성사자등, 반환 타입이 없는 경우에 주로 사용
template<typename T> void foo(T a, typename T::type a = 0) {}

// 3. 템플릿 인자 - 함수 자체의 모양이 복잡하지 않은 장점이 있다
template<typename T, typename T2 = typename T::type> void foo(T a) {}
int main()
{
	foo(10);
}