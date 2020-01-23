#include <iostream>
#include <memory>

using namespace std;

int main()
{
	unique_ptr<int> up1(new int);
	unique_ptr<int> up2(new int[10]); // C++ 14

	*up1 = 10;
	//up1[0] = 10;  //error

	*up2 = 10;   // error
	up2[0] = 10;  // ok

	// 다음중 에러는?

	shared_ptr<int> sp(new int);
	unique_ptr<int> up(new int);

	//shared_ptr<int> p1 = up; // error
	shared_ptr<int> p2 = move(up);
	//unique_ptr<int> p3 = sp; //error
	//unique_ptr<int> p3 = move(sp);  // error
}

//shared_ptr<int> p2 = move(up);
//unique_ptr<int> p3 = sp; //error

unique_ptr<int> AllocBuffer(int size) {
	return unique_ptr<int>(new int);
}

shared_ptr<int> ret1 = AllocBuffer(100);
unique_ptr<int> ret1 = AllocBuffer(100);

int[3] a;  // a의 type은 int[3];
int[4] b; // b의 type은 int[4];

//

int main()
{
	int n = 0;
	int* p = &n;
	shared_ptr<int> p(&n);
	observer_ptr<int> p(&n); ///c++20;
}