#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

// 아래 두 함수는 같은 타입의 다른 함수
inline bool cmp1(int a, int b) { return a < b; }
inline bool cmp2(int a, int b) { return a > b; }

struct Less {
	inline bool operator()(int a, int b) { return a < b; }
};

struct Greater {
	inline bool operator()(int a, int b) { return a > b; }
};


template<typename T> void foo(T f) {
	bool b = f(1, 2);
}

int main()
{
	Less f1;
	Greater f2;

	foo(cmp1);		// T: bool(*) (int,int)
	foo(cmp2);		// T: bool(*) (int,int)
	foo(f1);				// T: Less
	foo(f2);				//T: Greater

	// 1. 컴파일 하면 foo 함수는 몇개 생성되나?  +>3개
	// 2. foo를 제외하고 함수가 몇개 있는가?
   // D:\supari\advcpp\4day > cl 6_함수객체7.cpp / FAs / Ob1
	//	/Ob1 : 인라인 치환 적용
	// /FAs: 어셈블리 소스 만들어 달라는 
}