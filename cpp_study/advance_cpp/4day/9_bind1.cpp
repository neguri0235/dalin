#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

void foo(int a, int b, int c, int d) {
	printf("%d %d %d %d\n", a, b, c, d);
}



int main()
{
	foo(1, 2, 3, 4);
	bind(foo, 1, 2, 3, 4)();
	bind(foo, 1, _1, _2, _3)(7, 8, 9);  // 1, 7, 8,9
	bind(foo, 9, _2, _1,7)(6,4);  // 9, 4, 6, 7
}