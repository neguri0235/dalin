#include <iostream>


int factorialTail(int n, int i)
{
    if(n == 0) return i;
    return factorialTail(n-1, n*i);
}


int factorial(int i)
{
    return factorialTail(i,1);
}

auto main() -> int
{
    for(int i = 1; i<10; i++) {
        std::cout<<i<<"! = "<<factorial(i)<<std::endl;
    }
    return 0;
}
