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
	int a;
public:
	 void foo() { cout << "1" << endl; }
};

class B {
	int b;
public:
	virtual void goo() { cout << "2" << endl; }
};

int main()
{
	A aaa;
	B* p = reinterpret_cast<B*>(&aaa);
	p->goo();			// 런타임 에러가 발생함. 존재하지 않는 주소를 찾아가려고 하니 런타임 에러 발생
	return 0;
}
