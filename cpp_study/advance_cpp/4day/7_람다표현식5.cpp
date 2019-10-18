#include <iostream>
#include <type_traits>

using namespace std;

int main()
{
	auto f = [](int& a) {return a; };
	int n = 0;

	if (is_lvalue_reference_v<decltype(f(n))>) {
		cout << "����" << endl;
	}
	else {
		cout << "��" << endl;
	}
}