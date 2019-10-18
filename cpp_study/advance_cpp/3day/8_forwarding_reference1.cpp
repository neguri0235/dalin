#include <iostream>

using namespace std;

// int&		: int 타입의 lvalue만 가능
// int&&		: int 타입의 rvalue만 가능
// T&			: 임의의 타입의 lvalue만 받을 수 있다.
// T&&		: 임의의 타입 &, && 모두 받을 수 있다. -> 'forwarding reference' 라고 부름
//					'universal reference' 라고 부르기도 함(effective c++)

void f1(int&) {}  
void f2(int&&) {}   

// T&&   : 임의의 타입의 lvalue 와 rvalue 를 모두 받는다.
// 인자로 n(lvalue   )를 보내면		 T: int&,		T&& a: int &
// 인자로 10(rvalue)를 보내면		 T:int,			T&& a: int&&
// 결국, f4(int&)와 f4(int&&) 함수 두개 모두다 생성하는 것

// T가 임의의 타입이므로 T& 란게 T로 올 수 있음
template<typename T> void f3(T&		a) { 
	cout << "f3: " <<  __FUNCSIG__ << endl;;
}
template<typename T> void f4(T&&  a) {
	cout << "f4: " << __FUNCSIG__ << endl;;
}

int main()
{
	int n = 10;
	// 1. 사용자가 타입을 명시적으로 지정하는 경우 
	// <int >와 같이 명시적으로 타입을 지정 ---> collapsing 규칙을 따름
	cout << "f3 : 사용자 타입 지정" << endl;
	f3<int>(n);		// T& : int &  f3(int& a) 라는 함수가 생성됨
	f3<int&>(n);		//T& : int& &   f3(int& a) 라는 함수가 생성됨. (collapsing에 의해서)
	f3<int&&>(n);		//T& : int&& &   f3(int& a) 라는 함수가 생성됨. (collapsing에 의해서)
	cout << "------------" << endl;
	// 2. 사용자가 타입을 지정하지 않는 경우
	// 함수 인자를 보고 컴파일러가 T 타입을 결정해야 한다.
	f3(n);  // T는 int
	
	//f3(10);  // 컴파일 에러. rvalue를 & 로 전달 받을 수 없다.

	cout << "f4 : 사용자 타입 지정" << endl;
	// 1. 타입을 명시적으로 전달하는 경우
	f4<int>(10);					// T&& : int&&			f4(int&& a) 생성
	f4<int&>(n);				// T&& : int& &&		f4(int& a) 생성  - collaping
	f4<int&&>(10);			// T&& : int&& &&	f4(int&& a) 생성 
	cout << "------------" << endl;
	// 2.	타입을 전달하지 않으면 컴파일러가 인자를 보고 타입을 결정해야 한다
	f4(n);			// T: int&           T&&: int& && => int&  a의 타입: int&
	f4(10);		// T:int				T&& : int&&  => int&&	a의 타입: int&&
}