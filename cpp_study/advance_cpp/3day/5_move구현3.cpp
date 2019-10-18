#include <iostream>
#include <string>

using namespace std;


// rule of 5
// 포인터가 있고 생성자에서 자원  할당하면
// 소멸자, 복사 생성자, 대입 연산자가 필요하다.
//  C++11 에서는 "move 생성자", "move 대입 연산자"를 만들어야 함.

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

	People(const People& p) :name(p.name), age(p.age) {
		cout << "copy ctor " << endl;
		addr = new char[strlen(p.addr) + 1];
		strcpy(addr, p.addr);
	}

	People& operator=(const People& p) {
		cout << "copy = " << endl;
		if (&p == this) return *this;
		name = p.name;
		age = p.age;

		delete[] addr;
		addr = new char[strlen(p.addr) + 1];
		strcpy(addr, p.addr);
		return *this;
	}

	// move 생성자
	// 중요 !!!: 모든 멤버에 대해서 move로 옮겨야 함
	// name은 string이므로 move( )를 부르고, addr 은 포인터 주소만 복사
	People(People&& p) :name(std::move(p.name)), age(p.age), addr(p.addr) {
		cout << "move ctor " << endl;
		p.addr = nullptr;
		p.age = 0;
	}

	People& operator=( People&& p) {
		cout << "move = " << endl;
		
		// 표준에 아래는 정의되어 있지 않다. .
		// if (&p == this) return *this;

		name = p.name;
		age = p.age;

		delete[] addr;
		addr = std::move(p.addr);
		p.addr = nullptr;
		p.age = 0;
		return *this;
	}
};

int main()
{
	People p1("kim", 10, "seoul");
	People p2 = p1;		// 복사 생성
	p2 = p1;						// 복사 대입

	People p3 = std::move(p1);		// move 생성
	p3 = std::move(p2);						// move 대입

	p3 = move(p3); // undefined. 사용하면 안됨
}
