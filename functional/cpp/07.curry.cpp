#include <iostream>
#include <functional>


template<typename Func, typename... Args>
auto curry(Func func, Args... args)
{
    return [=](auto... lastParam)
    {
        return func(args..., lastParam...);
    };
}

int volumeOfRectanglular(int len, int wid, int hei)
{
    return len*wid*hei;
}

auto main() -> int
{
    auto length5width4 = curry(volumeOfRectanglular,5,4);

    for(int i = 0; i<=5; ++i) {
        std::cout<<"length5width4("<<i<<") = ";
        std::cout<<length5width4(i)<<std::endl;
    }
    return 0;
}

