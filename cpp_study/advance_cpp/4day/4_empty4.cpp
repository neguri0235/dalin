#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	//vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	auto p = v.begin();
	++p;	// 모든 반복자는 ++  연산이 가능하다.
	
	// p = p + 5;	// 좋지 않은 코드 : 임의 접근 반복자만 가능
	// container 를 타입을 보고서, p++ or p = p+5 를 하도록 함
	advance(p, 5); // <-- 이 방법이 좋음

	cout << *p << endl;

}