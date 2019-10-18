#include <iostream>
#include <string>
#include <vector>

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
	// (1) 예외가 발생하지 않게 만들어야 함
	// (2)  여기서 noexcept 를 붙여야 함. 그렇지 않으면 resize( )에서 복사만 함
	
	
	// People(People&& p) noexcept  (3) 아래처럼 바꿀 수 있음. 
	// std::string 에서 예외가 있으면 어떻게 하나?
	
	//People(People&& p)  // (4) 이렇게 만들면, resize( ) 할때 복사 생성자만 부르게 됨
	People(People&& p) noexcept (is_nothrow_constructible<string>::value) // (5) 이걸 만들어야 resize 를 할 때 이동 생성자를 부름
		
		:name(std::move(p.name)), age(p.age), addr(p.addr) {
		cout << "move ctor " << endl;
		p.addr = nullptr;
		p.age = 0;
	}

	People& operator=(People&& p) noexcept {
		cout << "move = " << endl;

		// 표준에 아래는 정의되어 있지 않다. .
		// 자기 자신에게 이동하는 것은 미정의
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

	People p("kim", 5, "seoul");

	People p1 = p; // 무조건 복사 생성자
	People p2 = move(p); // 무조건 move 생성자

	// 예외가 없을 때만 move 생성자를 부름. , 예외가 있으면 복사생성자를 부르게 되며,
	// move 생성자에 noexcept 키워드가 있는지 확인해야 함.
	// 따라서 std::vector< > 같은 것에 객체 넣을 때 해당 객체의 move 생성자에 noexcept를 넣지 않으면 효과가 없음.
	People p3 = move_if_noexcept(p2);
	 
	// move_if_noexcept 의 원리
	People p4 = is_nothrow_move_constructible<People>::value ? move(p3) : p3;
	
	cout << "------------" << endl;

	// default 생성자가 없으므로 임시 객체를 넘겨야 함.
	vector<People> v(3, People("kim", 5, "Seoul"));
	cout << "--------------" << endl;
	v.resize(5, People("kim", 5, "Seoul"));
	cout << "--------------" << endl;
}
