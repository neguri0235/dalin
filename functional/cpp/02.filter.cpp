#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

auto main() -> int
{
    std::vector<int> numbers ;
    for(int i = 0; i<20; i++) numbers.push_back(i);


    std::copy(begin(numbers), end(numbers), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<std::endl;

    std::vector<int> primes;

    copy_if(begin(numbers),end(numbers),back_inserter(primes),
            [](int n) {
                if(n<2) {
                return n != 0 ? true : false; }
                else{
                    for(int j=2; j<n; ++j) {
                        if(n%j == 0) return false;
                    }
                    return true;
                }
            }
            );

    std::copy(begin(primes), end(primes), std::ostream_iterator<int> (std::cout, " "));
    std::cout<<std::endl;

    return 0;
}
