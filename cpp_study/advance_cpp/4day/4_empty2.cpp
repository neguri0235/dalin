//73 page
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	//vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	auto p = v.begin();
	p = p + 5;  // vector는 반복자 이동 가능
						// list는 반복자 이동 불가
	cout << *p << endl;

	// stl의 성능 향상이 없으면 구현 안함. 
	// list에서는 list 이동 시 p +2 는 p++, p++ 와 같아서 굳이 구현 안함
	// vector의 경우 p+2 는 그대로 p+2 로 구현시 성능 향상이 있어서 p+2 지원 함
}

/*
STL 반복자
// 입력 반복자 :		=*p, ++   :싱글 패스
// 출력 반복자:			*p=, ++



// 전진형 반복자:	*p=, ++ => 싱글리스트
// 양방향 반복자:	*p=, ++ , -- => 더블리스트
// 임의 접근 반복자  *p=, ++ , -- , [] 
*/