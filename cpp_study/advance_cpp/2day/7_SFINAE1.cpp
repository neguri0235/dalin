// 215 page

#include <iostream>

using namespace std;

//template<typename T> void foo(T a) { cout << "T" << endl; }
//void foo(int			a) {	cout << "int" << endl; }
//void foo(double a) {	cout << "double" << endl; }
//void foo(char a) {	cout << "char" <<endl; }
//void foo(short a) {	cout << "short" << endl; }
void foo(...) {	cout << "..." << endl; }



int main()
{
	foo(10);
	// 1. int
	// 2. T -> template 
	// 3. error. 모호한 변환이라고 나옴
}