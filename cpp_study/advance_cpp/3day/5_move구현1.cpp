#include <iostream>
#include <string>

using namespace std;

class People {
	string		name;
	int			age;
	char*		addr;
public:
	People(string n, int a, const char* ad) : name(n), age(a) {
		addr = new char[strlen(ad) + 1];
		strcpy(addr, ad);
	}
	~People() {
		delete [] addr;
	}
};

int main()
{
	People p1("kim", 10, "seoul");
}