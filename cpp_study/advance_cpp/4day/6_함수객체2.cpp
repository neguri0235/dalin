#include <iostream>

using namespace std;

// 중복되지 않게 난수를 구하고 싶다.
// 전역 변수 필요

// 함수는 동작이 있지만 상태가 없다.
int random() {
	return rand() % 10;
}

int main()
{
	for (int i = 0; i < 10; i++) {
		cout << random() << endl;
	}
}