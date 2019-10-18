#include <iostream>
#include <bitset>
using namespace std;

// 중복되지 않게 난수를 구하고 싶다.
// 전역 변수 필요

// 함수는 동작이 있지만 상태가 없다.
// 함수 객체의 장범 1. 상태를 갖는다.

class URandom {
	//  멤버 데이터를 통해 상태를 표현할 수 있다.
	bitset<10> bs;
public:
	URandom() { bs.set(); }

	void reset() { bs.set(); }

	int operator()() {
		if (bs.none())  return -1;
		int k = -1;
		while (!bs.test(k = rand() % 10));
		rand() % 10;
		return k;
	}
};
/*
int random() {
	return rand() % 10;
}
*/
int main()
{
	URandom random;
	for (int i = 0; i < 10; i++) {
		cout << random() << endl;
	}
}