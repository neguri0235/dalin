#include <iostream>
#include <string>
#include <vector>

using namespace std;

// rule of 0
// 자원 관리는 직접 하는 코드는 만들지 말자.

// const char* => string
// int* buff = vector;
// 그래도 포인터가 필요하면 => 스마트포인터 사용

class People {
	string		name;
	string		addr;
	int			age;
public:
	People(string n, int a, string ad) : name(n), age(a), addr(ad) {
		
	}
	~People() {
	}
};

int main()
{
	People p("kim", 10, "seoul");
}
