#include <iostream>

using namespace std;

// 범용적으로 사용하기 위해 template으로 만듬

template<typename T>
class xunique_ptr {
	T* obj;
public:
	explicit xunique_ptr(T* p = 0) : obj(p) {}
	~xunique_ptr() {
		delete obj;
	}
	T* operator->() { return obj; }
	T& operator*() { return *obj; }

	// 복사와 대입을 금지
	// 성능 저하 별로 없음.
	xunique_ptr(const xunique_ptr&) = delete;
	xunique_ptr& operator = (const xunique_ptr& p) = delete;
};

int main()
{
	// xunique_ptr<int> p1 = new int;  // error explicit 때문에 에러 남
	 xunique_ptr<int> p1(new int);
	*p1 = 10;
	cout << *p1 << endl;

	//xunique_ptr<int> p2 = p1;  // 복사 생성자

	cout << "--" << endl;
}