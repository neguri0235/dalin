## Trivial
> 하는 일이 없다 ?

``` cpp
class Sample {
public:
	// 생성자가 하는 일이 없음!은 아니고 하는 일이 있음
	// (4) 만약 가상함수가 아니라면, vtptr 초기화가 필요치 않으므로 문제 발생하지 않음.
	virtual void foo() {
		cout << "foo" << endl;
	}
};

int main()
{
	// (1) 메모리만 할당
	Sample* p = static_cast<Sample*>(operator new(sizeof(Sample)));

	// (2) 생성자 호출 없이 가상 함수 호출 -> 프로그램 종료
	p->foo();
	
	// (3) 왜냐면 foo( ) 함수가 가상 함수라서 , 생성자에서 vtptr 초기화 하는 부분이 들어가야 함.
	new (p) Sample;
}
```
* trivial 의 조건
 1. 가상함수가 없고,
 2. 객체형 멤버가 없거나, 객체형 멤버의 생성자가 trivial 하고
 3. 기반 클래스가 없거나, 기반 클래스의 생성자가 trivial 하고
 4. 사용자가 만든 생성자가 없다면 => 생성자는 trivial 하다.

* 생성자를 컴파일러가 만들어 준다고 해서, 생성자가 하는 일이 없는 것이 아님


> 클래스에 대해서 trivial 한지 확인해 보자

``` cpp
class Sample1 {
public:
	virtual void foo() {
		cout << "foo" << endl;
	}
	Sample1() {} 
	//(2) 아무일도 안하지만 trivial 하지 않음.
	//(컴파일러가 알수 없음 - header와 source가 분리되어 있는 경우)
};

class Sample2 {
public:
	void foo() {
		cout << "foo" << endl;
	}

	Sample2() = default; 
	// (3) 아무일도 안하는 것은 컴파일러가 알 수 있음. trivial 함
	// 그래서 사용자가 생성자를 직접 만드는 것보다 이 방법을 추천
};

int main()
{
	// (1) trivial 인지 확인하는 함수. 표준에 정의되어 있음
	cout << is_trivially_default_constructible_v<Sample1> << endl;
	cout << is_trivially_default_constructible_v<Sample2> << endl;
}
```

### trivial 의 예
[TypeHelpers](https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/include/utils/TypeHelpers.h) 에 나온 예제
``` cpp
// 선택 (1) 복사할때 모든 요소를 한번에 복사할 것인지,
// 선택 (2) 아니면 하나씩 루프를 돌면서 복사할 것인지.
template<typename T>
void copy_type(T* dst, T* src, int sz) {
	if (is_trivially_copyable_v<T>) {
		// 복사 생성자가 하는 일이 없음
		cout << "복사 생성자가 하는 일이 없음" << endl;
		memcpy(dst, src, sizeof(T)*sz);
	}
	else {
		cout << "복사 생성자가 하는 일이 있으면 모든 요소에 대해 복사" << endl;
		while (sz--) {
			new (dst) T(*src);
			++dst, ++src;
		}
	}

}

struct Point1{
	int x, y;
};

struct Point2 {
	int x, y;
	Point2(const Point2& p) : x(p.x), y(p.y){
	}
	Point2() = default;
};

struct Point3 {
	int x, y;
	Point3(const Point3 & p) = default;
	Point3() = default;
};


int main()
{
	char s1[10] = "Hello";
	char s2[10];

	// (1)일반화 버젼을 만들자
	//strcpy(s2, s1);

	copy_type<char>(s2, s1, 10);

	// (2) 각 클래스에서 복사 생성자의 여부에 따라 다르게 동작함.
	// memcpy가 효율이 좋지만, 복사 생성을 해야 하는 경우가 있음
	Point1 p1[10];
	Point1 p2[10];
	copy_type<Point1>(p2, p1, 10);

	Point2 p3[10];
	Point2 p4[10];
	copy_type<Point2>(p3, p4, 10);

	Point3 p5[10];
	Point3 p6[10];
	copy_type<Point3>(p5, p6, 10);
}
```