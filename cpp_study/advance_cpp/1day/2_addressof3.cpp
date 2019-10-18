#include <iostream>
using namespace std;

class Point {
	int x, y;
public:
	// 주소 연산자를 재정의
	Point* operator&()  const {
		return nullptr;
	}
};

template<typename T> 
T* xaddressof(T& obj)  {   // 주소를 가져와야 하니까, 복사가 아닌 참조로 와야 함.
	// 1 . 상수성 제거
	//T* p = const_cast<T&>(obj);
	// 2. 다른 타입으로 캐스팅
	//T* p = &reinterpret_cast<char&>(const_cast<T&>(obj));
	// 3. 원래의 타입으로 복원

//	T* p = reinterpret_cast<T*>( &reinterpret_cast<char&>(const_cast<T&>(obj)));

	T* p = reinterpret_cast<T*>(   // const Point* 로 변환
				&const_cast<char&>(  // const volatile 제거. volatile 넣은 이유는 원본에 volatile이 있을 수 있어
				reinterpret_cast<const volatile char&>(obj)));

	return p;
}

int main() {
	const Point pt;
	const Point* p1 = reinterpret_cast<const Point*>(&reinterpret_cast<char&>(const_cast<Point&>(pt)));

	// 이렇게되 되지만, const 속성이 없어지므로 const를 붙여줘야 한다.
	Point* p2 = reinterpret_cast<Point*>(&reinterpret_cast<char&>(const_cast<Point&>(pt)));
	cout << p1 << endl;
	cout << p2 << endl;

   const Point* p3 = xaddressof(pt);
	cout << p3 << endl;

}