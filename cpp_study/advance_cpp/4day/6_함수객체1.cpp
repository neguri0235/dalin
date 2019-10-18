#include <iostream>

using namespace std;

// function object : 함수처럼( ) 를 사용해서 호출 가능한 객체
// 요즘은 callable object 라는 용어를 사용

struct Plus {
	int operator() (int a, int b) {
		return a + b;
	}
};

int main()
{
	Plus p;					// 객체
	int n = p(1, 2);		// 객체를 함수처럼 사용
									// p.operator()(1,2) 
	cout << n << endl;
}