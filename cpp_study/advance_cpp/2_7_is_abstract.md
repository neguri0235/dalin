## 평가되지 않는 표현식

``` cpp
/*
(1) 실행안되는 함수. 구현부가 필요한가?
int foo(int a) {
	cout << "foo" << endl;
	return 0;
}
*/
// (2) 이렇게 함수 바디가 없이 선언만 있어도 실행이된다.
int foo(int a);

int main()
{
	int n = 0;
	cout << sizeof(n) << endl;			// 4 byte
	cout << sizeof(&foo) << endl;		// 주소의 크기 32bit 환경 4
	//cout << sizeof(foo) << endl;		// error. 함수가 사용하는 코드 메모리는 구할 수 없다
	cout << sizeof(foo(n)) << endl;	// 반환값의 크기. "foo" 라고 출력되지 않음. (평가되지 않음)
}
```

* 평가되지 않는 표현식 (unevaluated expression)   
  -> 함수 호출식이 실제로 함수를 호출하지 않는 것
1. sizeof(foo(0));
2. decltype(foo(0)) m;  // foo(0) 호출 후 반환하는 타입과 같은 타입의 m
3. const type_info& r = typeid(foo(0));   // 
4. bool b = noexcept(foo(0));   // 예외 가능성이  없으면 true, 있으면 false


### is_abstract (1)

> 표준 함수를 사용해 보자
``` cpp
class Shape {
	virtual void Draw() = 0;
};

int main()
{
    // Shape class에 가상 함수가 있으면 true를 반환
	cout << is_abstract<Shape>::value << endl;
}
```

### is_abstract (2)
> 한번 만들어 보자

* 추상 클래스
1. 객체는 만들 수 없다
2. 포인터 변수는 만들 수 있다.
3. 배열을 가르키는 포인터는 만들 수 없다.


``` cpp
class Shape {
	virtual void Draw() = 0;
};

// 1. 조건을 만족하는 경우에만 함수를 호출
// 배열 타입이므로, 여기로 들어오면 추상 클래스가 아님. 즉 int 형 반환형은 추상 클래스가 아님
template<typename T> int check(T(*)[1] ); 
template<typename T> char check(...);

int main()
{
	if (sizeof(check<Shape>(0)) == sizeof(int))) {
		cout << "추상 아님" << endl;
	}
	else {
		cout << "추상" << endl;
	}
}
```

> 좀더 표준 처럼 만들어 보자
``` cpp
class Shape {
	virtual void Draw() = 0;
};

/*
template<typename U> struct xis_abstract {
	template<typename T> static char check(T(*)[1]);  // static 붙이는 이유는 멤버 함수 이므로 객체 없이 부르기 위해
	template<typename T> static int check(...);

	static constexpr bool value = (sizeof(check<U>(0)) == sizeof(char));
};
*/

//  int 와 char 이 크기가 같은 수 있으므로( int는 char보다 크거나 같다), int 와 char로 구분하지 말고, 배열 크기로 구분하자

template<typename U> struct xis_abstract {
	typedef char YES[1];
	typedef char NO[2];

	template<typename T> static NO& check(T(*)[1]);  
    // static 붙이는 이유는 멤버 함수 이므로 객체 없이 부르기 위해(그냥 C++문법)
	template<typename T> static YES& check(...);

	static constexpr bool value = (sizeof(check<U>(0)) == sizeof(YES));
};

int main()
{
	cout << xis_abstract<Shape>::value << endl;
}
```

### C++ 표준에서는
``` cpp
class Test {
public:
	Test(int n) {}
	void resize(int n ) {}
};

template<typename T> T xdeclval();  // declval 이 표준임. 핵심 구현이 없음.
// T&& 이 맞는 표현임
// https://en.cppreference.com/w/cpp/utility/declval


template<typename U> struct has_resize_function {
	typedef char YES[1];
	typedef char NO[2];

    // (1) T() 는 default 생성자가 있어야 함.그래서 T()를 사용하지 않고
    // declval을 사용함
	
	// template<typename T> static YES& check(decltype(T().resize(0) )* n);  (2)
	// template<typename T> static YES& check(decltype(T().resize(0) )* n);  
    // * 를 붙이는 이유는 void 타입이 들어올 경우를 대비해서 (void는 없지만 void* 타입은 존재)
	
    
    template<typename T> static YES& check(decltype(xdeclval<T>().resize(0))* n);
	template<typename T> static NO& check(...);

	static constexpr bool value = (sizeof(check<U>(0)) == sizeof(YES));
};

int main()
{
	cout << has_resize_function<vector<int> >::value << endl;
	cout << has_resize_function<Test>::value << endl; // (3) Test의 경우 default 생성자가 없어서 0 이 나옴
}
```