#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n = 10;

	// 복사본 변수. 문제 없음
	auto a1 = n;
	auto a2 = 10;


	auto& a3 = n;
	//auto& a4 = 10;  // error

	// auto는 템플릿과 같다.
	// foo(T arg); foo(10) => 10을 보고 T를 결정
	// auto arg = 10;  10을 보고 auto 결정
	auto&& a5 = n;
	auto&& a6 = 10;

	vector<bool> v(10, 0);
	auto			a10 = v[0]; /// 임시 객체를 넣는 것
	auto&		a11 = v[0]; // 임시 객체를 & 에 넣을 수없음
	auto&&	a12 = v[0]; // && 는 forwarding reference라서 에러 아님. &&는 모든 타입을 넣을 수 있음
}