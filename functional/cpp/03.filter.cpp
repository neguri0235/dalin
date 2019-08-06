#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

auto main() -> int
{
    std::vector<int> nums;
    for(int i = 1; i<=20; i++) nums.push_back(i);

    std::copy(begin(nums),end(nums), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<std::endl;

    std::vector<int>nonPrimes;

    remove_copy_if(nums.begin(), nums.end(), back_inserter(nonPrimes),
                   [](int n) {

                   for(int j=2; j<n; ++j) {
                        if(n%j==0) return false;
                   }
                   return true;

                   });

    copy(nonPrimes.begin(), nonPrimes.end(), std::ostream_iterator<int>(std::cout," "));
    std::cout<<std::endl;



    return 0;
}
