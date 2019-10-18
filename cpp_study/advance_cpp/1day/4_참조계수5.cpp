#include <iostream>
using namespace std;


/*

class RefCounted {
	mutable int m_count = 0;
public:
	void ref() const {												// 상수 멤버 함수 안에서도 값을 변경하고자 할때, mutable을 붙이 도록 함
		++m_count;
	}
	void deref() const {				// void deref(RecCounted* this)
														//  이렇게 하고 싶은데 RefCounted에서는 Truck을 알 수 없음.
		if (--m_count == 0)  delete (Truck*)this;      
	}

	// 가상 소멸자는 오버헤드가 있다. 소멸자를 가상으로 하지 말고 만들어야 함.
protected:
	 ~RefCounted() { cout << "RefCounted dtor" << endl; }
};

// Truck도 참조 계수로 관리하고 싶다.

class Truck : public RefCounted {
public:
	~Truck() { cout << "Truck dtor" << endl; }
};
*/


// page 71. CRTP 기술 . Curiously Recurring TemplatePattern
template<typename T> class RefCounted {
	mutable int m_count = 0;
public:
	void ref() const {
		++m_count;
	}
	void deref() const {
		if (--m_count == 0)  delete (T*)this;       // CTRP 기술
	}
	// 가상 소멸자는 오버헤드가 있다. 소멸자를 가상으로 하지 말고 만들어야 함.
protected:
	~RefCounted() { cout << "RefCounted dtor" << endl; }
};


class Truck : public RefCounted<Truck> {
public:
	~Truck() { cout << "Truck dtor" << endl; }
};

int main()
{
	Truck* p = new Truck;
	p->ref();
	p->deref();
}