#include <iostream>
#include <memory>

using namespace std;

class Point {
public:
	Point() { cout << "Poit()" << endl; }
	~Point() { cout << "~Poit()" << endl; }
};

void foo(void* p) { cout << "foo" << endl; free(p); }

int main()
{
	// 삭제자 변경
	// new 가 아닌 다른 함수로 메모리 할당한 경우
	// 삭제자를 관리하는 포인터도 필요

	shared_ptr<int> p1(new int);				// p1 소멸자에서 delete
	//shared_ptr<void> p2(malloc (100)); // new 가 아니니 free를 호출해야 함. 그래서 별도로 삭제하는 코드를 만들어야 함
	shared_ptr<void> p3(malloc (100),foo); 
	shared_ptr<void> p4(malloc (100),free); 
	shared_ptr<void> p5(malloc(100), [](void* p) {free(p); });

	// 배열 모양으로 할당
	//shared_ptr<int> p6(new int[10]);// 버그임. delete[] 가 필요
	shared_ptr<int> p6(new int[10], [](int* p) {delete[] p; }); 

	// default_delete<int> : delete 를 수행하는 함수 객체
	// default_delete<int[]> : delete[]
	shared_ptr<int> p7(new int[10], default_delete<int[]>());
	
	// 공식적으로  C++ 17에서 부터 지원
	shared_ptr<int[]> p8(new int[10] );


	shared_ptr<Point[]> p9(new Point[3]);

	// Point* pt = new Point[3];		// 생성자 3번 호출
	// delete  pt;			// 소멸자 한번 호출

	// file open도 처리할 수 있음
	shared_ptr<FILE> sp1(fopen("a.txt", "wt"), fclose);
}
