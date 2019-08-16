### Class Template

클래스 템플릿에서는 타입을 지정해 줘야 함.

``` cpp
template<typename T> class complex
{
    T re, im;
    void foo(complex c){ // 클래스의 멤버 함수일 경우 compile error 발생 안함
        complex c3;      // complex<T> c3 이라고 컴파일러가 인식
    }
};
/* compile error 발생함. Complex 의 type을 알 수 없음 
void foo(complex c){}
*/

int main()
{
//  complex c1;    // compile error
    complex<int> c2;
}
```

#### 멤버 함수등을 외부에 구현 할때

> getReal() 이란 함수를 외부에서 구현할 경우 외부에서는 return type을 알 수가 없으므로
`template<typename T> T`를 붙여준다

``` cpp
template<typename T> class complex
{
    T re, im;
public:
    complex(T a = {}, T b = {}) : re(a), im(a){}
    T getReal() const ; //(1)
    static int cnt; //(2)
    // 클래스 템플릿의 멤버 함수 템플릿 (선언만 있음) (3)
    template<typename U> T func(const U& c);    
};
//(1) 멤버 함수를 외부에 구현 할 때
template<typename T>T complex<T>::getReal() const
{
    return re;
}
//(2) static member 변수의 초기화를 외부에서 하는 경우
template<typename T> int complex<T>::cnt = 0;

//(3)
template<typename T> template<typename U>
T complex<T>::func(const U& c){}
```

### 일반화된 복사 생성자

복사 생성자는 같은 타입에만 가능. 다른 타입인 경우 컴파일 에러가 발생함

``` cpp
template<typename T>class Complex
{
    T re,im;
public:
    Complex(T r = {}, T i = {}) : re(r), im(i){}

    // (1)일반적인 복사 생성
    //Complex(const Complex<T>& c){}

    // (2)이렇게 하면 컴파일 에러 안남. 하지만 Complex<int>만 가능
    //Complex(const Complex<int>& c){}

    // (3)이렇게 하면 int 뿐만 아니라 모든 타입을 인자로 받을 수 있음
    // 이렇게 만드는 것을 일반화된 복사 생성자라고 부름
    template<typename U>
    Complex(const Complex<U>& c){}

};

int main()
{
    Complex<int> c1(1,2);
    Complex<int> c2 = c1; // 컴파일러가 복사 생성자를 알아서 만들어 줌
    Complex<double> c3 = c1; // 컴파일 에러
}
```

> 위 소스에서 (3)을 외부에 구현 한다고 하면 이렇게 할 수 있는데 컴파일 에러가 발생함. 왜냐면 private 변수를 참조하기 때문에. 그래서 `template<typename> friend class Complex;` 를 클래스 내부에 선언해 줘야 함

``` cpp
template<typename T> template<typename U>Complex<T>::Complex(const Complex<U>& c)
: re(c.re), im(c.im){ }
```

### Friend 함수

`cout`을 연산자 재정의 하여 만든 경우 x,y는 private 변수 이기 때문에 friend 함수로 만듬. 

``` cpp
class Point{
    int x,y;
public:
    Point(int a = 0, int b = 0) : x(a), y(b){}
    friend ostream& operator<<(ostream& os, const Point& p);
};

ostream& operator<<(ostream& os, const Point& p){
    return os <<p.x<<' '<<p.y<<'\n';
}

int main()
{
    Point p(1,2);
    cout<<p<<endl;
}
```

하지만 Point class가 template로 되어 있다면, 일반적으로 아래와 같이 만들면 되는데
컴파일 하면 에러가 발생함  
`undefined reference to operator<<(std::ostream&, Point<int> const&)`
이유는 클래스 밖에 구현한 함수는 함수 템플릿이라서, 컴파일러는 클래스 내의 `operator<<`의 구현 부를 찾기 때문에 undefined reference error가 발생하는 것임

