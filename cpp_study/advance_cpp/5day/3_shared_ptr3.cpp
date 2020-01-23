#include <iostream>
#include <memory>

using namespace std;

class Point {
	int x, y;
public:
	Point(int a = 0, int b = 0) { cout << "Point()" << endl; }
	~Point() { cout << "~Point()" << endl; }
};

// (2) new를 재정의해서 얼만큼 할당하는지 확인하자
void* operator new(size_t sz) {
	cout << "new: " << sz << endl;
	return malloc(sz);
}

// (5) make_shared 의 원리를 생각해 보자
/*
template<typename T,  typename ... ARGS> 
shared_ptr<T> xmake_shared(ARGS&& ... args) {
	void* p = operator new(sizeof(T) + sizeof(관리객체));

	// 객체 생성자 호출
	new (p) T(std::forward<ARGS>(args) ...);

	// 관리객체 생성자 호출
	shared_ptr<T> sp;
	sp.reset(p, ((char*)p) + sizeof(T));
	return sp;
}
*/

int main()
{
	// (1) 아래 코드는 동적 메모리 할당을 몇번 하게 될까요? 
	// (3) 2번 할당됨 : 객체 할당  + 관리 객체(ref counter 등) 할당
	shared_ptr<Point> sp1(new Point(1, 2));
	cout << "---" << endl;

	// (4) 메모리를 한번에 할당. 메모리 파편화 현상이 줄어듬
	shared_ptr<Point> sp2 = make_shared<Point>(1, 2);

	// make_shared 장점
	// 1. 객체 + 관리 객체를 한번에 할당하므로 "메모리 파편화" 현상이 줄어든다.
	// 2. 안전하다

	foo(shared_ptr<int>(new int), goo());
	// 1. new int
	// 2. goo()
	// 3. shared_ptr 만들기 
	// 순서로 실행되다가 goo에서 예외 나오면 메모리 누수

	foo(make_shared<int>(), goo());  // 메모리 누수가 없다.

	foo(new int, goo()); //안좋은 코드
	// 그래서 shared_ptr<int.> = new int;를 하지 못하는 이유
}
int goo() { return 0; }
void foo(shared_ptr<int> sp, int n) {}
