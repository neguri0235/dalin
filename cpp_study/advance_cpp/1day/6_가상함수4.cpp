#include <iostream>

using namespace std;
/*
class A {
	int a;
public:
	void foo() { cout << "1" << endl; }
};

class B {
	int b;
public:
	void goo() { cout << "2" << endl; }
};

int main ()
{
	A aaa;
	B* p = reinterpret_cast<B*>(&aaa);
	p->goo();  // 2 goo(p)
	return 0;
}
*/

/*
class A {
	int a;
public:
	virtual void foo() { cout << "1" << endl; }
};

class B {
	int b;
public:
	virtual void goo() { cout << "2" << endl; }
};

int main ()
{
	A aaa;
	B* p = reinterpret_cast<B*>(&aaa);
	p->goo();  // 1 , p->vtptr[1]() 이라는 기계어 코드 생성
	return 0;
}
*/

/*
class A {
	int a;
public:
	virtual void foo() { cout << "1" << endl; }
};

class B {
	int b;
public:
	void goo() { cout << "2" << endl; }
};

int main()
{
	A aaa;
	B* p = reinterpret_cast<B*>(&aaa);
	p->goo();  // 2
	return 0;
}
*/
class A {
	public:
	virtual void foo(int n = 10) { cout << "A " << n<< endl; }
};

class B : public A {
public:
	virtual void foo(int n = 20) { cout << "B " << n << endl; }
};

int main()
{
	A* p = new B;
	p->foo();
	// B  , 10
	// default 값을 설정하는 것은 빌드 시점에 하는 것임. 그래서 인자를 전달 안하면 10 이 나오는 것임
	// p->vtptr[1](10) 이라고 기계어 코드를 만듬
	// 결국 가상함수에서 default parameter는 사용하면 안됨
	return 0;
}
