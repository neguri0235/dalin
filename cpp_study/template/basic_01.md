
### Basic

``` cpp
// macro 로만들 수가 있음.
#define MAKE_SQUARE(T) \
T square(T a)           \
{                      \
    return a*a;         \
}

MAKE_SQUARE(int)
MAKE_SQUARE(double)

int main()
{
    square(3);
    square(3.3);
    return 0;
}

```
> 컴파일러가 이미 3, 3,3의 type을 알고 있는데, 굳이 int, double을 명시할 필요가 없지만, 전처리기는 3, 3.3의 타입을 알 수 없으므로 명시적으로 적어 줘야 함.

``` cpp
template<typename T>
T square(T a)
{
    return a*a;
}

int main()
{
    square<int>(3);
    square<double>(3.3);
    return 0;
}
```
> 템플릿으로 만들 수 있는데, `<>`를 생략해도 컴파일러가 잘 생성해 줌.

### Template Instance

컴파일러가 template으로 부터 실제 함수를 만들어 내는 과정. 함수 call 이 되지 않으면 실제 함수를 생성하지 않음.
* 명시적 인스턴스
* 암시적 인스턴스 (많이 사용)



> 명시적 인스턴스는 아래 처럼 할 수 있는데, main() 함수에서 square를 사용하지 않더라도, 컴파일러가 square()를 만들어 놓음. 첫번째 문장이 기본 표현이고 두번째, 세번째처럼 작성해도 컴파일러가 해석을 잘 해줌.  

``` cpp
template<typename T> class Test
{
public:
    void foo(){}
    void goo(){}
};
template<typename T> T square(T a)
{
    return a*a;
}

// 명시적 인스턴스의 예
template int square<int>(int);
template int square<>(int);
template int square(int);

// 명시적인 클래스의 인스턴스 예
template class Test<int>;
// 클래스내에서 함수 하나만 인스턴스화 할수 있음
template void Test<int>::foo();
int main()
{
}
```

> 암시적 인스턴스는 템플릿을 사용할 때

``` cpp
int main()
{
    // 타입을 생략하는 경우 컴파일러가 추론하여 만듬
    int n1 = square(2);
    int n2 = square<int>(3);

    // 클래스 템플릿의 경우 사용하지 않는 함수는 인스턴스화 하지 않음.  
    // 아래서는 goo() 함수는 인스턴스화 되지 않음
    // 지연된 인스턴스라고 부름

    // 클래스에서는 타입을 지정해 줘야 하는데 cpp 17부터는 컴파일러에서 지원함.
    Test<int>t2;
    t2.foo();
}
```

### Class Template Type Dedection

컴파일러가 함수로 전달되는 인자를 보고서 타입을 결정하는 것을 말함.

``` cpp
template<typename T> class Vector
{
    T* buff;
public:
    Vector(){}
    Vector(int sz, T initValue){}
};

int main()
{
    Vector<int> v1(10,3);
    Vector v1(10,3);  // C++ 17 부터 가능
    Vector v3; // C++ 17도 타입 추론 안됨
}
```
> 클래스의 생성자를 확인 후에 컴파일러에서 타입을 추론함.
`Vector()->Vector<int>` 라는 것을 C++ 17에서 지원하는데, `user define deduction guide`라고 함

``` cpp

template<typename T> void foo(T a) {}

template<typename T, typename U> struct pair
{
    T first;
    U second;
    pair(const T& a, const U& b) :first(a), second(b){}
};

int main()
{
    pair<int, double> p(1, 1.2);
    foo(p);
    foo(pair<int,double>(1, 1.2)); // 임시 객체로 만들어도 됨
}
```
> C++ 17 이전에는 컴파일러가 클래스의 생성자를 이용하여 타입 추론이 불가함. 그래서 타입을 `<>`에 넣어 줘야 하지만  
```cpp
template<typename T, typename U>
pair<T,U> make_pair(const T&a, const U& b)
{
    return pair<T,U>(a,b);
}
```
> make_pair를 만들어서 사용하면 됨. (함수 템플릿은 타입 추론이 가능하기 때문에 가능함) 이런 기법을 `object generator`라고 부르는데 C++ 17 부터는 사용이 줄어 들것 같음

