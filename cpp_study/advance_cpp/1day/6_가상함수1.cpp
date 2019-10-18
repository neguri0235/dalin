#include <iostream>
using namespace std;

class Animal {
public:
	virtual void Cry() { cout << "1" << endl; }
};

class Dog : public Animal {
public:
	// 함수 오버라이드
	void Cry() {
		cout << "2" << endl;
	}
};

int main()
{
	Animal a; a.Cry();
	Dog		d; d.Cry();

	Animal *p = &d;
	p->Cry();
}

// p->Cry( )를 어떤 함수로 연결할 까? => 함수 바인딩
// 1. static binding : 컴파일 시간에 컴파일러가 함수를 결정
//										무조건 포인터 타입으로 결정 => Animal Cry()
//										=> Early Binding 이라고 부름 (C++, C#)

// 2. dynamic binding :  컴파일 시에 p 가 가르키는 메모리 조사하는 기계어 코드 생성. 실행시 조사 후 호출
//												Dog Cry()
//												Late Binding 이라고 부름
//												java, swift, kotlin, objective-C, 