#include <iostream>

using namespace std;

//[1_Temporary5.cpp](1_Temporary5.cpp)

class Test {
public:
	// 함수 이름 뒤에 '&'를 붙여 주면, 임시 객체에서만 부를 수 있는지, 일반 객체에서 호출 가능한 함수 인지 구분함.
	// void foo()  { cout << "&" << endl; }  // (1) 임시 객체도 부를 수 있고, 이름 있는 객체도 부를 수 있음
	void foo()  & { cout << "&" << endl; }	// (2) 이름 있는 객체만 부를 수 있음
	void foo()  && { cout << "&&" << endl; }	// (2) 이름 없는 임시 객체 에서만 사용 가능
};

int main()
{
	Test t;
	t.foo();
	Test().foo();  // &&
	((Test*)0)->foo();  // 주소가 있으므로 이름 있는 객체로 판단. Test 객체를 0의 주소로 변경 후 함수 호출
}