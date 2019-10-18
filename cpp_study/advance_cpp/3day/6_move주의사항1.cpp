#include <iostream>
#include <string>
using namespace std;
 
template <typename T, typename U > struct PAIR {
	T first;
	U second;
	PAIR() = default;
	 
	// (1) 생성자를 만들어 보자
	// rvalue, lvalue 모두 받기 위해 const를 붙인다.
	PAIR(const T& a, const U& b) : first(a), second(b) {
		cout << "copy" << endl;
	}
	
	// (3) move를 위해서 새로 만듬
	PAIR(T&& a, U&& b) : first(move(a)), second(move(b)) {
		cout << "move" << endl;
	}

	// C++11 이전 : 생성자 (함수 인자)로 const T&를 주로 사용
	// C++11 이후: move 지원을 위해 2개의 생성자를 만들어야 함.
	// 1. const T&
	// 2. rvalue refence 버전: move 위해


};

int main()
{
	PAIR<int, int> p1(3, 4);

	string s1 = "hello";
	string s2 = "world";
	PAIR<string, string> p2(s1, s2);
	cout << "----" <<endl;
	// (2) move 하더라도  생성자의 타입이 const를 받기 때문에 복사가 됨
	PAIR<string, string> p3(move(s1), move(s2));
	cout << s1 << endl;
}