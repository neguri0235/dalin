``` cpp
struct Animal {
	virtual void Cry() { cout << "Animal cry" << endl; }
	virtual ~Animal() {}
};

struct Dog : public Animal {
	virtual void Cry() { cout << "Dog cry" << endl; }
};

int main() {
	Dog d;				d.Cry();
	Animal& a1 = d; a1.Cry();
	Animal a2 = d; a2.Cry();   // 객체 슬라이싱이 발생하고, a2에는 dog 이 아닌 animal 부분남 남는다.
}
```
#include <iostream>

using namespace std;

struct Animal {
	virtual void Cry() { cout << "Animal cry" << endl; }
	virtual ~Animal() {}
};

struct Dog : public Animal {
	virtual void Cry() { cout << "Dog cry" << endl; }
};


Dog d;
Animal	f1() { return d; }   // 값 리턴. 왼쪽에 올수 없다.  -		move 호출 non polymorphic

Animal&& f2() {   // 왼쪽에 올수 없다. -- move polymorphic
	return move(d);
} 

Animal& f3() { return d; } // 참조 리턴 . 왼쪽에 올 수 있다.  - copy 호출

int main() {

	f1().Cry(); // animal cry
	f2().Cry(); // dog cry
	f3().Cry(); // dog cry

//	Dog d1 = f1(); // move
//	Dog d2 = f2(); // move
//	Dog d3 = f3(); //move	
}


// expression : 하나의 값으로 계산 될 수 있는 코드 모음

// lvalue: 표현식의 결과가 lvalue 참조
// xvalue: 표현식의 결과가 rvalue 참조
// prvalue: 표현식의 결과가 값(literal , 임시 객체)

f1(); // 값 반환
f2(); // rvalue 참조 변환
f3(); //lvalue 참조 변환

int main() {

	class Point {};

	int n = 10;
	static_cast<int&>(n) = 10;		// 메모리가 반환 . lvalue 가능
	static_cast<int&&>(n) = 10;   // n . 이라는 메모리는 있음. 하지만 lvalue는 아님. 값 대입 불가. xvalue 라고 함
	n + 1 = 10;			// 값 11 반환. lvalue 안됨


	Point pt;
	// 아래 코드는 lvalue를 _rvalue(xvalue)로 캐스팅하고 있음.
	Point pt2 = static_cast<Point&&>(pt);
}
``` cpp
```
``` cpp
```
