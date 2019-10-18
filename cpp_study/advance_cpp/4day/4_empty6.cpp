#include <iostream>
#include <list>
#include <vector>

using namespace std;

>> ºôµå ¸øÇÔ

template <typename T> 
enable_if_t<is_same_v<decay_t<typename T::iterator_catetory >, random_access_iterator_tag> >
 xadvance(T& p, int n) {
	cout << "random ÀÏ¶§" << endl;
	p = p + n;
}

template <typename T> 
enable_if_t<! is_same_v<decay_t<typename T::iterator_catetory>, random_access_iterator_tag> >
xadvance(T& p, int n) {
	cout << "random ¾Æ´Ò¶§" << endl;
	while (n--) ++p;
}

int main()
{
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	auto p = v.begin();
	xadvance(p, 5);
	cout << *p << endl;
}