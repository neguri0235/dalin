#include <iostream>
using namespace std;

//[2_rvalue1.cpp](2_rvalue1.cpp)
int x = 0;
int foo() { return x; }
int& goo() { return x; }

// lvalue : 등호의 왼쪽에 올 수 있는 표기 법 
//					lvalue to rvalue conversion  (오른쪽에도 올 수 있다)
//					값 뿐만 아니라 이름(메모리)를 가지고, 단일 식(한 줄)을 넘어서 존재
//					주소 연산자로 주소를 구할 수 있다.
//					참조를 반환하는 함수

//	rvalue : 등호의 오른쪽에만 올 수 있다.
//					이름(메모리)이 없고 단일 식에만 있음
//					주소 연산자로 주소를 구할 수 없다

int main()
{
	// v1 : lvalue, 20 : rvalue
	int v1 = 10, v2 = 10;
	// 10 = v1; // 에러. 메모리가 없음
	v1 = 20;		
	v2 = v1;

	int* p1 = &v1;
	// int* p2 = &10;  // 에러
	
	// foo() = 10; // 에러
	goo() = 10;

	10; // rvalue
	"Hello";  // lvalue : 문자열 리터럴은 lvalue로 하기로 함.
//	"Hello"[0] = 'h';  // 예전 C 컴파일러는 허용
									// 요즘은 const char[] 이므로 에러
									// 문자열이 짧으면 그냥 코드 메모리로 올라가지만
									// 문자열이 길어 지면 데이터 메모리에 올리고서, 포인터로 가르킴

	const int c = 10; 
	//c = 20;  // error. immutable lvalue 라고 부름

	// 다음중 맞는 것은 ?
	// error . C 컴파일러는 허용하지만, 표준에는 맞지 않는 표현임
	//char* s1 = "hello";				
	const char* s1 = "hello";
}