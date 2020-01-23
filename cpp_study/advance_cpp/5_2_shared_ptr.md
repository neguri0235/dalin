``` cpp
// 1. 헤더파일
#include <memory>

int main()
{
	// 2 . 생성자가 explicit 이므로 = 로는 초기화가 안됨
	//shared_ptr<int> sp1 = new int; // error
	shared_ptr<int> sp2(new int); // ok

	// 3. 크기 : 대부분의 구현에서 raw pointer * 2
	cout << sizeof(sp2) << endl;

	// 4. -> 와 . 연산
	shared_ptr<Car> sp3(new Car);
	
	// -> : 대상체의 함수
	sp3->Go();
	(*sp3).Go();

	// . : shared_ptr 자체의 멤버 함수
	int n = sp3.use_count();  // 참조 계수 꺼내기
	cout << n << endl;

	Car* p = sp3.get(); // raw pointer 꺼내기
	
	sp3.reset();  // if(--참조계수 == 0) delete; obj = nullptr;
}

```

> 삭제자의 선언
``` cpp
class Point {
public:
	Point() { cout << "Poit()" << endl; }
	~Point() { cout << "~Poit()" << endl; }
};

void foo(void* p) { cout << "foo" << endl; free(p); }

int main()
{
	// 삭제자 변경
	// new 가 아닌 다른 함수로 메모리 할당한 경우
	// 삭제자를 관리하는 포인터도 필요

	shared_ptr<int> p1(new int);	// p1 소멸자에서 delete
	//shared_ptr<void> p2(malloc (100)); // new 가 아니니 free를 호출해야 함. 그래서 별도로 삭제하는 코드를 만들어야 함
	shared_ptr<void> p3(malloc (100),foo); 
	shared_ptr<void> p4(malloc (100),free); 
	shared_ptr<void> p5(malloc(100), [](void* p) {free(p);});

	// 배열 모양으로 할당
	//shared_ptr<int> p6(new int[10]);// 버그임. delete[] 가 필요
	shared_ptr<int> p6(new int[10], [](int* p) {delete[] p; }); 

	// default_delete<int> : delete 를 수행하는 함수 객체
	// default_delete<int[]> : delete[]
	shared_ptr<int> p7(new int[10], default_delete<int[]>());
	
	// 공식적으로  C++ 17에서 부터 지원
	shared_ptr<int[]> p8(new int[10] );


	shared_ptr<Point[]> p9(new Point[3]);

	// Point* pt = new Point[3];		// 생성자 3번 호출
	// delete  pt;			// 소멸자 한번 호출

	// file open도 처리할 수 있음
	shared_ptr<FILE> sp1(fopen("a.txt", "wt"), fclose);
}

```
``` cpp
#include <iostream>
#include <memory>

using namespace std;

class Point {
	int x, y;
public:
	Point(int a = 0, int b = 0) { cout << "Point()" << endl; }
	~Point() { cout << "~Point()" << endl; }
};

// (2) new를 재정의해서 얼만큼 할당하는지 확인하자
void* operator new(size_t sz) {
	cout << "new: " << sz << endl;
	return malloc(sz);
}

// (5) make_shared 의 원리를 생각해 보자
// 가능한 구현의 예는 아래와 같다.
/*
template<typename T,  typename ... ARGS> 
shared_ptr<T> xmake_shared(ARGS&& ... args) {
	void* p = operator new(sizeof(T) + sizeof(관리객체));

	// 객체 생성자 호출
	new (p) T(std::forward<ARGS>(args) ...);

	// 관리객체 생성자 호출
	shared_ptr<T> sp;
	sp.reset(p, ((char*)p) + sizeof(T));
	return sp;
}
*/

int main()
{
	// (1) 아래 코드는 동적 메모리 할당을 몇번 하게 될까요? 
	// (3) 2번 할당됨 : 객체 할당  + 관리 객체(ref counter 등) 할당
	shared_ptr<Point> sp1(new Point(1, 2));
	cout << "---" << endl;

	// (4) 메모리를 한번에 할당. 메모리 파편화 현상이 줄어듬
	shared_ptr<Point> sp2 = make_shared<Point>(1, 2);

	// make_shared 장점
	// 1. 객체 + 관리 객체를 한번에 할당하므로 "메모리 파편화" 현상이 줄어든다.
	// 2. 안전하다

	foo(shared_ptr<int>(new int), goo());
	// 1. new int
	// 2. goo()
	// 3. shared_ptr 만들기 
	// 순서로 실행되다가 goo에서 예외 나오면 메모리 누수

	foo(make_shared<int>(), goo());  // 메모리 누수가 없다.

	foo(new int, goo()); //안좋은 코드
	// 그래서 shared_ptr<int.> = new int;를 하지 못하는 이유
}
int goo() { return 0; }
void foo(shared_ptr<int> sp, int n) {}

```
``` cpp

```


