#include <iostream>

using namespace std;

int main()
{
	typedef int&		LREF;
	typedef int&&	RREF;

	int n = 10;
	LREF r1 = n;
	RREF r2 = 10;

	//typedef 나 템플릿의 경우 reference의 reference 가능
	//reference collapsing (레퍼런스 붕괴(축약))
	 // 두개다 && 인 경우에만 && 가 됨.
	LREF& r3 = n;  // int&    & => &
	RREF& r4 = n; // int&&  & => &

	LREF&& r5 = n; // int& && => &
	RREF&& r6 = 10; // int&& && => &&
}