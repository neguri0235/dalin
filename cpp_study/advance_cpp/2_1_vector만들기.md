## Typehelper를 만들어 보자
> 오픈 소스에 있는 
[Typehelper.h](https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/include/utils/TypeHelpers.h) 를 만들어 보려고 함.

``` cpp
template<typename TYPE>
typename std::enable_if<traits<TYPE>::has_trivial_copy>::type
inline
copy_type(TYPE* d, const TYPE* s, size_t n) {
	memcpy(d, s, n * sizeof(TYPE));
}

template<typename TYPE>
typename std::enable_if<!traits<TYPE>::has_trivial_copy>::type
inline
copy_type(TYPE* d, const TYPE* s, size_t n) {
	while (n > 0) {
		n--;
		new(d) TYPE(*s);
		d++, s++;
	}
}
```

### 메모리 할당과 생성자 호출을 분리


> 일반적으로 사용하는 new, delete 기법
``` cpp
class Point {
	int x, y;
public:
	Point(int a = 0, int b = 0) :x(a), y(b) {
		cout << "Point()" << endl;
	}
	~Point() { cout << "~Point()" << endl; }
};

int main()
{
	// 1. 메모리를 할당
	// 2. 생성자를 호출
	Point* p1 = new Point(1, 2);

	// 1. 소멸자 호출
	// 2. 메모리 해지
	delete p1;
}
```   
  
> `operator new`와 new( ) 를 사용해서 메모리 할당과 생성자 호출을 분리
``` cpp
int main()
{
	// 메모리 할당과 생성자 호출의 분리
	// 1. 메모리 할당 . C의 malloc 과 유사 (생성자는 불리지 않음)
	Point* p2 = static_cast<Point*>(operator new(sizeof(Point)));
	cout << p2 << endl;

	// 2. 할당된 메모리에 생성자 호출 - Placement new 라는 기술임
	// new Point(1, 2); 메모리 할당 +  생성자 호출		
	new (p2) Point(1, 2);   // 생성자만 호출

	// 3. 소멸자만 호출
	p2->~Point();  // 메모리 해지 없이 소멸자만 호출. 
    // 하지만 생성자는 p2->Point(1,2) 처럼 못 부름.
	
	// 4. 소멸자 호출 없이 메모리만 해지
	operator delete(p2);
}
```

> 언제 그리고 왜 사용해야 하나 ?  
> -> default 생성자가 없는 객체를 여러개 만들때 사용
``` cpp
int main()
{
	// (1) Point 객체를 힙에 한개 만들기 (가능하다!)
	Point* p1 = new Point(0, 0);
	
    // (2) 힙에 10개 만들기 ? (불가능)
	Point* p2 = new Point[10];  // 생성자를 부를 수가 없다. (error 발생)
	
    // (3) 해결 방법 =>
	// 디폴트 생성자가 없는 객체를 여러개 생성하려면,
	// 메모리 할당과 생성자 호출을 분리

	// 1. 메모리 할당
	Point* p2 = static_cast<Point*>(operator new (sizeof(Point) * 10));
	// 2. 생성자 호출
	for (int i = 0; i < 10; i++) {
		new(&p2[i]) Point(0, 0);
	}

	//  사용 후 소멸자 호출의 파괴
	for (int i = 0; i < 10; i++) {
		p2[i].~Point();
	}
	operator delete(p2);

	// 단 메모리 해지 할때, 아래처럼 사용하면 알수 없는 동작을 하게 됨
	// delete []p2; 
}
```


### vector를 만들어 보자 (1)

> 메모리 할당과 생성자 호출을 분리하여 vector를 만들면, 
``` cpp
template<typename T> class vector {
	T* buff;
	int sz;
public:
	
	// value를 받지만, 혹시 안주면 T의 default 값을 사용 : zero initialization 이라고 부름
	// T 가  primitive 또는 포인터이면  : 0
	//           user type이면 디폴트 생성자

	vector(int s, T value = T()) : sz(s) {
		
		// 1. 이렇게 컨테이너를 만들면, 안됨. 디폴트 생성자 없으면 동작 안함
		// 결국 컨테이너 생성 시 요구 조건 및 제약이 많아 짐
		//buff = new T[sz];

		// 2. 따라서 이렇게 만들어야 함 (메모리 할당만 먼저 해야 함)
		buff = static_cast<T*>(operator new(sizeof(T)*s));

		// 3. 할당된 메모리에 생성자 호출
		// 하지만 T 가 어떤 타입인지 모르니 어떤 생성자를 부를 수 없음.
		// -> 복사 생성자를 부르는 것이 기본 조건

		// 4. 메모리 할당 및 생성자 호출 시 예외 상황 발생시 자원해제를 하도록 함
		int cnt = 0;

		try {
			for (int i = 0; i < sz; i++) {
				// new (&buff[[i]) T;	// 디폴트 생성자 부르면 에러 발생
				new(&buff[i])T(value);  // 복사 생성자
				cnt = i;
			}
		}
		catch (...) {
			// 생성자 호출에 성공한 객체는 다시 소멸자 호출하여 예외 상황 처리
			for (int i = 0; i < cnt; i++) {
				buff[i].~T();
			}
			operator delete(buff);
		}
	}

	~vector(){
		for (int i = 0; i < sz; i++) {
			buff[i].~T();
		}
		operator delete(buff);
	}
};

int main()
{
	vector<int> v(10);
	Point pt(0, 0);
	vector<Point> p(10, pt);        // a. 명시적으로 객체를 전달 하거나
    vector<Point> p(10, {10,20});   // b. 임시 객체를 전달 하거나
}
```

