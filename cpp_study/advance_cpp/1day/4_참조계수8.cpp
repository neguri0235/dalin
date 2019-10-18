#include <iostream>
#include <atomic>

// https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/include/utils/LightRefBase.h
using namespace std;


// 복사 금지는 자주 사용한다. 그래서 MACRO로 만들면
#define WTF_MAKE_NONCOPYABLE(classname)		\
				classname(const classname&) = delete;			\
				classname& operator=(const classname&) = delete;

template<typename T> class RefCounted {
	// 함수 삭제 문법으로 복사 생성자와 대입 연사자를 삭제한다.
	// 복사 생성자와 대입 연산자를 사용하면 컴파일 에러

	//RefCounted(const RefCounted&) = delete;
	//RefCounted& operator=(const RefCounted&) = delete;

	// 아래 매크로를 사용하면 뒤의 두줄을 대치 할 수 있음.
	WTF_MAKE_NONCOPYABLE(RefCounted)
	
	mutable atomic<int> m_count = 0;
public:
	RefCounted() = default;
	void ref() const {
		m_count.fetch_add(1);
	}
	void deref() const {
		if (m_count.fetch_sub(1) == 1)  delete static_cast<const T*>(this);
	}

protected:
	// 원래 소멸자는 inline 이지만 가독성을 위해서 붙여줌
	inline ~RefCounted() { cout << "RefCounted dtor" << endl; }
};


class Truck : public RefCounted<Truck> {
public:
	Truck() = default;
	~Truck() { cout << "Truck dtor" << endl; }

	Truck(const Truck& t) {
		// 내 멤버만 복사. 기반 클래스의 참조 개수를 복사하거나
		// 기반 클래스의 복사 생성자를 호출 하지 말자
		// 컴파일러가 만들어 주는 버젼은 기반 클래스 복사 생성자 호출
	}
};

int main()
{
	Truck* p1 = new Truck; 	p1->ref();
	Truck* p2 = p1;					p2->ref();

	Truck* p3 = new Truck(*p1);
	p3->ref();

	p1->deref();
	p2->deref();

}