``` cpp
```
``` cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct People {
	string name;
	People() = default;
	People(string n) : name(n) { }
	~People() { cout << name << " 파괴" << endl; }
	// shared_ptr<People> bestFriend;  // -> 일반 포인터로 변경

	// 멤버 데이타는 수명에 관계 하지 않는다.
	// People* bestFriend;

	weak_ptr<People> bestFriend;
	// 참조 계수가 증가하지 않는 스파트 포인터. 
	// 객체 파괴 여부 조사 가능
};

int main()
{

	shared_ptr<People> sp1 = make_shared<People>("Kim");
	{
		shared_ptr<People> sp2 = make_shared<People>("Lee");

		sp1->bestFriend = sp2;  // weak는 shared와 호환
		sp2->bestFriend = sp1;
	}

	if (sp1->bestFriend.expired()) {   // expired() 로 판단 가능
		cout << "객체 파괴됨" << endl;
	}
```
``` cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct People {
	string name;
	People(string n) : name(n) { }
	~People() { cout<< name << " 파괴" << endl; }
	weak_ptr<People> bestFriend;
};

int main()
{
	shared_ptr<People> sp1;
	weak_ptr<People> wp1;

	shared_ptr<People> sp2 = make_shared<People>("Kim");

	// sp1 = sp2; // 참조 계수 2
	wp1 = sp2;  // 참조 계수 증가 안함. 
	cout << sp2.use_count() << endl;

	//---------------------
	shared_ptr<People> sp3 = make_shared<People>("lee");
	shared_ptr<People> sp4 = sp3;
	weak_ptr<People> wp4 = sp3; 

	// 아래 코드는 안전한가? 
	string s1 = sp4->name;   // sp가 살이 있는 동안 객체는 파괴될 수 없다. 
								// dangling 포인터가 나올 수 없다. 
	
	//string s2 = wp4->name; 	// error. wp4가 살아 있다고 해도 객체가 살아 있다는 보장이 없음
	// 그래서 -> 와 *  =연산자가 재정의 되어 있지 않다.
	
	// wp에 접근하려면,  참조 계수를 올리고서 접근해야 한다.
	// 참조 계수를 올리는 방법은 "shared_ptr"을 만들어야 한다.

	shared_ptr<People> sp5 = wp4.lock();  // lock 하는 도중에 sp3의 소멸자는 안불림.
	if (sp5) {
		string s3 = sp5 -> name;
	}
}

```

``` cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct People {
	string name;
	People() = default;
	People(string n) : name(n) { }
	~People() { cout << name << " 파괴" << endl; }
	// shared_ptr<People> bestFriend;  // -> 일반 포인터로 변경

	// 멤버 데이타는 수명에 관계 하지 않는다.
	// People* bestFriend;

	weak_ptr<People> bestFriend;
	// 참조 계수가 증가하지 않는 스파트 포인터. 
	// 객체 파괴 여부 조사 가능
};

int main()
{

	shared_ptr<People> sp1 = make_shared<People>("Kim");

	shared_ptr<People> sp2 = make_shared<People>("Lee");

	sp1->bestFriend = sp2;  // weak는 shared와 호환
	sp2->bestFriend = sp1;


	if (sp1->bestFriend.expired()) {   // expired() 로 판단 가능
		cout << "객체 파괴됨" << endl;
	}
	else {
		// 살아 있는 경우
	//	cout << sp1->bestFriend->name << endl;  // error
		// weak에는 -> 가 없음
		shared_ptr<People> sp = sp1->bestFriend.lock();
		if (sp) {
			cout << "* 1 " << sp->name << endl;
		}
	}
}
```

``` cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct People {
	string name;
	People() = default;
	People(string n) : name(n) { }
	~People() { cout << name << " 파괴" << endl; }
	// shared_ptr<People> bestFriend;  // -> 일반 포인터로 변경

	// 멤버 데이타는 수명에 관계 하지 않는다.
	// People* bestFriend;

	weak_ptr<People> bestFriend;
	// 참조 계수가 증가하지 않는 스파트 포인터. 
	// 객체 파괴 여부 조사 가능
};

int main()
{
	shared_ptr<People> sp = make_shared<People>("Kim");
	
	shared_ptr<People> = new (People)("Kim");
	weak_ptr<People> = sp;
}

// 관리 객체는 아래 4개의 정보를 가짐
// 1.  객체 수정
// 2. 객체 주소
// 3. weak ptr counter
// 4.  삭제자

// 그래서 shared ptr의 관리 객체가 제거 되는 시점은 weak ptr이 제거 될때임.
// 왜냐면 weak ptr에서 use_count 같은 것을 불러야 하기 때문. 
```

``` cpp
int main()
{
	int* p1 = new int;

	shared_ptr<int> sp1(p1);  // 관리 객체 생성
	shared_ptr<int> sp2(p1); // 다른 관리 객체 또 생성

	// 핵심 : 자원을 획득한 후에, 자원의 포인터를 자원 관리 객체에 넣으면 안됨

	// 자원의 획득은 자원 관리 객체가 만들어 질때 동시에 해야함
	shared_ptr<int> sp3(new int);  // 이렇게 하는것이 좋음. 즉 make_shared를 써야 함

	//  RAII : Resource Acquision Is Initialization.
}
```

``` cpp
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 상속 받을 때 자기 이름 보내는 것. CRTP
class ConnectDB :  public enable_shared_from_this<ConnectDB> {

	// 스레드를 사용하는 클래스가 있다면
	// 자신의 수명을 스레스가 종료될 때 까지 유지해야 한다
	// 자신을 가리키는 스마트 포인터가 있어야 한다.
	shared_ptr<ConnectDB> holdMe;

public:
	// 문제점 1. this는 raw pointer이므로 관리 객체가 따로 생성됨
	// 문제점 2.생성자에서는 스레드가 생성되기 전이다. 참조 계수가 증가될 필요 없다.
	/*
	ConnectDB() : holdMe(this) {
	}
	*/

	void start() {
		// holdMe = this; // error. 

		holdMe = shared_from_this(); // 외부에서 만들었던 관리 객체를 공유하게 해준다.

		thread t(&ConnectDB::Main, this);
		t.detach();
	}

	virtual void Main() {
		
		// (2) 그래서 이렇게 함.
		shared_ptr<ConnectDB> sp(holdMe);
		holdMe.reset();

		this_thread::sleep_for(3s);
		cout << "DB접속" << endl;
		// 멤버 데이타 사용중


		 holdMe.reset();  // << 이걸 제거하고 테스트해보면 차이를 확인 가능
				// (1) 이렇게 하면 위쪽에서 예외 발생시 수행못됨. 
	}
	~ConnectDB() {
		cout << "파괴" << endl;
	}
};

int main()
{
	{
		shared_ptr<ConnectDB> p(new ConnectDB);
		p->start();
		// (1) 여기 빠져나가면 제거됨. 나중에 문제 발생
	}
	
	getchar();
}

/*
https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/include/utils/Thread.h
	
	volatile bool           mRunning;
			sp<Thread>      mHoldSelf;

https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/Threads.cpp

int Thread::_threadLoop(void* user)
{
	Thread* const self = static_cast<Thread*>(user);

	sp<Thread> strong(self->mHoldSelf);
	wp<Thread> weak(strong);
	self->mHoldSelf.clear()

*/
```
``` cpp
```
``` cpp
```
``` cpp
```
