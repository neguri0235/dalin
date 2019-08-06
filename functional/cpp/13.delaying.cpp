#include <iostream>
#include <functional>

using namespace std;


/*

람다 표현식을 인수로 전달했음.
람다 표현식은 인스턴스 생성 시점에 실행되지 않고, Fetch()가 실행되면 실행됨.
Fetch() 가 실행될 때, multiply, division 인스턴스가 생성됨

*/

template<typename T> class Delay
{
private:
    function<T()> m_func;

public:
    Delay(function<T()>func) : m_func(func){ }

    T Fetch()
    {
        return m_func();
    }
};

auto main() -> int
{
    int a = 10;
    int b = 5;

    Delay<int> multiply([a,b](){
        cout<<"Delay<> multiply is ctor"<<endl;
        return a*b;
    });

    Delay<int> division([a,b](){
        cout<<"Delay division ctor"<<endl;
        return a/b;
    });


    cout<<"invoking Fetch()"<<endl;

    cout<<multiply.Fetch()<<endl;
    cout<<ivision.Fetch()<<endl;

    return 0;
}
