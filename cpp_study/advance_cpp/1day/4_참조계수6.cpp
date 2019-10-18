#include <iostream>
using namespace std;

template<typename T> class RefCounted {
	mutable int m_count = 0;
public:
	void ref() const {
		++m_count;
	}
	void deref() const {
		//if (--m_count == 0)  delete (T*)this; 
		//if (--m_count == 0)  delete static_cast<T*>(this);       //   RecCounted 와 Truck은 상속 관계라서 연관 관계 있음. static_cast. error
		
		if (--m_count == 0)  delete static_cast<T*>(const_cast<RefCounted*>(this));       

		//   deref( ) 함수가 const 타입이기 때문에, this 는 const* 로 되어 있음. 그래서 const_cast를 통해서 const를 제거해야 함.
		if (--m_count == 0)  delete static_cast<const T*>(this); 
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
