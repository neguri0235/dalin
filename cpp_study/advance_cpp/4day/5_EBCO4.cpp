
#include <iostream>
#include <type_traits>

using namespace std;

class Empty {};

// 아래 코드가 boost library 에 있는 compressed pair 라이브러리

template<typename T, typename U, bool b = is_empty_v<T>>
struct PAIR;
//{
 // 사용하지 않지만 안만들면 안됨. 사용하지 않으므로 {} 없어도 가능
//};

// 조건에 따라 PAIR를 부분 특수화한다.
template<typename T, typename U> struct PAIR <T, U, false>{
	T first;
	U second;
	PAIR() = default;
	template<typename A, typename B>
	PAIR(A&& a, B&& b) : first(std::forward<A>(a)),
		second(std::forward<B>(b)) {
	}
	T& getValue1() { return first; }
	U& getValue2() { return second; }
};


template<typename T, typename U> struct PAIR <T, U, true> : public T {
	U second;
	PAIR() = default;
	template<typename A, typename B>
	PAIR(A&& a, B&& b) : T(std::forward<A>(a)),
		second(std::forward<B>(b)) {
	}
	T& getValue1() { return *this; }
	U& getValue2() { return second; }
};

int main() {
	PAIR<Empty, int > p2;
	cout << sizeof(p2) << endl;
	PAIR<int, int > p3;
	cout << sizeof(p3) << endl;
}