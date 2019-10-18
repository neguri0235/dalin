// 왜 사용할 까?

#include <iostream>

using namespace std;

class Point {
	int x, y;
public:
	Point(int a , int b) :x(a), y(b) {
		cout << "Point()" << endl;
	}
	~Point() { cout << "~Point()" << endl; }
};

int main()
{
	// Point 객체를 힙에 한개 만들기
	Point* p1 = new Point(0, 0);
	// 힙에 10개 만들기
	
	// Point* p2 = new Point[10];  // 생성자를 부를 수가 없다.
	// 해결 방법 =>

	// 디폴트 생성자가 없는 객체를 여러개 생성하려면,
	// 메모리 할당과 생성자 호출을 분리

	// 1. 메모리 할당
	Point* p2 = static_cast<Point*>(operator new (sizeof(Point) * 10));
	// 2. 생성자 호출
	for (int i = 0; i < 10; i++) {
		new(&p2[i]) Point(0, 0);
	}

	//  사용 후 소멸자 호출의 파괴
	for (int i = 0; i < 10; i++) {
		p2[i].~Point();
	}
	operator delete(p2);

	// 메모리 해지 할때, 아래처럼 사용하면 알수 없는 동작을 하게 됨
	// delete []p2; 
}