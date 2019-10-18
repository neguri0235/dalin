//73 page
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

/*
STL 반복자
// 입력 반복자 :		=*p, ++   :싱글 패스        (입출력과같은)
// 출력 반복자:			*p=, ++  : 싱글 패스

// 아래는 멀티 패스

// 전진형 반복자:	*p=, ++ => 싱글리스트
// 양방향 반복자:	*p=, ++ , -- => 더블리스트
// 임의 접근 반복자  *p=, ++ , -- , +, -, []
*/

int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };


	// find 알고리즘
	// 최소 요구 조건 : 입력
	auto p = find(v.begin(), v.end(), 3);

	reverse(v.begin(), v.end());// 양방향

	sort(v.begin(), v.end());// 퀵 소트  임의 접근 : vector는 가능

	list<int>l = { 1,2,3,4 };
	sort(l.begin(), l.end()); // 리스트는 quick sort (반으로 나눠야 하는데 불가) 불가

	// 그래서 list는 내장 sort 함수 제공. 
	v.sort() // 이미 sort() 에서 vector를 sort 할 수 있음. 내장 함수로 만들 필요 없음.	
}
