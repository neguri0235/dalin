#include <iostream>
#include <vector>

using namespace std;

class Point {
	int x, y;
public:
	Point(int a, int b)			 : x(a), y(b)		 { cout << "Point()" << endl; }
	Point(const Point& p) : x(p.x), y(p.y) { cout << "Point(const Point)" << endl; }
		~Point() { cout << "~Point" << endl; }
};

int main()
{
	vector<Point> v;
	// v에 1,2 로 초기화된 Point를 넣고 싶다
	// 1. Point 객체 생성 후 넣기 -> 객체 생성(1) + 복사(1)  = 두개 만듬
	//Point p1(1, 2);
	//v.push_back(p1);
	//cout << "--------" << endl;

	// 2. 방법 : move생성자로 복사 -> Point 객체에서 move 생성 안만들었으니 , 결국 두개 만듬
	//Point p1(1, 2);
	//v.push_back(move(p1));

	//cout << "--------" << endl;
	//3.  방법 : 임시 객체 사용 -> 임시 객체 이므로 두개의 객체 생성 (다만 임시 객체이므로 문장 끝에서 파괴)
	// (2) 번 방법과 결과는 동일하지만, 객체를 바로 제거하니까 그나마 이게 낫음.
	//v.push_back(Point(1, 2));
	//v.push_back({ 1, 2 }); 
	//cout << "--------" << endl;

	// 4. 방법 : 객체를 외부에서 만들지 말고 vector에서 만들 수 있도록 함
	//					단, 객체를 만들때 필요한 생성자 인자 전달
	v.emplace_back(1, 2);  // 이 함수가 내부적으로 new Point(1,2)를 부름
	// => 결론은 emplace_back 쓰자.
	v.emplace_back(3, 4);
}