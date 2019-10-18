#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	const string s1 = "hello";	// (1) const 객체는 move해도 자원을 그대로 가지고 있음
	//string s2 = s1;
	string s2 = std::move(s1);
	cout << s1 << endl;

	vector<int> v1(10, 3);
	//vector<int> v2 = v1;			// (2) 느림
	vector<int> v2 = std::move(v1);	//(3) 빠름. 포인터만 전달

	cout << v1.size() << endl;
}