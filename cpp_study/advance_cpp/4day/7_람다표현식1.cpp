#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
	int x[10] = { 1,3,5,7,9,2,4,6,8,10 };
	// 람다 표현식 
	// 활용 1. STL 사용 시 알고리즘 함수의 인자로 전달
	sort(x, x + 10, [](int a, int b)  { return a < b; });

	// 활용 2. auto 변수에 담아서 함수처럼 사용
	auto f = [](int a, int b) -> int { return a + b; };  // 이 자체로는 함수가 아니라 객체임. (함수, 임시 객체)

	int n = f(1, 2);
	
	auto f1 = []() {};  // 클래스를 만들었는데, 임시 객체 
	//auto& f2 = []() {};  // 임시 객체 이므로 rvalue . 에러
	auto&& f3 = []() {};  // rvalue 이므로 forwarding referece 임. 

	decltype(f1) f4;		// error. 람다표현식을 default 생성자는 없음.
	decltype(f1) f5(f1);
}

/*
https://en.cppreference.com/w/cpp/language/lambda
Constructs a closure: an unnamed function object capable of capturing variables in scope.
*/