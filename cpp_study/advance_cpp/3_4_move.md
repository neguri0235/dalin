### 복사 생성자
``` cpp
class Point {
	int x, y;
public:
	Point(int a = 0, int b = 0) : x(a), y(b) {}
	
	// 복사 생성자 모양 
    // 1. call by value
	// 이렇게 만들 수 없음. 재귀적으로 무한히 복사하게 됨
	// 인자가 넘어갈때 복사가 되고, 다시 복사 생성자 불리고, 다시 복사 , 다시 복사 생성자..무한 반복
	// Point(Point pt) {} << 무한 반복하는 복사 생성자임.

	// 복사 생성자 모양 
    // 2. call by reference
	// 사용 가능. 에러 없음
	// 단점: rvalue를 받을 수 없다.
	// 혹은 값을 반환하는 함수의 반환값을 받을 수 없다. (factory pattern같은)
	Point(Point&) {}

	// 3. 복사 생성자 모양  call by const lvalue reference
	// lvalue 뿐 아니라 rvalue 모두 받을 수 있다.
	Point(const Point& pt) : x(pt.x), y(pt.y) {}
};

Point foo() {
	Point p;
	return p;
}

int main()
{
	Point p1;			// 디폴트 생성자 (인자없는 default 값으로 생성)
	Point p2(1, 2);		// 인자 2개인 생성자
	Point p3(p2);		// Point(Point)의 생성자 필요
	Point p4(Point(0,0));	// Point(Point)의 생성자 필요
    
    // foo에서 리턴되는 값은 임시 객체, rvalue. 
    // 2번 복사	생성자로는 이 코드를 처리 못함.
	Point ret = foo();
}
```

### 깊은 복사를 해야 하는 이유

``` cpp
1. 클래스 안에 포인터 변수가 있으면 얕은 복사 현상이 있음.
2. 반드시 복사 생성자를 사용자가 만들어야 한다.

class Buffer {
	int* resource;
	int size;
public:
	Buffer(int sz) : size(sz) { resource = new int[sz]; }
	~Buffer() { delete[] resource; }

	// (3) 깊은 복사를 하는 복사 생성자 만들기
    // 깊은 복사를 하는 복사 생성자를 사용자가 만들어 주면 소멸자 호출 시 문제 없음
    // 컴파일러가 생성해 주는 복사 생성자는 얕은 복사를 하게 됨
	Buffer(const Buffer& b) : size(b.size) {
		resource = new int[size];
		memcpy(resource, b.resource, sizeof(int)*size);
	}
};

int main()
{
	Buffer b1(1024);
	// (1) 이순간 얕은 복사가 됨
    Buffer b2 = b1;  
    // (2) 소멸자 호출 과정에서 프로그램 종료 됨
}
```

#### 이동 생성자

> 객체의 종류에 따라 서로 다른 복사/이동 생성자가 호출됨


1. C++11 이전에는 복사 생성자만 있었음.  
   이름 있는 객체나 없는 객체나 동일한 알고리즘 사용

2. C++11 이후 : 임시객체일때 복사하는 방법  
이름 있는 객체일때와 복사하는 방법을 분리해서 최적화하자.


``` cpp
class Buffer {
	int* resource;
	int size;
public:
	Buffer(int sz) : size(sz) { resource = new int[sz]; }
	~Buffer() { delete[] resource; }

	Buffer(const Buffer& b) : size(b.size) {
		resource = new int[size];
		memcpy(resource, b.resource, sizeof(int)*size);
		cout << "복사 생성자" << endl;
	}

	// (2) 인자로 임시객체가 올때는 메모리를 통째로 복사할 필요가 없다.
	// 주소만 복사해오면 된다. 왜냐면, 원본 객체를 더이상 사용하지 않으므로.
	Buffer( Buffer&& b) : size(b.size) {  // <------(3)
		resource = b.resource;
		// 이전 주소 포인터에 0을 넣어야 하므로, const를 빼야 함.
        b.resource = 0;  
		cout << "이동 생성자" << endl;
	}
};

Buffer foo() {
	Buffer buf(1024);
	return buf;
}

int main()
{
    // (1) 임시 객체인 경우만, 얕은 복사가 필요
	Buffer ret = foo();
	cout << "----" << endl;
	Buffer b1(1024);
	cout << "----" << endl;
	Buffer b2 = b1;
}
```

