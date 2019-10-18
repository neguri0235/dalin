#include <iostream>

using namespace std;

class Animal {
	// (5) 가상 함수가 있으면, 가상 함수 테이블이 만들어 지고 그 안에 타입 정보가 같이 들어감.
	// 각 각채게 테이블을 가르키게 디어서 빌드 성공
	// 결국 가상 함수가 없는 객체는 dynamic_cast를 사용할 수 없음.
public:
	virtual ~Animal() {

	}
};

class Dog : public Animal {
public:
	void Cry() {}
};

void foo(Animal* p) {
	// (1) 혹시 p 가 Dog 이라면 아래 처럼 하고 싶음
	// p->Cry(); 그런데 에러

	// (2) 그래서 이렇게. Down Casting 가능함. (기반 타입을 파생 타입으로)
	// (3) static cast 이므로 컴파일 시간에 처리하게 되는데, 컴파일 시간에 dog인지 아닌지 모름.
	//Dog* pDog = static_cast<Dog*>(p); // 상속이라는 연관성이 있으므로 컴파일 은 됨.
	//cout << pDog << endl;

	//(4) p가 정말 Dog일때만 성공해야 함
	// 컴파일 시점이 아닌 실행 시간에 조사한 후 캐스팅.
	// 그런데 빌드하면 에러남.
	Dog* pDog = dynamic_cast<Dog*>(p);
	cout << pDog << endl;

}

int main()
{
	Animal a; foo(&a);
	Dog		d; foo(&d);
}


// C++ 캐스팅
// static cast
// reinterpret cast - 컴파일 시간 : 서로 다른 타입에 대해서 캐스팅
// const_cast   - 컴파일 시간
// dynamic_cast 실행 시간(오버헤드가 있음) - 상속 관계에 있을 때만 사용