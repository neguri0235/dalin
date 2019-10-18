#include <iostream>
using namespace std;

// 컴파일러는 컴파일 시에 모든 가상함수의 주소를 메모리에 보관해야 함.
// 가상 함수가 세개면 4개 크기의 가상함수 테이블이 생성됨.
void* animal_table[] = {		Animal_RTTI 정보, &Animal::Foo, &Animal::Goo, &Animal::Cry};

class Animal {
	int age;
	void* vtptr;
public:
	Animal() : vtptr(animal_table){}

	virtual void Foo() {}
	virtual void Goo() {}
	virtual void Cry() { cout << "1" << endl; }
};
void* dog_table[] = { Dog_RTTI 정보, &Animal::Foo, &Animal::Goo, &Animal::Cry };

class Dog : public Animal {
	int color;
	void* vtptr;
public:
	Dog() :vtptr(dog_table) {}
	void Cry() {
		cout << "2" << endl;
	}
};

int main()
{
	Animal a;
	Dog		d;
	Animal *p = &d;
	p->Cry(); // p->vtptr[3](p); 라는 기계어 코드 생성
}
