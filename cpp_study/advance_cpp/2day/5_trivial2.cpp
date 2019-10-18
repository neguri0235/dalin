#include <iostream>
#include <type_traits>

using namespace std;

class Sample1 {
public:
	virtual void foo() {
		cout << "foo" << endl;
	}
	Sample1() {} // 아무일도 안하지만 trivial 하지 않음.(컴파일러가 모름)
};

class Sample2 {
public:
	void foo() {
		cout << "foo" << endl;
	}

	Sample2() = default; // 아무일도 안하는 것은 컴파일러가 알 수 있음. trivial 함. 그래서 이 방법을 추천
};


int main()
{
	// trivial 인지 확인하는 함수
	cout << is_trivially_default_constructible_v<Sample1> << endl;
	cout << is_trivially_default_constructible_v<Sample2> << endl;
}
