## int2type

> 템플릿은 두번 컴파일 된다 (의미상 두번)

1. T와 관련 없는 부부의 오류를 조사한다.  
   (T와 관련이 있는 코드는 조사하지 않는다.)

2. 실제 사용하면 T 타입이 결정되고, 실제 함수(클래스)의 코드가 생성
   생성된 함수를 다시 컴파일(오류조사)한다.
``` cpp
template <typename T> void foo(T a){
	*a = 10;    // 오류 아님 : a의 type을 모름
	goo(a);     // 오류 아님 : a의 type을 모름
	goo();	    
    // 오류 : goo( )함수는 void param을 갖는 함수로 명확하니까 goo( )함수 구현부를 컴파일러가 찾으려고 함.
}
int main()
{
    // main 함수에서 foo( )를 호출하지 않고 있음.
}
```


> 데이터 타입에 따라 다른 함수를 호출 하고 싶다!
``` cpp

template<typename T> void printv(T v)
{
// (2) 빌드하면 아래에서 에러가 발생한다.
// 이를 해결하기 위한 3가지 방법이 있음.
// (3) 빌드 에러는 왜 날까?
// 아래 조건문은 if( false) 로 빌드가 되는데, 결국 실행 시점에 분기를 타게 됨
// 하지만 v 가 int인 경우 *v 로 역 참조를 할 수가 없음
	if (std::is_pointer<T>::value) {
		cout << v << " : " << *v << endl;
	}
	else {
		cout << v << endl;
	}
}

template<typename T> void printv(T v)
{
	if (std::is_pointer<T>::value) {
		cout << v << " : " << *v << endl;
	}
	else {
		cout << v << endl;
	}
}

int main()
{
	int n = 10;
	// (1) 아래 함수를 위한 printv( )함수를 만들 때 에러 발생
    printv(n);
	// (3) 이함수는 에러가 발생하지 않음
    printv(&n);
}
```

#### 해결책을 위한 단계 (1)
``` cpp
template<typename T> void printv_pointer(T v)
{
// (2) 결국 여기서 빌드 에러가 발생함.
// 컴파일러는 printv_pointer( ) 사용할지 안할지 모름
	cout << v << " : " << *v << endl;
}

template<typename T> void printv_not_pointer(T v)
{
	cout << v << endl;
}

template<typename T> void printv(T v)
{
    //(1) 분기 조건을 만들어서 pointer인 경우만 아래 라인을 실행 시키도록
	if (std::is_pointer<T>::value) {
		printv_pointer(v);
	}
	else {
		printv_not_pointer(v);
	}
}
int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
```

#### 해결책을 위한 단계 (2)
> 함수 오버로딩을 사용하자

``` cpp
template<typename T> void printv_imp(T v, YES)
{
	cout << v << " : " << *v << endl;
}

template<typename T> void printv_imp(T v, NO)
{
	cout << v << endl;
}

template<typename T> void printv(T v)
{
	// (1) 함수 오버로딩에 의한 분기 : 컴파일 시간 분기
    // 그런데 ? 에 어떤 타입을 전달해야 오버로딩이 동작 하는지?
	printv_imp(v, ? );
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
```

#### 해결책을 위한 단계 (3)
> 변수로 타입을 결정하자 (숫자로 오버로딩을 하게 됨)
``` cpp
template<int N> struct int2type {
	enum { value = N };
};

//(3) pointer 인 경우 생성
template<typename T> void printv_imp(T v, int2type<1>) {
	cout << v << " : " << *v << endl;
}

//(4) pointer가 아닌 경우 생성
template<typename T> void printv_imp(T v, int2type<0>) {
	cout << v << endl;
}

// (1) is_pointer<T>::value를 통해 1 or 0 이 리턴됨
template<typename T> void printv(T v){
	printv_imp(v,	int2type<is_pointer<T>::value>());
		// (2) int2type<0> 만 하면 타입이 되므로, ( ) 를 붙여서 임시 객체를 만듬.
		// 왜냐면, 함수로 전달되려면 type이 아니라 값이나 객체가 넘어가야 함.
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
```


#### int2type 간단한 정리
``` cpp
// "Modern C++ Design" 에 나오는 기법
// int를 type으로 만드는데, 굳이 int가 아니어도 가능 
template<int N> struct int2type {
	enum { value = N};
};

int main()
{
	foo(0);
	foo(1);

	//(1) 0 과 1은 같은 타입(int)임 결국, foo(0), foo(1)은 같은 함수 호출

	int2type<0> t0; 
	int2type<1> t1;

	foo(t0);
	foo(t1);
	// (2) t0와  t1은 서로 다른 타입, foo(t0), foo(t1)서로 다른 함수를 호출
}
```


#### int2type의 표준 함수
``` cpp
// (1) int2type : int 형 상수를 독립된 타입으로 만드는 도구
template<typename T, T  N> struct xintegral_constant {
		static constexpr T value = N;
};

// (2) true, false	:  서로 같은 타입
// (3) true_type, false_type : 서로 다른 타입
typedef xintegral_constant<bool, true > true_type;
typedef xintegral_constant<bool, false> false_type;

// (4) is_pointer 등의 traits는 아래처럼 만든다 (표준에서)
template<typename T> struct is_pointer :  false_type {};
template<typename T> struct is_pointer<T*> : true_type {};
```


#### C++ 17 표준을 사용하는 방법
``` cpp
template<typename T> void printv(T v)
{
	// (1) C++17 에서 나오는 정적 if 문
	// 템플릿에서 조건을 만족하지 않으면 코드를 생성하지 않는다.
	if  constexpr (std::is_pointer<T>::value) {
		cout << v << " : " << *v << endl;
	}
	else {
		cout << v << endl;
	}
}
 void printv(int v)
{
	 // (2) 컴파일러는 아래와 같은 함수를 만들어 냄.
	 // 조건이 맞지 않으므로, 실행이 되는것이 아니고 아예 코드 생성 안됨.
	 // std:c++latest 를 추가해서 빌드해야함. (혹은 std:c++17)
	if  constexpr (false) {
		
	}
	else {
		cout << v << endl;
	}
}
```

#### 변수의 포인터 여부에 따른 다른 동작 하기
``` cpp
template<typename T> void foo(T a) {
	// T의 포인터 여부에 따라 다른 일 하기
	if (is_pointer<T>::value) {

		// *a = 10; 과 같은 역 참조하는 소스는 사용할 수 없음
		// 1. *a = 10 과 같은 소스를 사용하려면, if constexpr 사용
		// 2. true_type, false_type으로 오버로딩
	}
	else {

	}

	if constexpr (is_pointer<T>::value) {
		*a = 10;
	}

	foo_imp(a, is_pointer<T>());
}

template<typename T> void foo_imp(T a, true_type) {}
template<typename T> void foo_imp(T a, false_type) {}

// 3. 함수 템플릿을 2개 만들고 enable_if 로 조건에 따라 사용하도록 함.
template<typename T>
typename enable_if<is_pointer<T>::value>::type foo(T a) {}

template<typename T>
typename enable_if<!is_pointer<T>::value>::type foo(T a) {}

// 기술이 나온 순서는 true_type/false_type -> enable_if -> if const_expr

```