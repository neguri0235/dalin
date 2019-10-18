#include <iostream>
using namespace std;
/*
class MaxObject {
	static int cnt;
public:
	MaxObject() { if (++cnt > 5) throw 1; }
	~MaxObject() { --cnt; }
};
int MaxObject::cnt = 0;
class Truck : public MaxObject{
};

class Car : public MaxObject {
};

int main() {
	Truck t1[3];
	Car		t2[2];
}
*/

// CRTP를 사용해서 서로 다른 기반 클래스를 만드는 코드

template<typename T>
class MaxObject {
	static int cnt;
public:
	MaxObject() { if (++cnt > 5) throw 1; }
	~MaxObject() { --cnt; }
};

// 클래스 템플릿의 static 멤버를 외부에서 선언하는 경우
template<typename T>  int MaxObject<T>::cnt = 0;

class Truck : public MaxObject <Truck>{
};

class Car : public MaxObject <Car>{
};

int main() {
	Truck t1[3];
	Car		t2[3];
}