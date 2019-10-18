#include <iostream>

using namespace std;

/*
int main()
{
	int n = 10;

	// int 4 byte, double : 8 byte . 하지만 주소의 크기는 같음.

	//double* p = &n;  // (1) C 언어는 허용, 단 경고는 발생
	                 // (2) C++는 암시적 변환이 안되어서 에러 발생
	double*p = (double*)&n; // (3) C++에서 명시적 형변환 사용
	
	*p = 3.4;  // (4) n 은 4 바이트였는데, p 는 double pointer이므로 8 바이트 공간임. 
	           // 그래서 n이 처음 할당한 4바이트가 아닌 8 바이트 공간에 값을 쓰려함. 
	           // 결국 빌드 시점엔 문제 없지만, 실행 시 문제 발생 => C++는 4개의 캐스팅 제공
}
*/
/*
int main()
{
	const int c = 10;    // (0) . 컴파일 시점에는 무조건 10으로 치환됨.
	//int* p = &c;       // (1) error. 상수의 주소를 비상수 포인터에 담을 수 없음.
	int*p = (int*)&c;    // (2) C 스타일 명시적인 캐스팅. 
	*p = 20;
	cout << c << endl;    // 10
	cout << *p << endl;   // 20
}
*/

int main()
{
	int n = 10;
	const int c = n;      // (0) 컴파일러가 c 가 10이라는 사실을 알지 못함. 
	//int* p = &c;       // (1) error. 상수의 주소를 비상수 포인터에 담을 수 없음.
	int*p = (int*)&c;    // (2) C 스타일 명시적인 캐스팅. 
	*p = 20;
	cout << c << endl;    // 20
	cout << *p << endl;   // 20
}