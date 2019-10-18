#include <iostream>

using namespace std;

class Empty {};
class PAIR {
	Empty e;
	int n;
};

// EBCO - empty base class optimization
//					empty 클래스를 기반 클래스로 사용하면 크기가 0으로 계산된다.
class PAIR2 : public Empty {
	int n;
};

int main() {
	cout << sizeof(Empty) << endl;  //1 
	cout << sizeof(PAIR) << endl;   //8 
	cout << sizeof(PAIR2) << endl;  //4
}