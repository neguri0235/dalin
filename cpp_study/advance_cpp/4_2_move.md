
> Type을 구하기
``` cpp
template<typename T> void foo(T a)
{
	// type traits 기술의 종류

	// 1. 타입 질의 - T의 타입을 구할 수 있다.
	bool b1 = is_pointer<T>::value;     // C++11
	bool b2 = is_pointer_v<T>;				// C++ 14

	//2. 변경된 타입 얻기 - 포인터 이전의 타입을 구하기.
	//remove_pointer<T>::type n;  -> type이 값인지, type인지 모르니 typename을 적어야 함.
	typename remove_pointer<T>::type n;
	remove_pointer_t<T> n2;    //C++ 11
}
```

``` cpp

class Point {
public:
	Point(int a, int b) {}
	Point(const Point& p)		{ cout << "copy" << endl; }
	Point(Point&& p)				{ cout << "move" << endl; }
};


// 템플릿을 만들때 인자를 T&로 할것인가 ? T&&로 할것인가?
// T& : lvalue만 받겠다
// T&& : lvalue와 rvlaue 모두 받겠다

/*
// template <typename T> T&& xmove(T& arg) {  // (1)
template <typename T> T&& xmove(T&& arg) { //(2)
	// xmove(lvalue) : T는 int&
	// xmove(rvalue) : T는 int
		return static_cast<T&&>(arg);
}
*/

template <typename T> remove_reference<T> && xmove(T&& arg) {
	// 위의 문제는 T가 참조를 가지고 있는 것이 문제
	// 그래서 remove_reference를 통해 원래 타입을 가지고 옴
	return static_cast<remove_reference<T> &&>(arg);
}


int main()
{
	Point p1(1, 2);
	Point p2 = p1;
	Point p3 = static_cast<Point&&>(p2); // move
	//Point p4 = move(p3);  move 를 만들어 보자
	Point p4 = move(p3);  //move 1이면 move인데, 2이면 copy가 됨. 원하는 결과가 아님.
	Point p5 = move(Point(1,2));  //move


	// 아래 함수는 어떤 생성자를 호출하나?
	// 1. 인자는 2개인 생성자
	// 2. 복사
	// 3. move
	Point pt = Point(1, 2);

	// C++ 98: 임시객체를 만들고 복사 생성자로 pt에 복사
	// C++11 : 임시 객체를 만들고 move 생성자로 pt에 복사
	// 컴파일러가 최적화 하면서 복사 생성자, move 생성자 호출 생략
	// C++17 : 문법적으로 임시객체를 만들지 않고 인자 2개인 생성자 호출

	/*
		gcc a.cpp -std:c++98 --fno-elide-constructors
		gcc a.cpp -std:c++11 --fno-elide-constructors
		gcc a.cpp -std:c++17 --fno-elide-constructors
	*/
}
```

``` cpp
```

``` cpp
```

``` cpp
```