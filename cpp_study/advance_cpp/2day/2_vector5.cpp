#include <iostream>
#include <vector>
using namespace std;


int main()
{
	vector<int> v1(10);
	vector<bool> v2(10);

	auto a1 = v1[0];
	auto a2 = v2[0];

	cout << typeid(a1).name() << endl;
	cout << typeid(a2).name() << endl;

	// 핵심 1
	// modern effective c++. vector<bool> 이 반환하는 것은 bool 이 아님.
	/*
	class std::_Vb_reference<struct std::_Wrap_alloc<class std::allocator<unsigned int> > >
	*/

	for (auto a : v1) 
		cout << a << endl;

	// 핵심 2: range for 를 사용하면, auto& 사용 못함. 왜냐면 임시 객체이므로
	// 컨테이너가 temporary(rvalue)를 반환하는 경우가 있음. auto&&(forwarding reference)가 좋음
	//for (auto& a : v2)  // error
	for (auto&& a : v2)
		cout << a << endl;
}