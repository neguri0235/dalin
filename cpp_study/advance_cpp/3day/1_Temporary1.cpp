//1_temporary.cpp

//https://github.com/WebKit/webkit/blob/master/Source/WTF/wtf/Scope.h
/*
	ScopeExit(const ScopeExit&) = delete;
	ScopeExit& operator=(const ScopeExit&) = delete;
	ScopeExit& operator=(ScopeExit&&) = delete;
*/

#include <iostream>

using namespace std;

class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {
		cout << "Point()" << endl;
	}
	~Point() { cout << "~Point()" << endl; }
	void set(int a, int b) { x = a;  y = b; }
};

// 핵심 1.  temporary를 만드는 방법
//          	2. temporary의 수명
int main()
{
	//Point p(1, 1);  // (1)  이름이 있는 객체 (named object) . 단일 문장을 넘어서 메모리 존재
								// (2) 수명: 객체를 생성한 블럭의 끝

	//Point (1, 1);  // (3) unnamed object, temporary(object) 
							// (4) 수명: 문장의 끝. 이름이 없기 때문에 다른 곳에서 사용 불가
	Point(1,1), cout<<"x"<<endl; // (5) 이렇게 만들면 객체의 수명을 확실히 알수 있음
	cout << "------" << endl;
}