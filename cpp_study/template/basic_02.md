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