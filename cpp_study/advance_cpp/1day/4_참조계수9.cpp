#include <iostream>
#include <atomic>

using namespace std;

//https://github.com/WebKit/webkit/blob/master/Source/WTF/wtf/RefCounted.h

	  // 복사 금지는 자주 사용한다. 그래서 MACRO로 만들면
#define WTF_MAKE_NONCOPYABLE(classname)		\
				classname(const classname&) = delete;			\
				classname& operator=(const classname&) = delete;



// 코드 메모리를 줄이기 위해
// template 클래스 안에서 T를 사용하지 않는 모듬 멤버는 기반 클래스로 옮김. 
// 기반 클래스는 template이 아니어야 함
// 그렇지 않으면 각 멤버 함수가 증가함.

// Thin template (237 page) 

class RefCountedBase {
protected:
	mutable atomic<int> m_count = 0;
public:
	void ref() const {
		m_count.fetch_add(1);
	}
};

template<typename T> class RefCounted :  public RefCountedBase{
	WTF_MAKE_NONCOPYABLE(RefCounted)

public:
	RefCounted() = default;
	void deref() const {
		if (m_count.fetch_sub(1) == 1)  delete static_cast<const T*>(this);
	}

protected:
	inline ~RefCounted() { cout << "RefCounted dtor" << endl; }
};


class Truck : public RefCounted<Truck> {
public:
	Truck() = default;
	~Truck() { cout << "Truck dtor" << endl; }
};


int main()
{
	Truck* p1 = new Truck; 	p1->ref();
	Truck* p2 = p1;					p2->ref();

	p1->deref();
	p2->deref();

}
