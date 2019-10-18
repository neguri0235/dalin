#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

void foo(int a, int& b) { b = 100; }

int main()
{
	function<void(int)>f;
	/* 
	{
	int n = 0;
	f = bind(&foo, _1,n);  // n의 값을 복사해서 보관. 블록을 벗어나면 파괴.
	}
	*/

	int n = 0;
	f = bind(&foo, _1, ref(n));  // << ref는 어떻게 만드나?
	f(10);
	cout << n << endl;
}