> `uninitialized_fill_n` 함수를 제공하기 때문에, 이 함수로 생성자 호출
``` cpp
template<typename T> class vector {
	T* buff;
	int sz;
public:
	vector(int s, T value = T()) : sz(s) {
		buff = static_cast<T*>(operator new(sizeof(T)*s));
		try{
			std::uninitialized_fill_n(buff, sz, value);
		}
		catch (...) {
			operator delete(buff);
		}
	}

	~vector() {
		for (int i = 0; i < sz; i++) {
			buff[i].~T();
		}
		operator delete(buff);
	}
};

int main()
{
	Point pt(0, 0);
	vector<Point> p(10, pt);
	vector<Point>p2(10, { 0,0 });
}
```

### vector를 만들어 보자 (2)
  
> [ ] 연산을 가능하도록 해 보자
``` cpp
template<typename T> class vector {
	T* buff;
	int sz;
public:
	vector(int s, T value = T()) : sz(s) {
		buff = static_cast<T*>(operator new(sizeof(T)*s));
		std::uninitialized_fill_n(buff, sz, value);
	}
	~vector() {
		for (int i = 0; i < sz; i++) {
			buff[i].~T();
		}
		operator delete(buff);
	}

	// (3) 연산자를 재정의 해보자
	// T operator[] (int idx) 
    // -> 값을 반환하면 안됨. 값을 반환하면 , v[0] = 0; 같은 연산을 할 수 없기 때문에
    // 참조를 반환해야 함
		T& operator[] (int idx) {
		return buff[idx];
	}
};

int main()
{
	vector<int> v(10);
	// (1) vector 처럼 사용하려면, [ ] 연산이 되어야 함
    // (2) 결국 연산자 재정의를 해야 하는 상황
    // v.operator[](0) = 100; 과 같은 코드 임.
	v[0] = 100;			
	cout << v[0] << endl;
}
```

### vector를 만들어 보자 (3)

> bool을 저장해 보자  
> (3) 문제를 해결하는 것이 목적
``` cpp
// 위에서 만든 vector< >와 동일
template<typename T> class vector {
...
public:
...
};

// bool을 위한 template 특수화 같은 것을 만듬
template<> class vector <bool> {
	int* buff;
	int sz;
public:
	vector(int s, bool value = false) : sz(s) {
		// (2) bit 개수만큼 메모리 할당 32개 미만이면 int 1개,
        int cnt = sz / 32 + 1;
		buff = static_cast<int*>(operator new(sizeof(int)*cnt));
		// buff 부터 sz 비트를 value로 채우기 (초기화 과정 생략)
	}
	~vector() {
		operator delete(buff);
	}

	// (3) bit를 반환해야 하는데 어떻게 반환할 수 있을까???
	?& operator[] (int idx) {
		return buff[idx];
	}
};

int main()
{
	// (1) bool을 int type에 30개 공간에 저장하기엔 메모리 낭비가 있다.
    // bit로 만들면 30개 공간이라도 int 크기 만큼인 4byte 면 충분
	vector<bool> v1(30);
}
```

> `BitProxy` 클래스를 만들자.
``` cpp
// 위에서 만든 vector< >와 동일
template<typename T> class vector {
...
public:
...
};

// bool 타입을 위한 특수화 ( template specialization )
template<> class vector <bool> {
	int* buff;
	int sz;
public:

	vector(int s, bool value = false) : sz(s) {
		int cnt = sz / 32 + 1;
		buff = static_cast<int*>(operator new(sizeof(int)*cnt));
		// buff 부터 sz 비트를 value로 채우기
	}
	~vector() {
		operator delete(buff);
	}
	// (1) []  연산자에서 각 비트를 반환하기 위해 만드는 'helper' class
	class BitProxy {
		int*	buff;
		int		idx;
	public:
		BitProxy(int* p, int n) : buff(p), idx(n) {	}
		
		BitProxy& operator=(bool value) {
			// buff 주소의 idx 비트를 value로 채웁니다.
			cout << idx << " 비트 " << value << " 채우기" << endl;
			return *this;
		}

		operator bool() {
			// 연산 필요하지만, 여기서는 구현 안함.
			return true;
		}
	};

	// (2) 핵심 : Proxy 객체를 임시 객체로 반환한다.
	BitProxy operator[] (int idx) {
		return BitProxy(buff, idx);
	}
};

int main()
{
	vector<bool> v2(30);
	v2[10] = true;	// (3) BitProxy에 대입 연산자가 있어야 한다.
	bool n = v2[0];	// BitProxy는 bool 로 암시적 변환이 되어야 함. (객체가 bool로 변환)
									// operator bool( ) 필요
	cout << n << endl;
}
```

> `BitProxy`의 타입은 무엇인가? 
``` cpp
int main()
{
	
	vector<bool> v2(10);
    auto a2 = v2[0];

	cout << typeid(a2).name() << endl;

	// 핵심 1
	// modern effective c++. vector<bool> 이 반환하는 것은 bool 이 아님.
	/*
	class std::_Vb_reference<struct std::_Wrap_alloc<class std::allocator<unsigned int> > >
	*/

	for (auto a : v1) 
		cout << a << endl;

	// 핵심 2: range for 를 사용하면, auto& 사용 못함. 왜냐면 임시 객체이므로
    // 임시 객체는 &를 사용할 수 없음. 대신 && 는 가능
	// 컨테이너가 temporary(rvalue)를 반환하는 경우가 있음. auto&&(forwarding reference)가 좋음
	//for (auto& a : v2)  // error
	for (auto&& a : v2)
		cout << a << endl;
}
```