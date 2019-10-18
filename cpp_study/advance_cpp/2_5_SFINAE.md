## SFINAE

> 어떤 foo( ) 함수가 호출 되는지 하나씩 확인 해 보면,
``` cpp
//template<typename T> void foo(T a) { cout << "T" << endl; }
//void foo(int a) { cout << "int" << endl; }
void foo(double a) { cout << "double" << endl; }
void foo(char a) { cout << "char" <<endl; }
void foo(short a) {	cout << "short" << endl; }
void foo(...) {	cout << "..." << endl; }

int main()
{
	foo(10);
	// 1. int
	// 2. T -> template 
	// 3. error. 모호한 변환이라고 나옴 ()
    // int 와 template이 없으니, 어디로 가야 하는지 모름
}
```

> SFINAE 맛보기
``` cpp
// 1. foo(10) -> template 버젼을 사용하기로 결정
// 2. T::type 을 int::type으로 치환하게 되면 , 잘못된 표현식 등장
// 컴파일 에러가 아니라 후보군에서 제외

// 3. 다른 버전의 foo 가 있으면 사용 가능
// "치환 실패는 에러가 아니다", substitution failure is not an error. (SFINAE)

// T가 int이면 T::type 이란 표현은 없음.
// 없는 표현이면 컴파일 에러가 나야 할 것 같지만 에러 안남.
template<typename T> typename T::type foo(T a) { cout << "T" << endl;  return 0; }
template<typename T> void foo(T a) { cout << "T" << endl;  }

int main()
{
	foo(10);
}
```

``` cpp
template<typename T> void foo(T a) {
	typename T::type n;  
    // (1) T 가 int 이면 에러 발생. 여기서 에러 발생
    // 아래 3가지 조건이 아니면 에러 발생함
}

// SFINAE 는 아래 3가지 경우만 사용 가능
// 1. 함수 반환 타입 - 가장 널리 사용
template <typename T> typename T::type foo(T a) { return 0; }

// 2. 함수 인자 : 생성사자등, 반환 타입이 없는 경우에 주로 사용
template<typename T> void foo(T a, typename T::type b = 0) {}

// 3. 템플릿 인자 - 함수 자체의 모양이 복잡하지 않은 장점이 있다
template<typename T, typename T2 = typename T::type> void foo(T a) {}
int main()
{
	foo(10);
}

```