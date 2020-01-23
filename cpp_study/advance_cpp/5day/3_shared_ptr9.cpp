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
	shared_ptr<People> sp = make_shared<People>("Kim");
	
	shared_ptr<People> = new (People)("Kim");
	weak_ptr<People> = sp;
}

// 관리 객체는 아래 4개의 정보를 가짐
// 1.  객체 수정
// 2. 객체 주소
// 3. weak ptr counter
// 4.  삭제자

// 그래서 shared ptr의 관리 객체가 제거 되는 시점은 weak ptr이 제거 될때임.
// 왜냐면 weak ptr에서 use_count 같은 것을 불러야 하기 때문. 