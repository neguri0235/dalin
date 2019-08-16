### specialization


``` cpp
// primary template
template<typename T> class Stack {
public:
    void push(T a) {cout<<"T"<<endl;}
};

// partial specialization (부분 특수화, 부분 전문화)
template<typename T> class Stack<T*>{
public:
    void push(T* a){cout<<"T*"<<endl;}
};

// specialization (특수화, 전문화
template<> class Stack<char*> {
public:
    void push(char *){cout<<"char*"<<endl;}
};

int main()
{
    Stack<int>s1; s1.push(0);
    Stack<int*>s2; s2.push(0);
    Stack<char*>s3; s3.push(0);
    return 0;
}
```
특수화를 하든 안하든 소스 코드는 커지지만, 실제 만들어 지는 기계어 코드는 변화가 별로 없음

특수화를 더 사용해 보자
``` cpp
template<typename T, typename U> struct Test {
    static void foo(){cout<<"T, U"<<endl;}
};

template<typename T, typename U> struct Test <T*,U>{
    static void foo(){cout<<"T*, U"<<endl;}
};

template<typename T, typename U> struct Test <T*,U*>{
    static void foo(){cout<<"T*, U*"<<endl;}
};

// 부분 특수화 할때, 인자는 두개를 꼭 사용해야 함.
template<typename T> struct Test <T,T>{
    static void foo(){cout<<"T T"<<endl;}
};

template<typename T> struct Test <int,T>{
    static void foo(){cout<<"int T"<<endl;}
};

template<> struct Test <int,int>{
    static void foo(){cout<<"int int"<<endl;}
};

template<> struct Test <int,short>{
    static void foo(){cout<<"int short"<<endl;}
};

template<typename T, typename U, typename V> struct Test <T,Test<U,V>>{
    static void foo(){cout<<"T T<U,V>"<<endl;}
};

int main()
{
    Test<int, double>::foo();  //T, U
    Test<int*, double>::foo(); //T*,U
    Test<int*, double*>::foo(); //T*, U*
    Test<int,int>::foo();  // 두개가 같은 타입. T, T
    Test<int,char>::foo();  // int, U
    Test<int,short>::foo();  // int, short
    Test<double, Test<char,short>>::foo();  // T, Test<U,V>
    return 0;
}
```

### specialization 주의 할 점
``` cpp

template<typename T>struct Test {
    static void foo() {cout<<typeid(T).name() <<endl;}
};

int main()
{
    Test<int>::foo();
    Test<int*>::foo();
    return 0;
}
```
출력하면 int, int* 가 나오게 되는데, 여기서 특수화를 사용하면, 출력해보면
아래는 int 로 나오게 됨. 
```cpp
template<typename T>struct Test <T*>{
    static void foo() {cout<<typeid(T).name() <<endl;}
};
```

아래는 default 값이 있으로 문제 없이 잘 실행됨
``` cpp
template<typename T, int N = 10>struct Stack {
    T buff[N];
};
int main()
{
    Stack<int,10> s1;
    Stack<int> s2;
}
```

그런데 여기서 특수화를 하고 싶어 아래는 추가 한다고 하면 에러가 발생.
primary에서 default 값을 부여 했으면 특수화 버젼에서는 default 값을 줄 필요 없음
``` cpp
template<typename T, int N = 10>struct Stack<T*, N> {
    T buff[N];
};
```

컴파일러가 알아서 default 값을 가지고 옴
``` cpp
template<typename T, int N>struct Stack<T*, N> {
    T buff[N];
};
```

클래스 전체가 아닌 멤버 함수만 특수화 하고자 할때
``` cpp 
template<typename T>class Stack {
public:
    T pop() {}
    void push(T a);
};
template<typename T> void Stack<T>::push(T a){
    cout<<"T"<<endl;
}

template<> void Stack<char*> ::push(char* a){
    cout<<"char*"<<endl;
}

int main()
{
    Stack<int>   s1; s1.push(0);
    Stack<char*> s2; s2.push(0);
}
```


### IfThenElse

빌드 시점에 bool 값을 이용하여 특수화 한다.

```cpp
template<bool b, typename T, typename F>struct IfThenElse {
    typedef T type;
};

// 부분 특수화 할때 선언하는 개수는 두개여도 되지만, 뒤에 나오는 인자의 개수는 꼭 일치애햐 함.
template<typename T, typename F>struct IfThenElse<false,T, F> {
    typedef F type;
};

int main()
{
    IfThenElse<true, int, double>::type t0;  //int
    IfThenElse<false, int, double>::type t1;  //double

    cout<<typeid(t0).name()<<endl; //int
    cout<<typeid(t1).name()<<endl; //double
}
```

`IfThenElse`를 사용하는 예를 보면, 32비트맵을 관리하지만. 8 비트만 필요한 경우 메모리 낭비가 발생하게 됨

```cpp
template<bool b, typename T, typename F>struct IfThenElse {
    typedef T type;
};

template<typename T, typename F>struct IfThenElse<false,T, F> {
    typedef F type;
};

template<size_t N>
struct Bit{
    using type = typename IfThenElse< (N<=8), char, int>::type;
    type bitmap;
};

int main()
{
    Bit<32>b1;
    Bit<8>b2;
    cout<<sizeof(b1)<<endl;
    cout<<sizeof(b2)<<endl;
}
```

이 기능은 `conditional` 이라는 기능으로 `<type_traits>`를 통해서 지원하고 있음

``` cpp

#include <type_traits>

template<size_t N>
struct Bit{
    using type = typename conditional< (N<=8), char, int>::type;
    type bitmap;
};

int main()
{
    Bit<32>b1;
    Bit<8>b2;
    Bit<16>b3;
    cout<<sizeof(b1)<<endl;
    cout<<sizeof(b2)<<endl;
}
```