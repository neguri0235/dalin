#include <iostream>
#include <functional>

using namespace std;

class MyValue {
public:
    const int value;
    MyValue(int v) :value(v){}
};

class MyFunction {
public:
    const int x,y;

    MyFunction(int _x, int _y) : x(_x), y(_y){}

    MyValue addition() const { return MyValue(x+y);}
    MyValue substraction() const { return MyValue(x-y);}
};

auto main() -> int
{
    int a = 100;
    int b = 10;

    cout<<"a,b = "<<a<<" "<<b<<endl;


    MyFunction func(a,b);


    auto callableAdd = mem_fn(&MyFunction::addition);
    auto callableSub = mem_fn(&MyFunction::substraction);

    auto value1 = callableAdd(func);
    auto value2 = callableSub(func);

    cout<<"value 1: "<<value1.value<<endl;
    cout<<"value 2: "<<value2.value<<endl;

    return 0;
}
