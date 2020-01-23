#include <iostream>

using namespace std;

class Car {
public:
	void Go() { cout << "Car  Go" << endl; }
	~Car() { cout << "~Car" << endl; }
};


// 아래 코드가 핵심임
// 개념: 임의의 객체가 다른 타입의 포인터 역할을 하는 것
// 원리: -> 와 * 를 재 정의해서 포인터 처럼 보이게 하는것

// 장점: raw pointer 가 아닌 객체이다.
//				생성/복사/소멸의 과정에 추가의 작업을 할 수 있다.
//				대표적 활용이 소멸자에서 자동 삭제 기능.

class Ptr {
	Car* obj;
public:
	Ptr(Car* p = 0) : obj(p) {}
	~Ptr() { delete obj; }
	Car* operator->() { return obj; }
	Car& operator*() { return *obj; }		// 핵심 .. 반드시 '참조' 리턴해야 함
};

int main()
{
	Ptr p = new Car;  //    Ptr p(new Car), ptr 객체에 car를 넣은 개념
	p -> Go();   // ( p.operator->())Go() => (p.operator->())->Go()
	(*p).Go();
}