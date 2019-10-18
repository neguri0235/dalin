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

int main() {
    const Point pt;
	const Point* p1 = reinterpret_cast<const Point*>(&reinterpret_cast<char&>(const_cast<Point&>(pt)));
	
	// 이렇게되 되지만, const 속성이 없어지므로 const를 붙여줘야 한다.
	Point* p2 = reinterpret_cast< Point*>(&reinterpret_cast<char&>(const_cast<Point&>(pt)));
	cout << p1 << endl;
}