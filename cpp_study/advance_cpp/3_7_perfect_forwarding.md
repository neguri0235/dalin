### 완벽한 전달 (1)


* 완벽한 전달(perfect forwarding) (1)
> 도착한 인자를 다른 함수에게 완벽하게 전달해 주는 것
>> 결론은 & 나 const 를 붙이는 것으로는 perfect forwarding을 할 수 없음.
``` cpp
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

// => 결론은 & 나 const 를 붙이는 것으로는 perfect forwarding을 할 수 없음.
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
```

### 완벽한 전달 (2)

* 완벽히 전달하려면
1. 인자는 복사본이 생성되면 안된다 - 참조로 전달해야 함.
2. const를 붙여도 안된다.
3. int& 와 int&& 버전의 함수를 2개 제공한다.
4. const int&, const volatime int& 도 추가로 만들어 줘야 한다.

``` cpp
void foo(int a) {}
void goo(int& a) { a = 100; }

// => 아래 두 코드는 perfect forwarding 을 거의 비슷하게 구현한것. 
template<typename F>
void chronometry(F f, int & arg) {
	f(arg);
}

template<typename F>
void chronometry(F f, int&& arg) {
	f(arg);
}
```

### 완벽한 전달 (3)
> 한단계 더 나가자 !
``` cpp
template<typename F> void chronometry(F f, int & arg) {
	f(arg);
}


// main             ->  chronometry         -> hoo(int&&)
// 10(rvalue) 전달  -> int&& arg (lvalue)   ->  다시 rvalue로 속성 변경
template<typename F> void chronometry(F f, int&& arg) {
	// int&& arg = 10;
	// 10 : rvalue, arg: lvalue	
	//f(arg);
	f(static_cast<int&&>(arg));
}

int main()
{
	int n = 10;
	hoo(10);
    // 하지만 여기서 에러 발생 hoo() 에는 && 이 전달되어야 함
	chronometry(hoo, n); 
  	chronometry(hoo, 10);
}
```

### 완벽한 전달 (4)
``` cpp
// 결론
// 1. int&, int&& 로 2개를 만들어야 한다
// 2. int&& 버전에서 다른 함수로 전달할때 rvalue로 캐스팅해서 전달
/*
template<typename F> void chronometry(F f, int & arg) {
	//f(arg);
	f(static_cat<int&>(arg)); // 필요 없는 캐스팅, 있어도 문제 되지 않음.
}

template<typename F> void chronometry(F f, int&& arg) {
	f(static_cast<int&&>(arg));
}
*/

// n (lvalue) 전달 => T: int& t&& :int&
// 10(rvalue) 전달 => T: int, T&& : int&&
// 즉, 아래 템플릿은 2번째 인자가 n 인지 10인지에 따라 위의 2개 함수 생성
template<typename F, typename T> void chronometry(F f, T&& arg) {
	
	// 아래 캐스팅은 ?
	// 2번째 인자에 따라서 다른 캐스팅이 됨

	// 2번째 인자가 10(rvalue)를 보내면 rvalue로 캐스팅
	// 2번째 인자로 n(lvalue)를 보내면 lvalue로 캐스팅
	//f(static_cast<T&&>(arg)); 

	//위 기능을 해주는 함수가 있음
	f(std::forward<T>(arg));
}

int main()
{
	int n = 10;
	//hoo(10);
	// chronometry에서 아무리 전달을 잘 해도 hoo, goo에 전달되는 타입과 일치해야 함
	chronometry(hoo, 10);
    chronometry(goo, n); 
}
```
### 완벽한 전달 (5)
``` cpp
void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}
void koo(int a, int b, int c) {}
void joo() {}

// C++11 가변인자 템플릿
// return 이있을 수도 있고, 없을 수도 있고. 그래서 decltype(aut0)를 붙여줌
template<typename F, typename ... T> 
decltype(auto) chronometry(F f, T&& ...arg) {
	   	return f(std::forward<T>(arg)...);
}

int main()
{
	hoo(1);
	chronometry(hoo, 10);
	chronometry(koo, 10,20,30);
	chronometry(joo);
}
```