#include <iostream>

using namespace std;

class Vector {
public:
	//  (2) 
	///Vector(int sz) {}
	explicit Vector(int sz) {}
};
// (1)
// call by value 로 인자 전달 . copy initialization 사용
// 아래 표현은 가능하지만, 위험함.  타입이 다른데 전달 되므로
// Vector v  = 10 ; 과 같음. 
void foo(Vector v) {}


void goo(shared_ptr<int> sp, int n) {

}

int main()
{
	Vector v1(10);   // ok - 직접 초기화 direct initialization
	// Vector v2 = 10;  //ok - 복사 초기화 copy initializatoin (= 로 초기화) error . (2) 처럼 변경하면 에러남 
	// foo(10); error
	//goo(new int, hoo()); // error 

	shared_ptr<int> sp = new int; // explicit 때문에 에러
	shared_ptr<int> sp(new int); // ok
}
