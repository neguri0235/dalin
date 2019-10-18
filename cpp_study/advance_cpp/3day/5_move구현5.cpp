#include <iostream>
#include <string>


using namespace std;

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
		cout << "People copy ctor " << endl;
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

	People(People&& p) noexcept (is_nothrow_constructible<string>::value)
				:name(std::move(p.name)), age(p.age), addr(p.addr) {
		cout << "people move ctor " << endl;
		p.addr = nullptr;
		p.age = 0;
	}

	People& operator=(People&& p) noexcept {
		cout << "move = " << endl;
		name = p.name;
		age = p.age;

		delete[] addr;
		addr = std::move(p.addr);
		p.addr = nullptr;
		p.age = 0;
		return *this;
	}
};

// 규칙 1. 복사 계열과 move 계열을 모두 제공하지 않으면
//				컴파일러가 모두 디폴드 버젼을 제공해 준다.				


class Home {
	People p;
public:
	Home() : p("kim", 10, "seoul") {}

	Home(const Home& h) : p(h.p) {
		cout << "Home copy constructor" << endl;
	}


	// (3) 디폴트 move 생성자를 만들어 달라고 컴파일러에게 알려줌
	// 그렇지 않으면, 컴파일러는 복사 생성자를 사용자가 만들었으니, move 생성자도
	// 만들 것을 예상해서 컴파일러가 만들어 주지 않는다.
	// 그래서 아래 구문이 없으면 Home h3 = move(h1); 연산에 대해 복사 생성자가 불리게 된다.
	Home(Home&&) = default;

};

int main()
{
	Home h1;
	Home h2 = h1;
	Home h3 = move(h1);  // (1) 컴파일러가 move 생성자를 만들어 줌
}
