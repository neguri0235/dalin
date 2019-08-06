#include <iostream>
#include <vector>
#include <functional>
#include <numeric>


// 함수를 로깅하기 위한 함수


auto addition (const int& x, const int& y)
{
    std::cout<<x<< "+ "<<y<<std::endl;
    return x+y;
}

auto main() -> int
{
    std::vector<int> nums = {1,2,3,4,5};

    auto foldl = accumulate(begin(nums), end(nums), 0, addition);
    std::cout<<"==================="<<std::endl;
    auto foldr = accumulate(rbegin(nums), rend(nums), 0, addition);
    std::cout<<"==================="<<std::endl;
    std::cout<<foldl<<std::endl;

    std::cout<<foldr<<std::endl;

    return 0;
}
