### Traits

> `traits` 특질 :  타입의 다양한 속성을 조사하는 기술
``` cpp
template<typename T> void printv(T v) {
	// (1) 이런걸 할 수 있을 까? 
	if (T 가 포인터라면) {
		cout << v << ' ' << *v << endl;
	}
	else {
		cout << v << endl;
	}
}
```


#### traits 를 구현해 보자(1)

* T 가 포인터 인지 조사하는 기술
 1. 구조체 템플릿을 만든다
 2. enum 상수 value를 넣고 false로 초기화
 3. 해당 조건을 만족하는 부분 특수화 버전을 만들고 value = true로 변경

``` cpp
template<typename T> struct xis_pointer {
	enum { value = false }; // (1) 이렇게 만들거나 (예전 스타일)
	// bool value = true; 이렇게 하면 변수이기 때문에 컴파일 시점에 알수 없음.
	// 대신 enum 으로 사용하면 컴파일 할때 알 수 있음. 하지만 c++11 이전 스타일
	static constexpr bool value = false; // (2) c++11 스타일로 만들거나
};

template<typename T> struct xis_pointer <T*>{
	enum { value = true };
};

template<typename T> void foo(T a) {
	if (xis_pointer<T>::value) {
		cout << "포인터입니다." << endl;
	}
	else {
		cout << "포인터가 아닙니다" << endl;
	}
}
```

#### traits 를 구현해 보자 (2)
> 변수 템플릿을 이용
``` cpp
template<typename T> struct xis_reference {
	static constexpr bool value = false;
};

template<typename T> struct xis_reference <T&> {
	static constexpr bool value = true;
};

template<typename T> struct xis_reference <T&&>{
	static constexpr bool value = false;
};


int main()
{
	cout << xis_reference<int>::value << endl;		// false
	cout << xis_reference<int&>::value << endl;	// true
}
```

> 그런데 복잡해서 보기 안좋음. 그래서 variable template(변수 템플릿)을 사용함.  
> std:: 표준 함수를 보다보면 _v 가 붙은 함수들이 보이는데, 변수 템플릿을 사용한 것임

``` cpp
template<typename T> 
bool xis_reference_v = xis_reference<T>::value;

int main()
{
	cout << xis_reference<int>::value << endl;		// false
	cout << xis_reference<int&>::value << endl;	    // true
	cout << xis_reference_v<int&><< endl;	        // true
}
```


* Template은 4가지 종류가 있음.
1. template<typename T> class list {};						// 클래스 템플릿
2. template<typename T> void foo(T a) {} ;	// 함수 템플릿
3. template<typename T> using List = list<T>; // using 템플릿
4. template<typename T> bool v = xis_reference<T>::value // variable template (변수 템플릿)
v<int> // == xis_pointer<int>::value 와 같은 의미


### 표준에 정의된 traits
``` cpp
template<typename T> void foo(T a)
{
	bool b = std::is_array<T>::value;
	bool c = std::is_array_v<T>;
	// variable template은 c++14 부터 가능함
}

int main()
{
	int n = 10;
	foo(n);
	foo(&n);
}
```

### Typename
> 때때로 `typename`이란 키워드를 붙이는데, 
``` cpp
class AAA
{
public:
	typedef int DWORD;
	static int value;
};

int AAA::value = 0;

template<typename T> void foo(T t) {
	// (1) AAA 클래스 안에 있는 DWORD를 사용하는 것 : int n
	AAA::DWORD n;

	// (2) T 가 임의의 타입이라서 static 멤버 변수인지 typedef 인지 알 수 없음
	//T::DWORD b; 에러남.

	//(3) T::이름 => 무조건 static 변수로 해석
	// typename T:: 이름 => "이름"을 static 변수가 아닌 타입으로 해석해야 함.
	int n2 = T::value;
 
 	// (4) typename을 빼면 빌드 에러나 발생하고, typename이 반드시 필요함
	typename T::DWORD n3; 
}

int main()
{
	AAA	a;
	foo(a);
}
```

> vector< >에서 크기를 나타내는 타입의 최적은 ?
``` cpp
using namespace std;

template<typename T> class vector {
public:
	typedef unsigned int size_type;
	// (2) size( )라는 멤버 함수가 있어야 하고
	// size_type 이라는 것이 구현되어 있어야 함
	size_type size() const { return 10; }
};

//void foo(vector<int>&v) {
template<typename T> void foo(vector<int>&v) {
	// (1) ? 에 들어갈 최적의 타입은? 
	// ? = v.size();
	//vector<int>::size_type n = v.size();
	typename T::size_type n = v.size();
}

int main()
{
	vector<int> v(10);
	foo(v);
}
```

