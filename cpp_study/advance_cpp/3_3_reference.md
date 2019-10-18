### 레퍼런스 규칙
```  cpp
// 레퍼런스 규칙
// 1. non const lvalue reference는 lvalue만 가리킨다
int n = 0;
int& r1 = n;		// 0k
int& r2 = 10;		// error

// 2. const reference는 lvalue 와 rvalue 모두 가리킨다
// 단점 : rvalue가 항상 const 인 것은 아니다 . Point(0, 0)란 임시 객체를 생성한 경우
const int& r3 = n;	//ok
const int& r4 = 10;	// ok
//ARM(annotated reference manual)에 나온 내용

// 3. C++11 . const 없이 rvalue 가리키는 참조가 필요했다.
// rvalue reference는 rvalue만 가르킬 수 있다.
int&& r5 = n;		// error 
int&& r6 = 10;		// ok
```  

### lvalue, rvalue의 함수 전달
``` cpp
// __FUNCTION__ : 함수 이름 . C++ 표준
// __FUNCSIG__ : 함수 이름 + signature  (vc++)
// __PRETTY_FUNCTION__ (g++)

int n = 10;
foo(n);		// 1번 -> (1번 없으면) 2번 순으로
foo(10);	// 3번 -> (3번 없으면) 2번

int& r1 = n; 
foo(r1);			// 1번 -> (1번 없으면) 2번 순으로

int&& r2 = 10;
// >>>> 중요 !!! 어디로 가는지? 1번임. 10은 rvalue 이지만, r2는 lvalue 임.그래서 1번으로 간다. 없으면 2번으로.
foo(r2); 
foo(r2+1);    //  3번으로 감. 없으면 2번

foo(static_cast<int&&> (r2));// 3번으로
/*
https://en.cppreference.com/w/cpp/language/static_cast
If new_type is an rvalue reference type, static_cast converts the value of glvalue, class prvalue, or array prvalue (until C++17)any lvalue (since C++17) expression to xvalue referring to the same object as the expression, 
*/
foo(static_cast<int&> (10));   // casting error
// int&, int&& : 데이터 타입
// rvalue, lvalue: 표현식에 대한 속성
```