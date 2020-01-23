#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct People {
	string name;
	People(string n) : name(n){ }
	~People() { cout << name << " 파괴" << endl; }
	// shared_ptr<People> bestFriend;  // -> 일반 포인터로 변경
	
	// 멤버 데이타는 수명에 관게 하지 않는다.
	People* bestFriend;
};

int main()
{
	
	shared_ptr<People> sp1 = make_shared<People>("Kim");
		{
		shared_ptr<People> sp2 = make_shared<People>("Lee");

		sp1->bestFriend = sp2.get();
		sp2->bestFriend = sp1.get();
	}

	if(sp1 -> bestFriend != nullptr) {  // dangling 포인터. 객체가 파괴었는지 모름
		cout << sp1->bestFriend->name << endl;
}