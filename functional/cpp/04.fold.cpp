#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

auto main() -> int
{
    std::vector<int> nums = {0,1,2,3,4};

    auto foldl = accumulate( begin(nums), end(nums),0,std::plus<int>());

    auto foldr = accumulate( rbegin(nums), rend(nums), 0, std::plus<int>());

    std::cout<<"foldl "<<foldl<<std::endl;
    std::cout<<"foldr "<<foldr<<std::endl;

    return 0;
}
