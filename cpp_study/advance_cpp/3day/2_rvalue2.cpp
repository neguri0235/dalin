#include <iostream>
using namespace std;

// 핵심 : value category는 객체가 아닌 표현식(expression)에 대한 개념

// statement : ; 으로 종료되는 한줄의 코드 모음
// expression : 하나의 값으로 계산될 수 있는 코드 모음

int main()
{
	int n = 10; 
	n = 20;  // n : lvalue

	// n+1 은 11이 되어서 값임. 메모리에 들어가는 것이 아님 . rvalue
	n + 1 = 20;   // error
	
	// n+n 은 20, 값. error
	n + n = 20;  // error
	cout << n << endl;
	n = 3;
	// lvalue(전위형 증가 연산자는 왼쪽에).값을 리턴하는 것이 아니고 참조를 리턴하는 것
	// 참조를 리턴해야, 변경된 값을 유지하기 때문
	++n = 20;  // ok.
	
    // 참조를 리턴하지 않고 값을 리턴하게 됨.  참조를 리턴하면 변경된 값이 리턴되므로
	// 값을 리턴하고서, 메모리의 값을 증가 시킴.
	n++ = 20; // error
}