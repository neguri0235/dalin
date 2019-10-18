### std::move( ) 구현

#### 대입 연산자 만들기

> rule of 3
* 포인터가 있고 생성자에서 자원 할당하면
1. `소멸자`
2. `복사 생성자`
3. `대입 연산자`가 필요하다.

``` cpp
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

	// 포인터가 멤버변수 에 있으니까, 복사 생성자를 꼭 만들어야 함
	People(const People& p) :name(p.name), age(p.age) {
		addr = new char[strlen(p.addr) + 1];
		strcpy(addr, p.addr);
	}

    // 대입 연산자를 만드는 규칙!!!

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
```


### move 생성자, move 대입 연산자 만들기

* rule of 5
1.  포인터가 있고 생성자에서 자원 할당하면
2.  `소멸자`, `복사 생성자`, `대입 연산자`가 필요하다.
3.  C++11 에서는 `move 생성자`, `move 대입 연산자`를 만들어야 함.

``` cpp
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
	}

	People& operator=(const People& p) {
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
		
		// 표준에 아래는 정의되어 있지 않다. 이런 동작은 하지 않을 것이라고 예상
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
```

### vector에서 resize( )  하려고 할때

> `resize()` 함수에 대해 어떤 생성자가 불리는지 확인해 보자

``` cpp
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
	
    // (4) 이렇게 만들면, resize( ) 할때 복사 생성자만 부르게 됨.
	//People(People&& p)
	People(People&& p) noexcept (is_nothrow_constructible<string>::value)
    
    // (5) 이걸 만들어야 resize( ) 를 할 때 이동 생성자를 부름
	People(People&& p) noexcept (is_nothrow_constructible<string>::value)
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
	
    People p3 = move_if_noexcept(p2);   
    // 예외가 없을 때만 move, 예외가 있으면 복사. move 생성자에 noexcept 가 있는지 확인해야 함.
	// 따라서 std::vector< > 같은 것에 객체 넣을 때 noexcept를 넣지 않으면 효과가 없음.
	
	// move_if_noexcept 의 원리
	People p4 = is_nothrow_move_constructible<People>::value ? move(p3) : p3;
	
	cout << "------------" << endl;

	// default 생성자가 없으므로 임시 객체를 넘겨야 함.
	vector<People> v(3, People("kim", 5, "Seoul"));
	cout << "--------------" << endl;
    
    // 이때 People 객체의 move 생성자가 noexcept로 만들어 져야 함.
	v.resize(5, People("kim", 5, "Seoul"));
	cout << "--------------" << endl;
}
```


### 컴파일러가 만들어 주는 default move 생성자


* 규칙 
1. 복사 계열과 move 계열을 모두 제공하지 않으면 컴파일러가 모두 디폴트 버전을 제공해 준다.				

``` cpp
class Home {
	People p;
public:
	Home() : p("kim", 10, "seoul") {}

	// (2) 아래 복사 생성자를 만드는 순간, 컴파일러는 move 생성자를 만들어 주지 않음.
	// 그래서 Home h3 = move(h1)을 불러도, 아래 복사 생성자가 있으면 move에 대해 복사 생성자를 부르게 된다.
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
```

### rule of 0


* 자원 관리는 직접 하는 코드는 만들지 말자.
1. const char* => string
2. int* buff => vector;
3. 그래도 포인터가 필요하면 => 스마트포인터 사용

``` cpp
// 동적으로 할당하는 자원이 없으니 코드가 간결해 진다.
class People {
	string		name;
	string		addr;
	int			age;
public:
	People(string n, int a, string ad) : name(n), age(a), addr(ad) {
		
	}
	~People() {
	}
};

int main()
{
	People p("kim", 10, "seoul");
}
```

### std::pair< > 를 만들어 보자

* C++11 이전 : 생성자 (함수 인자)로 const T&를 주로 사용
* C++11 이후: move 지원을 위해 2개의 생성자를 추가로 만들어야 함.
1. const T&
2. rvalue refence 버전: move 위해

``` cpp
template <typename T, typename U > struct PAIR {
	T first;
	U second;
	PAIR() = default;

	// (1) 생성자를 만들어 보자
	// rvalue, lvalue 모두 받기 위해 const를 붙인다.
	PAIR(const T& a, const U& b) : first(a), second(b) {
	}
	
	// (3) move를 위해서 새로 만듬
	PAIR(T&& a, U&& b) : first(move(a)), second(move(b)) {
	}
};

int main()
{
	PAIR<int, int> p1(3, 4); // move 생성자 불림

	string s1 = "hello";
	string s2 = "world";
	PAIR<string, string> p2(s1, s2);  // 복사 생성자 불림

	// (2) move 하더라도 생성자의 타입이 const를 받기 때문에 복사가 됨
	PAIR<string, string> p3(move(s1), move(s2));  // move 생성자 불림
	cout << s1 << endl;
}
```

### C++11 이전과 C++11 이후의 비교

> C++11 이후에는 성능 향상을 위해 move 연산도 꼭 만들어 줘야 함. 
``` cpp
class Data {

};

class Test {
	Data data;
public:
	// C++11 이전에는 아래 한개면 됨
	void SetData(const Data& d) {	data = d;	}

	// C++11 이후에는 아래처럼 move 지원하는 것도 만들어 줘야 함
	void seData(Data&& d) { data = move(d); }
};

int main()
{
	vector<string> v;
	string s1 = "Hello";

	v.push_back(s1);
	cout << s1 << endl;  // Hello 출력

	v.push_back(move(s1));
	cout << s1 << endl;   // Hello 출력 안됨
}
```