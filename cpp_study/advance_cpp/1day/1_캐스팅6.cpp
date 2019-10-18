#include <iostream>

using namespace std;

// 값 캐스팅 : 임시 객체를 만들게 된다.
// 참조 캐스팅: 임시 객체가 생성되지 않는다.

struct Base {
	int value = 10;
	Base() {
		cout << "Base()" << endl;
	}
	Base(const Base& d) {
		cout << "Base copy" << endl;
	}
};

struct Derived : public Base { 
	int value = 20; 
	Derived() {}
};

int main()
{
	Derived d;
	cout << d.value << endl;

	// 기반 클래스 멈버 접근하기
	// 값 캐스팅 vs 참조 캐스팅
	cout << static_cast<Base>(d).value << endl;			// 임시 객체로 생성됨. 여기서 출력되는 10은 임시객체의 10임. 별도의 메모리
																										// 복새 생성자가 불리게 됨.
	cout << static_cast<Base&>(d).value << endl;

	//static_cast<Base&>(d).value = 30;   // 컴파일 됨
	//static_cast<Base>(d).value = 30;     //  컴파일 안됨. 왜냐면 임시 객체는 등호의 왼쪽에 올 수 없다.
																			// 따라서 항상 값 캐스팅 하면 안되고, 참조 캐스팅을 해야 함.
}
