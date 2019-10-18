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
	Point pt;
	cout << &pt << endl;  // & 연산자를 재 정의 하였기 때문에 주소를 가지고 올 수 없음. pt.operator&()

	Point* p1 = &pt;
	cout << p1 << endl;  
	cout << "----" << endl;
	//step 1. char* 타입에 담아 보자
	char* p2 = reinterpret_cast<char*>(&pt); // &pt 이므로 0.
	
											 //char* p3 = &reinterpret_cast<char>(pt); 
									// 1.  reinterpert_cast는 값 캐스팅에는 사용 불가
									// 2.	값 캐스팅은 임시 객체를 만들기 때문에 , 주소 가지고 오는 것은 의미 없다. 
	
	
	char* p4 = &reinterpret_cast<char&>(pt);  //  이렇게 하면 주소를 가지고 올 수 있음
	cout << p4 << endl;
	cout << "----" << endl;
	// step 2. Point type에 넣어 보자
	Point* p5 = reinterpret_cast<Point*>(&reinterpret_cast<char&>(pt));
	cout << p5 << endl;
	Point* p6 = &reinterpret_cast<Point&>((pt));
	cout << p6 << endl;   // 이렇게 직접하면 Point& 때문에 0 이 나옴.

	// char 이 아닌 int로 하여도 됨
	Point* p7 = reinterpret_cast<Point*>(&reinterpret_cast<int&>(pt));
	cout << p7 << endl;
}