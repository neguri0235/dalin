#include <iostream>
#include <memory>
#include <string>

using namespace std;



struct People {
	string name;
	People(string n) : name(n){ }
	~People() { cout << name << " 파괴" << endl; }
	shared_ptr<People> bestFriend;
};

int main()
{

	shared_ptr<People> sp1 = make_shared<People>("Kim");
	 shared_ptr<People> sp2 = make_shared<People>("Lee");

	// 서로를 가리킨다 (cycle reference) - 버그 . 메모리 삭제 안됨
	sp1->bestFriend = sp2;
	sp2->bestFriend = sp1;
}