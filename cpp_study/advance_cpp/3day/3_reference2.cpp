#include <iostream>

using namespace std;

// __FUNCTION__ : 함수 이름 . C++ 표준
// __FUNCSIG__ : 함수 이름 + signature  (vc++)
//									__PRETTY_FUNCTION__ (g++)


void foo(int& a) { 	cout << __FUNCSIG__ << endl;}
void foo(const int& a) { 	cout << __FUNCSIG__ << endl;}
void foo(int&& a) { 	cout << __FUNCSIG__ << endl;}

int main()
{
	int n = 10;
	foo(n);		// 1번 -> (1번 없으면) 2번 순으로
	foo(10);	// 3번 -> (3번 없으면) 2번

	int& r1 = n; 
	foo(r1);			// 1번 -> (1번 없으면) 2번 순으로

	int&& r2 = 10;
	// >>>> 중요 !!! 어디로 가는지? 1번임. 10은 rvalue 이지만, r2는 lvalue 임.그래서 1번으로 간다. 없으면 2번으로.
	foo(r2); 
	foo(r2+1);    //  3번으로 감. 없으면 2번

	foo(static_cast<int&&> (r2));// 3번으로
	/*
	https://en.cppreference.com/w/cpp/language/static_cast
	If new_type is an rvalue reference type, static_cast converts the value of glvalue, 
		class prvalue, or array prvalue (until C++17)any lvalue (since C++17) expression 
		to xvalue referring to the same object as the expression, 
	*/
	foo(static_cast<int&> (10));   // casting error
	// int&, int&& : 데이터 타입
	// rvalue, lvalue: 표현식에 대한 속성
}