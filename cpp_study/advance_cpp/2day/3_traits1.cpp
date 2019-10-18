#include <iostream>

using namespace std;

// Traits (특질):  타입의 다양한 속성을 조사하는 기술

template<typename T> void printv(T v) {
	// (1) 이런걸 할 수 있을 까? 
	if (T 가 포인터라면) {
		cout << v << ' ' << *v << endl;
	}
	else {
		cout << v << endl;
	}
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
