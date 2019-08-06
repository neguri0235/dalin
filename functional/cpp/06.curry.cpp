#include <iostream>
#include <functional>

template<typename Func, typename ... Args>
auto curry(Func func, Args ... args)
{
    return [=] (auto ... lastParam)
    {
        return func(args..., lastParam...);
    };
}

int areaOfRectangle(int len, int wid)
{
    return len*wid;
}

auto main() -> int
{
    auto length5 = curry(areaOfRectangle,5);

    for(int i = 0; i<=5; i++){
        std::cout<<"length5("<< i<<") = ";
        std::cout<<length5(i)<<std::endl;
    }
    return 0;
}
