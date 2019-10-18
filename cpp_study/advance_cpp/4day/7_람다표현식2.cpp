#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

class Test {
public:
	void operator () (int a, int b) & { cout << "&" << endl; }
	void operator () (int a, int b) && { cout << "&&" << endl; }
};

// 함수를 인자로 받고 싶다.
// template<typename T> void foo(const T& func) { (1)
template<typename T> void foo(T&& func) {
	
	// func(1, 2);  // (1) 때문에 func가 const라서 ( ) 연산자가 const 멤버여야 함. 
	// func(1, 2); // (4) && 가 아닌 &가 호출. T&& func = T() 인데, T()는 rvalue 이지만 func 자체는 lvalue 임
	std::forward<T>(func)(1, 2);
}

int main()
{
	foo([](int a, int b) { return a + b; });
	Test t; foo(t);
	foo(Test()); // (3) && 호출이 되기를 기대

}