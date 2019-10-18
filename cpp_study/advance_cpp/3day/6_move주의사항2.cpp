#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Data {

};

class Test {
	Data data;
public:
	// C++11 이전에는 아래 한개면 됨
	void SetData(const Data& d) {	data = d;	}

	// C++11 이후에는 아래처럼 move 지원하는 것도 만들어 줘야 함
	void seData(Data&& d) { data = move(d); }
};

int main()
{
	vector<string> v;
	string s1 = "Hello";

	v.push_back(s1);
	cout << s1 << endl;  // Hello 출력

	v.push_back(move(s1));
	cout << s1 << endl;   // Hello 출력 안됨
}