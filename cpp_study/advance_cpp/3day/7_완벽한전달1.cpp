#include <iostream>

using namespace std;

int main()
{
	int n = 10;
	int* p1 = &n;
	int* * p2 = &p1; // 포인터 변수의 포인터

	int& r1 = n;
	int&& r2 = n;   // 레퍼런스의 레퍼런스 - error
}