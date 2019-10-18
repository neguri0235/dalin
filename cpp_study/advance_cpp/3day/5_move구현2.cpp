#include <iostream>
#include <string>

using namespace std;

// rule of 3
// 포인터가 있고 생성자에서 자원 할당하면
// 소멸자, 복사 생성자, 대입 연산자가 필요하다.

class People {
	string		name;
	int			age;
	char*		addr;
public:
	People(string n, int a, const char* ad) : name(n), age(a) {
		addr = new char[strlen(ad) + 1];
		strcpy(addr, ad);
	}
	~People() {
		delete[] addr;
	}

	// 포인터가 멤버에 있으니까, 복사 생성자를 꼭 만들어야 함
	People(const People& p) :name(p.name), age(p.age) {
		addr = new char[strlen(p.addr) + 1];
		strcpy(addr, p.addr);
	}

	// 복사 생성자를 만든 경우는 대부분 대입 연산자도 필요하다
	// 그렇지 않으면 실행 도중 프로그램이 종료 됨

	// 규칙 1. 대입의 반환값은 자신을 참조로 해야 한다.
	// 규칙 2. 자신과의 대입을 조사해야 한다
	// 규칙 3. 기반 클래스가 있다면 기반 클래스의 대입 연산자도 호출해야 함
	// 규칙 4. 예외에 안전하게 작성해야 한다.

	People& operator=(const People& p) {

		// 자신과의 대입 조사
		// p1 = p1 이렇게도 가능한데, 그러면 delete [] addr에서 문제 발생.
		// 왜냐면 int i; i = i; 란 구문이 가능하므로, 충분히 발생할 수 있는 구문
		if (&p == this) return *this;

		// 기반 클래스가 있다면 기반 클래스의 대입 연산자도 호출해야 한다.
		// Base::operator=(p); (상속 받은 클래스의 경우)

		// 멤버 변수가 포인터가 아니면 그냥 대입
		name = p.name;
		age = p.age;

		// 포인터는 기존 메모리를 제거하고, 새로운 메모리에 복사
		delete[] addr;
		addr = new char[strlen(p.addr) + 1];
		strcpy(addr, p.addr);
		return *this;
	}
};

int main()
{
	People p1("kim", 10, "seoul");
	People p2 = p1;  // 복사 생성자
	p2 = p1;					// 대입 연산자 p2.operator=(p1)

	int n  = 10;
	(n = 20) = 30;
}