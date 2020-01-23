#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct People {
	string name;
	People(string n) : name(n) { }
	~People() { cout<< name << " 파괴" << endl; }
	weak_ptr<People> bestFriend;
};

int main()
{
	shared_ptr<People> sp1;
	weak_ptr<People> wp1;

	shared_ptr<People> sp2 = make_shared<People>("Kim");

	// sp1 = sp2; // 참조 계수 2
	wp1 = sp2;  // 참조 계수 증가 안함. 
	cout << sp2.use_count() << endl;

	//---------------------
	shared_ptr<People> sp3 = make_shared<People>("lee");
	shared_ptr<People> sp4 = sp3;
	weak_ptr<People> wp4 = sp3;

	// 아래 코드는 안전한가? 
	string s1 = sp4->name;   // sp가 살이 있는 동안 객체는 파괴될 수 없다. 
								// dangling 포인터가 나올 수 없다. 

	//string s2 = wp4->name; 	// error. wp4가 살아 있다고 해도 객체가 살아 있다는 보장이 없음
	// 그래서 -> 와 *  =연산자가 재정의 되어 있지 않다.

	// wp에 접근하려면,  참조 계수를 올리고서 접근해야 한다.
	// 참조 계수를 올리는 방법은 "shared_ptr"을 만들어야 한다.

	shared_ptr<People> sp5 = wp4.lock();  // lock 하는 도중에 sp3의 소멸자는 안불림.
	if (sp5) {
		string s3 = sp5->name;
	}
}
