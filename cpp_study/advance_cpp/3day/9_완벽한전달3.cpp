#include <iostream>

using namespace std;

void foo(int a) {}
void goo(int& a) { a = 100; }

// 완벽한 전달(perfect forwarding)
// 도착한 인자를 다른 함수에게 완벽하게 전달해 주는 것

// 특정 함수의 성능을 측정하는 함수
template<typename F, typename T>  
 
// (2) 복사로 인자를 보내면 모두 가능
//void chronometry(F f, T arg) {

// (3) 참조로 보냄. 이렇게 하면 10을 전달할 수 없음. chronometry(foo, 10); 에서 에러
 //void chronometry(F f, T& arg) { 

 // (4) 10을 전달하기 위해 const를 붙여줌.  하지만 chronometry(goo, n);  에서 에러 발생
// 그리고 값도 변경 못함
void chronometry(F f, const T& arg) {
	cout << "current time" << endl;
	f(arg);
	cout << "ellapsed time" << endl;
}

int main()
{
	int n = 10;
	//foo(10);
	chronometry(foo, 10);
	cout << "------------------" << endl;
	chronometry(goo, n); // (1) goo 이후에 n이 100으로 변경되길 기대하지만,그렇지 않음
	cout << "------------------" << endl;
	cout << n << endl;
}
