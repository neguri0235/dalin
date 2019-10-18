## rvalue


[2_rvalue1.cpp](2_rvalue1.cpp)
``` cpp
int x = 0;
int foo() { return x; }
int& goo() { return x; }

// lvalue : 등호의 왼쪽에 올 수 있는 표기 법 
//					lvalue to rvalue conversion  (오른쪽에도 올 수 있다)
//					값 뿐만 아니라 이름(메모리)를 가지고, 단일 식(한 줄)을 넘어서 존재
//					주소 연산자로 주소를 구할 수 있다.
//					참조를 반환하는 함수

//	rvalue : 등호의 오른쪽에만 올 수 있다.
//					이름(메모리)이 없고 단일 식에만 있음
//					주소 연산자로 주소를 구할 수 없다
int main()
{
	// v1 : lvalue, 20 : rvalue
	int v1 = 10, v2 = 10;
	// 10 = v1; // 에러. 메모리가 없음
	v1 = 20;		
	v2 = v1;

	int* p1 = &v1;
	// int* p2 = &10;  // 에러
	
	// foo() = 10; // 에러
	goo() = 10;

	10; // rvalue
	"Hello";  // lvalue : 문자열 리터럴은 lvalue로 하기로 함.
//	"Hello"[0] = 'h';  // 예전 C 컴파일러는 허용
									// 요즘은 const char[] 이므로 에러
									// 문자열이 짧으면 그냥 코드 메모리로 올라가지만
									// 문자열이 길어 지면 데이터 메모리에 올리고서, 포인터로 가르킴

	const int c = 10; 
	//c = 20;  // error. immutable lvalue 라고 부름

	// 다음중 맞는 것은 ?
	// error . C 컴파일러는 허용하지만, 표준에는 맞지 않는 표현임
	//char* s1 = "hello";				
	const char* s1 = "hello";
}
```


### value category

* 핵심 : value category는 객체가 아닌 표현식(expression)에 대한 개념

1. statement : ; 으로 종료되는 한줄의 코드 모음
2. expression : 하나의 값으로 계산될 수 있는 코드 모음

`++n` 과 `n++`의 차이를 구분할 수 있어야 함.
``` cpp
int main()
{
	int n = 10; 
	n = 20;  // n : lvalue

	// n+1 은 11이 되어서 값임. 메모리에 들어가는 것이 아님 . rvalue
	n + 1 = 20;   // error
	
	// n+n 은 20, 값. error
	n + n = 20;  // error
	cout << n << endl;
	n = 3;
	// lvalue(전위형 증가 연산자는 왼쪽에).값을 리턴하는 것이 아니고 참조를 리턴하는 것
	// 참조를 리턴해야, 변경된 값을 유지하기 때문
	++n = 20;  // ok.
	
    // 참조를 리턴하지 않고 값을 리턴하게 됨.  참조를 리턴하면 변경된 값이 리턴되므로
	// 값을 리턴하고서, 메모리의 값을 증가 시킴.
	n++ = 20; // error
}
```

#### decltype
``` cpp
int main()
{
	int n = 10;
	int* p = &n;

	// decltype이 동작하는  규칙 
	// 1 : 변수 이름만 있는 경우
	//		->  해당 변수의 선언을 조사해서 타입 결정
	decltype(n) d1;  // int d1
	decltype(p) p2;  // int* p2

	// 2: 변수에 연산자가 포함된 표현식이 있는 경우
	//		-> 해당 표현식이 등호의 왼쪽에 올 수 있으면 참조, <-> 아니면 값 타입
	decltype(*p) d ;		// int& d3; 이렇게 되기 때문에 error. decltype(*p) d = n ; 이라고 했으면 에러 아님
	decltype(n + 1) d4;  //	int d4
	decltype(++n) d5 ; // int&d5; error.
	decltype(n++) d6; //int d6

	decltype(n) d7; // int
	decltype(10) d8; // int
	//decltype((n)) d9; // int& error.
	decltype((10)) d10; // int
}
```

### value category를 조사하는 방법
``` cpp
#define CHECK_VALUE_CATEGORY(...)							\
if (is_lvalue_reference<decltype ((__VA_ARGS__)) >::value)  \
	cout << __VA_ARGS__<<" : lvalue" << endl;				\
else														\
	cout << __VA_ARGS__<<" : rvalue" << endl;																			
int main()
{
	// value category를 조사하는 방법
	int n = 0;
	CHECK_VALUE_CATEGORY(10)
	CHECK_VALUE_CATEGORY(n)
	CHECK_VALUE_CATEGORY(n+n)
	CHECK_VALUE_CATEGORY("Hello")  // 문자열은 조금 특이항 경우
}
```