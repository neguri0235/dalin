#include <iostream>

using namespace std;

template <typename T> struct xdefault_delete{
	void operator() (T* p)  const {
		static_assert(sizeof(T) > 0, "implete type!!");
		delete p;
	}
};

struct Freer {
	void operator()(void* p) {
		cout << "Free" << endl;
		free(p);
	}
};

template<typename T, typename D = xdefault_delete<T>>
class xunique_ptr {
	T* obj;
public:
	explicit xunique_ptr(T* p = 0) : obj(p) {}
	~xunique_ptr() {
		D d;
		d(obj);
	}
	T* operator->() { return obj; }
	T& operator*() { return *obj; }

	xunique_ptr(const xunique_ptr&) = delete;
	xunique_ptr& operator = (const xunique_ptr& p) = delete;
};

int main()
{
	// 이렇게 할 경우, 삭제자를 만들어야 하는데, 삭제자를 만들면 삭제자를 관리할 관리 객체가 있어야 함
	// 그래서 함수 객체를 사용한다. 
	// 삭제자 변경을 템플릿 인자로 
	xunique_ptr<int> p1(new int);
	xunique_ptr<int, Freer> p2((int*)malloc(100));

	// 생성자 인자로 변경
	shared_ptr<int> sp1(new int);
	shared_ptr<int> sp1((int*)malloc(100), free);
}