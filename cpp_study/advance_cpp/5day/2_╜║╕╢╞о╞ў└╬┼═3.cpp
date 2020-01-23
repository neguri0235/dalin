#include <iostream>

using namespace std;

// 범용적으로 사용하기 위해 template으로 만듬

template<typename T>
class xunique_ptr {
	T* obj;
public:
	xunique_ptr(T* p = 0) : obj(p) {}
	~xunique_ptr() { 
		delete obj; 
	}
	T* operator->() { return obj; }
	T& operator*() { return *obj; }
};

int main()
{
	xunique_ptr<int> p1 = new int;
	*p1 = 10;
	cout << *p1 << endl;

	xunique_ptr<int> p2 = p1;
	cout << "--" << endl;
}