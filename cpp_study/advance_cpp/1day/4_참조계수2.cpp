
#include <iostream>

using namespace std;

class Car {
	int speed;
	int m_count = 0;
public:
	void ref() {
		++m_count;
	}
	void deref() {
		if (--m_count == 0)  delete this;
	}

protected: // protected 는 객체 외부에서 호출 안되므로,  객체를  stack에 만들 수 없게 함. 강제로 heap에 만들게 함.
	~Car() { cout << "car dtor" << endl; }
};

Car* p;

int main()
{
	Car* p1 = new Car;
	p1->ref();					// 규칙 1. 객체의 생성 시 참조 계수 증가
	Car*p2 = p1;
	p2->ref();					// 규칙 2. 객체 주소 복사 시 참조 계수 증가

	p2->deref();				// 규칙 3. 사용 후 참조 계수 감소
	p1->deref(); 

	//Car c; // 위와 같이 reference count 를 사용하면, stack 객체를 만들 수 없게 하는것, 195 page, onlyHeap 클래스
				// 방법은 소멸자를 protected: 에 넣는것. 그러면 heap에 만들수 밖에

	//Car::~Car( ) 를 컴파일러가 만들어 줘야 하는데, protected 라서 만들 수가 없음. 결국 빌드 에러
}