``` cpp
template<typename T>
class Point{
    T x,y;
public:
    Point(T a = 0, T b = 0) : x(a), y(b){}
    friend ostream& operator<<(ostream& os, const Point<T>& p);
};
template<typename T>
ostream& operator<<(ostream& os, const Point<T>& p){
    return os <<p.x<<' '<<p.y<<'\n';
}

int main()
{
    Point<int> p(1,2);
    cout<<p<<endl;
}
cout<<p<<endl;
}
```

이것을 어떻게 해결 하느냐..
1. friend 함수 선언시에 함수 자체를 템플릿 모양으로 선언  
>  
``` cpp
    friend ostream& operator<<(ostream& os, const Point<T>& p);
    //이경우 빌드 에러 남.

    template<typename U>
    friend ostream& operator<<(ostream& os, const Point<U>& p);
    // 이렇게 만듬
```

2. 이것 보다는, friend 함수를 일반 함수로 만들고, 구현을 클래스 템플릿 내부에 포함시킴
> 
``` cpp
template<typename T>
class Point{
    T x,y;
public:
    Point(T a = 0, T b = 0) : x(a), y(b){}
    friend ostream& operator<<(ostream& os, const Point<T>& p)
    {
          return os <<p.x<<' '<<p.y<<'\n';
    }
 
};
int main()
{
    Point<int> p(1,2);
    cout<<p<<endl;
}
```


### Typename

``` cpp
class Test{
public:
    enum { value1 = 1};
    static int value2;
    typedef int INT;
    using SHORT = short;
    class innerClass{};
};
int Test::value2 = 1;

int main()
{
    int n1 = Test::value1;  // 값을 꺼내는 것
    int n2 = Test::value2;  // 값을 꺼내는 것
    Test::INT a;             // 타입을 꺼내는 것
    Test::SHORT b;           // 타입을 꺼내는 것
    Test::innerClass c;      // 타입을 꺼내는 것
}
```

다른 예제를 보면
``` cpp
int p = 0;
class Test{
	enum {DWORD = 5;} //(2)
	typedef int DWORD; //(3)
};
template<typename T>int foo(T t){
    T::DWORD* p; // (1)
	Test::DWORD*p //(4)
    typename T::DWORD* p; //(5)
    return 0;
}
int main()
{
    Test t;
    foo(t);
}
```
> (1) 이 어떻게 해석이 되는지?   만약 (2) 라고 선언이 되어 있다면 값을 꺼낸 것이 되어 '5*p' 라는 표현  
(3) 이라고 하면 지역 변수 p(포인터)를 선언한 것으로 의미 
만약 (4)와 같이 T 가 아닌 Test 로 되어 있다면 컴파일러는 Test 선언을 보고서 값인지, 선언인지 구분 가능하지만
Test 가 아니라 T로 되어 있으면 구분 할 수가 없음.
그래서 결국은 (5)와 같이 'typename'을 붙여서 DWORD를 타입으로 해석해 달라고 해야 함


### value_type  

이런 함수가 있을 경우, 이왕이면 vector<int> 뿐만 아니라 vector<double>도 같이 입력 받으면 좋을것 같은데  
``` cpp
void print_first_element(vector<int>& v)
{
    int n = v.front();
    cout<<n<<endl;
}
int main()
{
    vector<int> v = {1,2,3};
    print_first_element(v);
}
```

이렇게 하면 원하는대로 되었음. 그런데 'vector' 가 아닌 'list'를 프린트 하고 싶으면.

``` cpp 
template<typename T>
void print_first_element(vector<T>& v)
{
    T n  = v.front();
    cout<<n<<endl;
}
int main()
{
    vector<double> v = {1,2,3};
    print_first_element(v);
}
```

모든 container를 전달 하고 싶을때, 이렇게..  
``` cpp
template<typename T>
void print_first_element(T& v) //(1)
{
    ? n  = v.front(); //(2)
    cout<<n<<endl;
}
int main()
{
    list<double> v = {1,2,3};
    print_first_element(v);
}
```
(1) 과 같이 container 자체를 전달 할 수 있는데, (2)에서는 T container에 있는 데이터 타입을 가지고 와야 하는데
어떻게 가지고 올 수 있을까?  
> 모든 컨테이너는 자신이 저장하는 타입이 있음. 그 타입을 value_type이라는 이름으로 알려준다.


