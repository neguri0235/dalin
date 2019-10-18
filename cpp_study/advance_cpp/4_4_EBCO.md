``` cpp
class Empty {};
class PAIR {
	Empty e;
	int n;
};

// EBCO - empty base class optimization
//					empty 클래스를 기반 클래스로 사용하면 크기가 0으로 계산된다.
class PAIR2 : public Empty {
	int n;
};

int main() {
	cout << sizeof(Empty) << endl;  //1 
	cout << sizeof(PAIR) << endl;   //8 
	cout << sizeof(PAIR2) << endl;  //4
}
```

``` cpp

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
```
``` cpp

#include <iostream>

using namespace std;

class Empty {};
/*
template<typename T, typename U> struct PAIR {
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
*/

template<typename T, typename U> struct PAIR :public T{
	U second;
	PAIR() = default;
	template<typename A, typename B>
	PAIR(A&& a, B&& b) : T(std::forward<A>(a)),
		second(std::forward<B>(b)) {
	}
	T& getValue1() { return *this; }
	//T& getValue1() { return static_cast<T>(this); }
	U& getValue2() { return second; }
};

int main() {
	PAIR<int, int> p(4, 5);

	PAIR<Empty, int > p2;
	cout << sizeof(p2) << endl; // 8 나옴. empty 이니 4면 좋은거 아닌가? 
}
```

``` cpp

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
```

``` cpp
```