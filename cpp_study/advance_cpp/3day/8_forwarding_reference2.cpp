#include <iostream>

using namespace std;

// 모든 정수값을 받을 수 있는 함수를 만들고 싶다.

// 방법 1.  call by falue
// 특징 : 복사본을 생성, 크기가 큰 타입의 경우 오버헤드가 있다.
//void foo(int a) {}

// 방법 2. call by reference
// 특징 : lvalue만 가능하다
//void foo(int& arg) {}

// 방법 3. call by  const lvalue reference
// 특징 : 복사본은 아니지만 const 이므로 원본 수정은 불가능
//void foo(const int& arg) {}

// 방법 4. 함수를 2개 만든다.
// 특징 : 원본에 const 추가 없이 그대로 받을 수 있다.
//				단 2개의 함수를 만들어야 한다.
//void foo( int& arg) {}
//void foo( int&& arg) {}

//방법 5. forwarding reference를 사용하면 자동으로 2개의 함수가 생성된다.
template<typename T> void foo(T&& arg) {
	cout << __FUNCSIG__ << endl;
}

int main()
{
	int n = 10;
	foo(n);  // T : int&  arg: int&
	foo(10);// T: int arg:int&&
	const int c = 10;
	foo(c);
	/*
	void __cdecl foo<int&>(int &)
	void __cdecl foo<int>(int &&)
	void __cdecl foo<const int&>(const int &)
	*/
}