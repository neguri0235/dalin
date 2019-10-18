#include <iostream>
#include <type_traits>

using namespace std;

class Shape {
	virtual void Draw() = 0;
};

int main()
{
	cout << is_abstract<Shape>::value << endl;
}