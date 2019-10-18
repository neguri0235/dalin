#include <iostream>
#include <bitset>
using namespace std;

// 1. 일반 함수는 자신만의 타입이 없다.
//		signature(전달 인자와 리턴)가 동일하면 같은 타입
// 2. 함수 객체는 자신만의 타입이 있다.
//		signaure가 동일해도 다른 타입

struct Plus {
	inline int operator() (int a, int b) { return a + b; }
};

struct Minus {
	inline int operator() (int a, int b) { return a - b; }
};

// void foo(Plus p)
// 인자로 다양한 정책(함수)를 보낼 수 있는데, 
// 정책이 인라인 치환이 가능한 코드
// 함수 객체 + 템플릿으로 만드는 기술
template<typename T> 
void foo(T f) 
{
	int n = f(1, 2);  
}


int main()
{
	Plus p; foo(p);			// foo(Plus) 함수 생성
	Minus m; foo(m);		// foo(Minus) 함수 생성
}