### std::move( )

> move 연산이 좋기는 한데, const 객체는 move를 할 수 없음.
> 
``` cpp
class Buffer {
	int* resource;
	int size;
public:
	Buffer(int sz) : size(sz) { resource = new int[sz]; }
	~Buffer() { delete[] resource; }

	Buffer(const Buffer& b) : size(b.size) {
		resource = new int[size];
		memcpy(resource, b.resource, sizeof(int)*size);
		cout << "복사 생성자" << endl;
	}


	Buffer(Buffer&& b) : size(b.size) {
		resource = b.resource;
		b.resource = 0; 
		cout << "이동 생성자" << endl;
	}
};

Buffer foo() {
	Buffer buf(1024);
	return buf;
}

int main()
{
{
	Buffer ret = foo();	 // move
	Buffer b1(1024);
	Buffer b2 = b1;		 //copy
							 
    //Buffer b3 = b2;	 // (1) 이 시점에 더이상 b2가 필요 없음. move 연산이 더 좋다.
	Buffer b3 = static_cast<Buffer&&>(b2); // (2) move연산하기 위해서 b2를 rvalue로 캐스팅
	Buffer b4 = std::move(b3);	 // (3) 위와 같은 casting을  move 안에서 처리하고 있음(표준 방식)

	const Buffer cb(1024);

	Buffer b5 = cb;	 // const 객체 이므로 복사 생성
	
    // (4) 빌드 에러. const 속성에서 변환 불가
    //Buffer b6 = static_cast<Buffer&&>(cb); 
	
    // (5) 복사를 부름. && 로 캐스팅하지만 const가 있어서 복사를 호출
    Buffer b6 = static_cast<const Buffer&&>(cb); 

	Buffer b7 = static_cast< const Buffer&&>(cb); // (6) 복사를 부름.
	Buffer b8 = std::move(cb);   // 복사 생성자

	// 결론 : const 객체는 move 될 수 없다.
}
```

### STL에서 move 를 사용하는 경우

> const 객체는 std::move가 동작하지 않음
``` cpp
int main()
{
    // (1) const 객체는 move해도 자원을 그대로 가지고 있음
	const string s1 = "hello";	
	
    string s2 = std::move(s1);
	cout << s1 << endl;  // "hello" 출력됨

	vector<int> v1(10, 3);
	//vector<int> v2 = v1;			// (2) 느림
	vector<int> v2 = std::move(v1);	// (3) 빠름. 포인터만 전달

	cout << v1.size() << endl;
}
```


### 알고리즘 함수 제작과 move

> swap( ) 함수를 만든다고 할 경우, 복사는 속도 느림.
``` cpp
template <typename T> void Swap(T& a, T& b) {
	// 복사 생성자에 의한 swap - 느리다
	/*
	T tmp = a;
	a = b;
	b = tmp;
	*/
	// move 생성자에 의한 swap - 빠르다

	T tmp = std::move(a);
	a = std::move(b);  // move 대입 연산자.
	b = std::move(tmp);
}

int main()
{
    // Buffer 객체를 swap( ) 하고자 함.
	Buffer b1(1024);
	Buffer b2(1024);
	Swap(b1, b2);

	string s1 = "hello";
	string s2 = "world";
	Swap(s1, s2);
	cout << s1 << s2 << endl;

	int n = 10; 
	int n1 = static_cast<int&&>(n); // 컴파일 시점 캐스팅이므로 오버헤드 없음.
	int n2 = move(n);				// 동적할당된 자원이 없으니 빨라지는 것은 아님
}
```