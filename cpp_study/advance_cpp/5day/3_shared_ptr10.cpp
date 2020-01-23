#include <iostream>
#include <memory>

using namespace std;

int main()
{
	int* p1 = new int;

	shared_ptr<int> sp1(p1);  // 관리 객체 생성
	shared_ptr<int> sp2(p1); // 다른 관리 객체 또 생성

	// 핵심 : 자원을 획득한 후에, 자원의 포인터를 자원 관리 객체에 넣으면 안됨

	// 자원의 획득은 자원 관리 객체가 만들어 질때 동시에 해야함
	shared_ptr<int> sp3(new int);  // 이렇게 하는것이 좋음. 즉 make_shared를 써야 함

	//  RAII : Resource Acquision Is Initialization.
}