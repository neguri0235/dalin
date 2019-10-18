#include <iostream>

using namespace std;

template<typename T> struct xreference_wrapper {
	T* obj;
public:
	xreference_wrapper(T& r) : obj(&r) {}
	operator T&() { return *obj; }
};


void foo(int& a) { a = 100; }

template<typename T> void Bind(T arg) {
	foo(arg);
}

template<typename T>
xreference_wrapper<T> xref(T& obj) {
	return xreference_wrapper<T>(obj);
}

int main()
{
	int n = 0; 

	// Bind(&n);   // T가 int* 인테 int& 로 변환될 수 없다. error
	
	// xreference_wrapper<int> r(n);
    // Bind(r);  // 결국 주소를 보내는 것, 그런데 r은 int& 로 변환 가능

	// 임시 객체로 만들자. 
	//Bind(xreference_wrapper<int>(n));
	// 그런데 좀 길다.그래서 ..xreference_wrapper를 만들어 주는 함수를 만듬
	Bind(xref(n));
	cout<< n << endl;
}
