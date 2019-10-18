#include <iostream>
using namespace std;

class RefCounted {
	mutable int m_count = 0;
public:
	void ref() const {												// 상수 멤버 함수 안에서도 값을 변경하고자 할때, mutable을 붙이 도록 함
		++m_count;
	}
	void deref() const {				// void deref(RecCounted* this)
		if (--m_count == 0)  delete this;
	}
	// 기반 클래스 타압의 포인터로 삭제할 때 파생 클래스의 소멸자가 호출되게 하려면 
	// 가상 소멸자를 사용해야 한다.
protected: 
	 virtual ~RefCounted() { cout << "RefCounted dtor" << endl; }
};

// Truck도 참조 계수로 관리하고 싶다.

class Truck : public RefCounted {
public:
	 ~Truck() { cout << "Truck dtor" << endl; }
};


int main()
{
	Truck* p = new Truck;
	p->ref();
	p->deref();
}