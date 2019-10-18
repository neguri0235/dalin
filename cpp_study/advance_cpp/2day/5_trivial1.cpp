#include <iostream>
using namespace std;

// trivial : 하는 일이 없다.

class Sample {
public:
	// 생성자가 하는 일이 없음. 은 아니고 하는 일이 있음
	// 하지만 생성자를 호출하지 않으면 문제 발생함.
	virtual void foo() {
		cout << "foo" << endl;
	}
};

int main()
{
	Sample* p = static_cast<Sample*>(operator new(sizeof(Sample)));
	
	// 아래의 생성자 부르는 코드가 없으면 종료됨
	// 왜냐면 foo( ) 함수가 가상 함수라서 , vtptr 초기화 하는 부분이 들어가야 함.
	new (p) Sample;
	p->foo();
}

// 결론 : trivial 의 조건
// 1. 가상함수가 없고,
// 2. 객체형 멤버가 없거나, 객체형 멤버의 생성자가 trivial 하고
// 3. 기반 클래스가 없거나, 기반 클래스의 생성자가 trivial 하고
// 4. 사용자가 만든 생성자가 없다면,
// => 생성자는 trivial 하다.

// 생성자를 컴파일러가 만들어 준다고 해서, 생성자가 하는 일이 없는 것이 아님