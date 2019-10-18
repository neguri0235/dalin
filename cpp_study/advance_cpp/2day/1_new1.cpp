// https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/include/utils/TypeHelpers.h

/* 
template<typename TYPE>
typename std::enable_if<traits<TYPE>::has_trivial_copy>::type
inline
copy_type(TYPE* d, const TYPE* s, size_t n) {
	memcpy(d, s, n * sizeof(TYPE));
}

template<typename TYPE>
typename std::enable_if<!traits<TYPE>::has_trivial_copy>::type
inline
copy_type(TYPE* d, const TYPE* s, size_t n) {
	while (n > 0) {
		n--;
		new(d) TYPE(*s);
		d++, s++;
	}
}
*/
// 103.page
#include <iostream>

using namespace std;

class Point {
	int x, y;
public:
	Point(int a = 0, int b = 0) :x(a), y(b) {
		cout << "Point()" << endl;
	}

	~Point() { cout << "~Point()" << endl; }

};
/*
int main()
{
	// 1. 메모리를 할당
	// 2. 생성자를 호출
	Point* p1 = new Point(1, 2);

	// 1. 소멸자 호출
	// 2. 메모리 해지
	delete p1;
}
*/
int main()
{
	// 메모리 할당과 생성자 호출의 분리
	// 1. 메모리 할당 . C의 mallock 과 유사 ( 생성자는 불리지 않음)
	Point* p2 = static_cast<Point*>(operator new(sizeof(Point)));
	cout << p2 << endl;

	// 2. 할당된 메모리에 생성자 호출 - Placement new 라는 기술임
	// new Point(1, 2); 메모리 할당 +  생성자 호출		
	new (p2) Point(1, 2);   // 생성자만 호출

	// 3. 소멸자만 호출
	p2->~Point();  // 메모리 해지 없이 소멸자만 호출. 생성자는 p2->Point(1,2) 처럼 못 부름.
	
	// 4. 소멸자 호출 없이 메모리만 해지
	operator delete(p2);
	
}