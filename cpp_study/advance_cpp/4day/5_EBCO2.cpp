
#include <iostream>

using namespace std;

class Empty {};

template<typename T, typename U> struct PAIR {
	T first;
	U second;

	PAIR() = default;

	template<typename A, typename B>  // (2) 별도의template로 분리 해야 함
	//PAIR( A&& a, B&& b) { // (1) < 이렇게 하면 forwardig 이 아님. 
	PAIR( A&& a, B&& b) :	first(std::forward<A>(a)), 
													second(std::forward<B>(b)){ // (3) 초기화 리스트로 분리
		//first = std::forward<A>(a);
		//second = std::forward<B>( b);
	}

	T& getValue1() { return first; }
	U& getValue2() { return second; }
};

int main() {
	PAIR<int, int> p(4, 5);

	PAIR<Empty, int > p2;
	cout << sizeof(p2) << endl; // 8 나옴. empty 이니 4면 좋은거 아닌가? 
}