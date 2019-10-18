#include <iostream>
using namespace std;

class Car {
	int speed;
	//int m_count = 0;
	mutable int m_count = 0;
public:
	void ref() const {												// 상수 멤버 함수 안에서도 값을 변경하고자 할때, mutable을 붙이 도록 함
		++m_count;
	}
	void deref() const {
		if (--m_count == 0)  delete this;
	}

protected: // protected 는 객체 외부에서 호출 안되므로,  객체를  stack에 만들 수 없게 함. 강제로 heap에 만들게 함.
	~Car() { cout << "car dtor" << endl; }
};

Car* p;

int main()
{
	const Car* p1 = new Car;
	p1->ref();					// 아무리 객체가 상수 객체여도 참조 계수는 변경가능해야 함
	p1->deref();
}