> stl에서는 아래와 같이 'value_type'을 사용하고 있음

``` cpp
template<typename T, typename Ax = Allocator<T>> class list {
	public:
	typedef T value_type; // typename T가 value_type으로 선언
};

list<int> s = {1,2,3};
list<int>::value_type n = s.front(); // 여기서 value_type은 int 가 되는 것임
```

그래서 위에 어떻게 처리할 지 모르는 부분을 이렇게 할 수 있음
``` cpp
template<typename T>
void print_first_element(T& v)
{
    T::value_type n  = v.front();
    cout<<n<<endl;
}
```
그런데 컴파일 하면 에러 나옴, 그래서 위에서 나온 'typename'을 붙여 줘야 함

``` bash
dependent-name T:: value_type is parsed as a non-type, but instantiation yields a type
say 'typename T:: value_type' if a type is meant|
```
결국 이렇게, 'typename T::value_type n = v.front()'


### template

``` cpp
class Test
{
public:
    template<typename T>static void f() {}
    template<typename T>class Complex {};
};

template<typename T> void foo(T a)
{
    Test::f<int>(); //ok
//    T::f<int>(); //error . 컴파일러가 `<`가 비교연산인지, 템플릿인지 모름
    T::template f<int>(); //ok
}
int main()
{
    Test t;
    foo(t);
}
```


### template parameter


template으로 전달되는 인자는

1. type
2. 값(non-type)
3. template

```cpp

template<typename T, int N> struct Stack{
    T buffer[N];
};

int main()
{
    Stack<int, 10> s;
}
```

1. 정수형 상수를 전달할 수 있음(1), 단 변수는 안됨(2)
2. enum 상수도 가능 (3)
3. pointer도 가능하지만, reference의 경우 지역 변수의 주소이므로 불가능(4) . 하지만 전역 변수의 주소는 가능  
   정확히는 지역 변수라기 보다는 no linkage를 가지는 변수 주소는 불가능
4. 함수 포인터도 가능  

```cpp
template<int N> class Test1{};
enum Color { red = 1, green =2};
template<Color> class Test2 {};
template<int*> class Test3 {};
template<int(*)(void)> class Test4{};

int x = 0;
int main()
{
    int n = 10;
    Test1<10> t1; //(1)
    Test1<n> t1;  //(2)
    Test2<red> t3; //(3)
    Test<&n> t4; // (4)
    Test<&x> t5;
}
```

typeid를 통해 전달되는 type을 확인 할 수 있음
``` cpp
template<auto N>struct Test{
    Test()
    {
        cout<<typeid(N).name()<<endl;
    }
};

int x = 0;
int main()
{
    Test<10> t1;
    Test<&x> t2;
    Test<&main> t3;
}
```

``` cpp
template<typename T>class List{};
template<typename T, template<typename> class C> class Stack{
	C c; //error
	C<T> c; // ok. List<int> c;
};

int main()
{
    list s1; //error
    List<int> s2;
    Stack<int, List> s3;
    // Stack의 첫번째는 타입인데, 두번째 인자는 템플릿임. 그래서
    // List 가 아닌 List<int> 로 적으면 템플릿이 아닌 type이 됨.
}
```


### variable template

`constexpr`을 이용하여 define 대신 사용할 수가 있는데, 빌드해보면 T의 type이 서로 달라서 빌드 에러가 발생 함.

``` cpp
constexpr double pi = 3.14;
template<typename T> void foo(T a, T b){ }

int main()
{
    float f = 3.3;
    foo(f,pi);
}
```

그래서 pi = 3.14를 template으로 만들수가 있음
``` cpp
template<typename T> constexpr T pi = 3.14;
template<typename T> void foo(T a, T b){ }
int main()
{
    float f = 3.3;
    foo(f,pi<float>);
}
```