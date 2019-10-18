#include <iostream>
#include <list>
#include <vector>

// >> ºôµå ¾ÈµÊ

using namespace std;

template <typename T>
void xadvance(T& p, int n) {
	if constexpr (is_same_v<decay_t<typename T::iterator_catetory >, 
								random_access_iterator_tag>) {
		p = p + n;
	}
	else {
		while (n--) p++;
	}
}


int main()
{
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	auto p = v.begin();
	xadvance(p, 5);
	cout << *p << endl;
}