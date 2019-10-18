//73 page
#include <iostream>

using namespace std;

// Empty 클래스, non static member data와 가상 함수가 없는 클래스
class Empty {
	public:
	~Empty() {}
};

int main()
{
	Empty e;
	cout << sizeof(e) << endl;  //  1

	// 핵심: empty class의 크기는 1

}