``` cpp
template<typename T> struct identity
{
    typedef T type;
};

template<typename T> void foo(T a) {}
template<typename T> void goo(typename identity<T>::type a){}

int main()
{
    identity<int>::type n;
    foo(3);
    foo<int>(3);
    goo(3); // compile error
    goo<int>(3);
}
```
> goo()의 전달 인자인 identity는 클래스 템플릿이라서 컴파일러가 타입 추론을 할 수 없음
> 
```
error: no matching function for call to 'goo(int)'|
note: candidate: template<class T> 
note: template argument deduction/substitution failed:|
```
> 함수 템플릿 사용할 때, 꼭 타입을 지정해서 전달이 필요한 경우 `identity`를 사용함

### Template Instantiation 사용 시 주의할 사항

``` cpp
template<typename T> T square(T a)
{
    return a*a;
}
int main()
{
    printf("%p\n",&square); // compile error
    printf("%p\n",&square<int>); // compile ok
}
```
> &square<int>로 사용하는 경우 template instantiation 이 됨  
> square는 template 이지 함수는 아니기 때문
`    printf("%p\n",static_cast<int(*)(int)>(&square));` 이렇게 static_case를 해도 가능

### Lazy Instantiation

```cpp
template<typename T>class A
{
    int data;
public:
    void foo(T n) { *n = 10;}
};


int main()
{
    A<int> a;
    a.foo(10);
}
```
> `A<int> a;` 까지는 빌드 에러가 발생하지 않음. 왜냐면 실제 foo()라는 함수를 사용하지 않으므로 컴파일러가 instantiation 하지 않음. 예를 들어 클래스에서 100개의 함수를 제공하지만 실제는 1개만 사용하면 인스턴스화 하는 것은 한개만 하면 됨

### Template Argument Type Decuction

컴파일러가 함수 인자를 보고 템플릿의 타입을 결정 하는 것.


> 두번째 세번째의 foo 함수 인자는 const int 와 reference 이지만 foo(T a) 로 되어 있기 때문에 const 와 reference 속성이 제거 됨. 왜냐면 foo로 넘어가는 것이 복사본의 개념이기 때문
``` cpp
template<typename T> void  foo(T a)
{
    ++a;
}

int main()
{
    int n = 0;
    int& r = n;
    const int c = n;
    foo(n); // int a:1
    foo(c); // int a:1
    foo(r); // int a:1
}
```
> reference로 되어 있는 경우 const는 compile error 가 발생함  
``` cpp
template<typename T> void  foo(T& a)
{
    ++a;
}
int main()
{
    int n = 0;
    int& r = n;
    const int c = n;

    foo(n); // int a:1
    foo(c); // compile error
    foo(r); // int a:2
}
```

### array name

``` cpp
int x[3] = {1,2,3};
```
> 변수의 이름을 빼면 type만 남게 되는데, `int[3]`. 배열의 주소를 만드려면 int  (*p)[3] = &x 가 정확한 배열의 주소가 됨. ( *p = &x 는 아님)

``` cpp
int x1[3] = {1,2,3};
int x2[3] = x1 ; // error . 배열은 자신과 동일한 타입의 배열로 복사가 안됨
int *p1 = x1; // 배열의 이름은 첫번째 요소의 주소로 암시적 형변환이 됨
int (*p3)[3] = &x1; // 배열의 주소가 되고 pointer 연산을 하면 delta가 달라짐.
```

### Argument Decay

* 배열을 값으로 받으면 T는 요소 타입의 포인터가 됨
* 배열을 참조로 받으면 T는 배열 타입으로 결정
``` cpp
template<typename T> void foo(T a){}
// void foo(int* a) 로 만듬
template<typename T> void goo(T& a){}
// void goo( int(&a)[3]) 으로 만듬
int main()
{
    int x[3] = {1,2,3};

    int y[3] = x; //error
    int* p = x; // ok
    int (&r)[3] = x // ok

    foo(x);
    goo(x);
}
```

> 아래에서는 goo()에서 에러가 발생하는데, orange는 7개짜리 배열의 타입이 넘어가고 apple은 6개까지 배열의 타입이 넘어가게 되어 서로 다른 타입이 되어 컴파일 에러가 발생함.  
만약 두 문자열의 길이가 같아면 컴파일 에러 발생하지 않음
``` cpp
template<typename T>void foo(T a, T b){}
template<typename T>void goo(T& a, T& b){}

int main()
{
    foo("orange","apple");
    goo("orange","apple");
}
```