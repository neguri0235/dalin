#include <iostream>

using namespace std;

template<typename T>
class xunique_ptr {
	T* obj;
	int* ref;  // 참조 계수를 관리할 포인터
public:
	xunique_ptr(T* p = 0) : obj(p), ref(new int(1)) {}
	~xunique_ptr() {
		if (--(*ref) == 0) {
			delete obj;
			delete ref;
		}
	}
	T* operator->() { return obj; }
	T& operator*() { return *obj; }

	// 참조 계수 증가를 위해 복사 생성자를 만듬
	xunique_ptr(const xunique_ptr& p) : obj(p.obj), ref(p.ref) {
		++(*ref);
	}
};

int main()
{
	xunique_ptr<int> p1 = new int;
	*p1 = 10;
	cout << *p1 << endl;

	xunique_ptr<int> p2 = p1;
	cout << "--" << endl;
}