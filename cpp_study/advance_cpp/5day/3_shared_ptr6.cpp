#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct People {
	string name;
	People() = default;
	People(string n) : name(n) { }
	~People() { cout << name << " 파괴" << endl; }
	// shared_ptr<People> bestFriend;  // -> 일반 포인터로 변경

	// 멤버 데이타는 수명에 관계 하지 않는다.
	// People* bestFriend;

	weak_ptr<People> bestFriend; 
	// 참조 계수가 증가하지 않는 스파트 포인터. 
	// 객체 파괴 여부 조사 가능
};

int main()
{

	shared_ptr<People> sp1 = make_shared<People>("Kim");
	{
		shared_ptr<People> sp2 = make_shared<People>("Lee");

		sp1->bestFriend = sp2;  // weak는 shared와 호환
		sp2->bestFriend = sp1;
	}

	if (sp1->bestFriend.expired()) {   // expired() 로 판단 가능
		cout << "객체 파괴됨" << endl;
}