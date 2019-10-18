## enable_if

> C++11에는 이미 표준이다.
``` cpp
template<bool b, typename T = void> struct enable_if {
	typedef T type;
};

// (1) 부분 특수화 할때는 T = void 와 같은 default는 사용할 수 없다.
// T=void 라고 하면 에러 발생!
template< typename T> struct enable_if <false, T>{

};

int main()
{
	enable_if<true, int>::type	    n1;	 // int 가 됨.
	enable_if<true, double>::type	n2;	 // double 이 됨
	enable_if<true>::type			n3;  // void 타입이 됨. 하지만 void 변수는 만들 수 없으므로 error

	enable_if<false, int>::type		n4;  //error. type 자체가 존재하지 않음.
    // 잘 이해가 안됨 -> enable_if <false, T> 인 경우 type이 없음 
}
```

### 타입에 따라 함수를 생성

> 최대 공약수를 구하는 함수를 만들자
``` cpp

// 최대 공약수를 구하는 함수
// 단, 정수 계열 타입만 사용가능하게 하고 싶다.

// 방법 1: C++11 static_assert ( ) 사용
// 조건을 만족하지 않으면 무조건 빌드 에러 발생하는 함수
template<typename T> 
T gcd(T a, T b) {
	static_assert(is_integral<T>::value, "T is no integral");
	return a;
}
// 실수 계열은 아래 함수가 호출되게 하고 싶다
double gcd(double a, double b)
{
	cout << "double" << endl; return 0;
}

int main()
{
	gcd(3, 6);			// T 사용
	gcd(3.4, 2.8);		// double 사용
	gcd(3.4f, 2.8f);	// T 사용 - static assert error 발생함.
                        // float 이기 때문에, double이 아닌 T로 생성하려하지만
                        // static_assert에 걸려 빌드 에러
}
```

> enable_if를 써보자 
``` cpp
/*
enable_if<
	is_integral<T>::value, // T가 is_integral<T>::value 에서 true이면
	T> ::type			   // T에서 type을 return 한다는 의미
*/

// enable_if 를 사용한 함수 템플릿
// 조건을 만족하면 함수 템플릿 사용
// 조건을 만족하지 못하면 SFINAE의 특징에 따라 후보에서 제외
// 다른 버젼의 동일 이름 함수 사용 가능

template<typename T>
typename enable_if<is_integral<T>::value, T> ::type
// 참고로, 맨 앞에 typename을 붙이는 이슈는 template에 :: 쓰게 되면
// 멤버인지, type인지 알수 없어서 붙여주는 것

gcd(T a, T b) {
	cout << "T" << endl;
	return a;
}

double gcd(double a, double b)
{
	cout << "double" << endl; return 0;
}

int main()
{
	gcd(3, 6);          // T
	gcd(3.4, 2.8);      // double
	gcd(3.4f, 2.8f);    // double
}
```

> 정리해 보면 ( enable_if + SFINAE)
``` cpp
template<typename T>
typename enable_if<is_integral<T>::value, void> ::type
 foo(T a) {
	cout << "T" << endl;
}

void foo(...) { cout << "..." << endl; }

int main()
{
	// 정수 일때만 T, 정수가 아니면 ... 를 출력
	foo(10);
	foo(3.4);
	foo(3.4f);
}
```

### int2type을 개선해 보자
> SFINAE를 사용해서 개선!
``` cpp
template<int N> struct int2type {
	enum { value = N };
};

template<typename T> void printv_imp(T v, true_type) {
	cout << v << " : " << *v << endl;
}

template<typename T> void printv_imp(T v, false_type) {
	cout << v << endl;
}

template<typename T> void printv(T v) {
	printv_imp(v, is_pointer<T>());
}

// 사용자가 호출 했을 때 위와 같이 함수 3개를 만들지 않고,
// 단지2개만 만들어서 사용
template<typename T>
typename enable_if<is_pointer<T>::value, void>::type
printv_new(T v) {
	cout << v << " : " << *v << endl;
}

template<typename T>
typename enable_if<!is_pointer<T>::value, void>::type
printv_new(T v) {
	cout << v << endl;
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
```