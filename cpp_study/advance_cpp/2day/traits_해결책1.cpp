#include <iostream>
#include <type_traits>
using namespace std;


template<typename T> void printv(T v)
{
	// (1) 이부분이 컴파일되어서 문제임.
	//if (std::is_pointer<T>::value) {
	
	// (2) C++17 에서 나오는 정적 if 문
	// 템플릿에서 조건을 만족하지 않으면 코드를 생성하지 않는다.
	if  constexpr (std::is_pointer<T>::value) {
		cout << v << " : " << *v << endl;
	}
	else {
		cout << v << endl;
	}
}


 void printv(int v)
{
	 // (3) 컴파일러는 아래와 같은 함수를 만들어 냄.
	 // 조건이 맞지 않으므로, 실행이 되는것이 아니고 아예 코드 생성 안됨.
	 // /std:c++latest 를 추가해서 빌드해야함. (혹은 std:c++17)
	if  constexpr (false) {
		
	}
	else {
		cout << v << endl;
	}
}



int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}