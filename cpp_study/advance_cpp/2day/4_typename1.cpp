#include <iostream>
using namespace std;

class AAA
{
public:
	typedef int DWORD;
	static int value;
};

int AAA::value = 0;

template<typename T> void foo(T t) {
	// (1) AAA 클래스 안에 있는 DWORD를 사용하는 것 : int n
	AAA::DWORD n;

	// (2) T 가 임의의 타입이라서 static 멤버 변수인지 typedef 인지 알 수 없음
	//T::DWORD b; 에러남.

	//(3) T::이름 => 무조건 static 변수로 해석
	// typename T:: 이름 => "이름"을 static 변수가 아닌 타입으로 해석해야 함.
	int n2 = T::value;

	// (4) typename을 빼면 빌드 에러나 발생하고, typename이 반드시 필요함
	typename T::DWORD n3;
}

int main()
{
	AAA	a;
	foo(a);
}