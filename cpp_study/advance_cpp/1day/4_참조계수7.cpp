#include <iostream>
#include <atomic>

// https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/include/utils/LightRefBase.h
using namespace std;

template<typename T> class RefCounted {
	// multi thread 환경에서 안전하게 위해 이렇게 함.
	mutable atomic<int> m_count = 0;
public:
	void ref() const {
		m_count.fetch_add(1);
	}
	void deref() const {
		if (m_count.fetch_sub(1)  ==  1)  delete static_cast<const T*>(this);  
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
