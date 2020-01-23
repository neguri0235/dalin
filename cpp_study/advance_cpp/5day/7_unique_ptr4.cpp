#include <iostream>

using namespace std;

template <typename T> struct xdefault_delete {
	void operator() (T* p)  const {
		static_assert(sizeof(T) > 0, "implete type!!");
		delete p;
	}
};

/*
struct Freer {
	void operator()(void* p) {
		cout << "Free" << endl;
		free(p);
	}
};
*/


template<typename T, typename D = xdefault_delete<T>>
class xunique_ptr {
	T* obj;
	D dx;
public:
	explicit xunique_ptr(T* p = 0, const D& d = D()) : obj(p), dx(d) {}
	~xunique_ptr() {
		dx(obj);
	}
	T* operator->() { return obj; }
	T& operator*() { return *obj; }

	xunique_ptr(const xunique_ptr&) = delete;
	xunique_ptr& operator = (const xunique_ptr& p) = delete;
};

int main()
{
	// malloc 했으므로 삭제자 전달해야 함
	// 아래는 에러,객체가 아닌 타입이 들어거야 함.
	// xunique_ptr<int, [](int* p) {free(p); } > p1((int*)malloc(100));

	// 아래도 문제. C++ 20부터 가능
	//xunique_ptr<int, decltype([](int* p) {free(p); } )> p1((int*)malloc(100));

	/*
	auto f1 = [](int a, int b) { return a + b; };
	decltype(f1) f2;  // error . xxx 안에 디폴트 생성자가 없다.
	decltype(f1) f2(f1);
	*/

	// (3) 결국 멤버 관리 데이타가 있어야 함.
	auto del = [](int* p) {free(p); };
	xunique_ptr<int, decltype(del) > p1((int*)malloc(100),del);

}