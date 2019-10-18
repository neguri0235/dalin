#include <iostream>
using namespace std;

int main()
{
	int n = 10;
	int* p = &n;

	// decltype이 동작하는  규칙 
	// 1 : 변수 이름만 있는 경우
	//		->  해당 변수의 선언을 조사해서 타입 결정
	decltype(n) d1;  // int d1
	decltype(p) p2;  // int* p2

	// 2: 변수에 연산자가 포함된 표현식이 있는 경우
	//		-> 해당 표현식이 등호의 왼쪽에 올 수 있으면 참조, <-> 아니면 값 타입
	decltype(*p) d ;		// int& d3; 이렇게 되기 때문에 error. decltype(*p) d = n ; 이라고 했으면 에러 아님
	decltype(n + 1) d4;  //	int d4
	decltype(++n) d5 ; // int&d5; error.
	decltype(n++) d6; //int d6

	decltype(n) d7; // int
	decltype(10) d8; // int
	//decltype((n)) d9; // int& 
	decltype((10)) d10; // int
}