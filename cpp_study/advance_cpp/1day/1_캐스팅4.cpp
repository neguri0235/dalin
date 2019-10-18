#include <iostream>

using namespace std;

struct A { int a; };
struct B { int b; };
struct C : public A,  public B{ int c; };


int main()
{

	/*
	ccc 의 메모리 구조
	|a					|  1000
	|b					|  1004
	|c					|
	
	*/

	C ccc;
	A* pA = &ccc;  // 1000
//	B* pB = &ccc; // 1004

//	B* pb = (B*)&ccc; //1004
//	B* pB = static_cast<B*>(&ccc); //1004
						// &ccc 주소에서 B의 위치를 찾아서 주소 변환
						// 해당 주소에 B가 없으면 연관성 없어서 에러
						// 그래서 컴파일 할때, &ccc + sizeof(A) 이렇게 해서 4바이트 커짐
	B* pB = reinterpret_cast<B*>(&ccc); //1000
					// & ccc주소를 무조건 B 처럼 생각. 컴파일 시점에 하는 

	pB->b = 100;  // 이렇게 하면 a에 100이 들어감 하면
	cout << &ccc << endl;
	cout << pA	 << endl;
	cout << pA->a	 << endl;  // 100 들어가 있음. 
	cout << pB	<< endl;
}