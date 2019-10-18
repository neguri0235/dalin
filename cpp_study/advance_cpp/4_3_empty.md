
``` cpp
// Empty 클래스, non static member data와 가상 함수가 없는 클래스
class Empty {
	public:
	~Empty() {}
};

int main()
{
	Empty e;
	cout << sizeof(e) << endl;  //  1

	// 핵심: empty class의 크기는 1

}
```

``` cpp
/*
STL 반복자
// 입력 반복자 :		=*p, ++   :싱글 패스        (입출력과같은)
// 출력 반복자:			*p=, ++  : 싱글 패스

// 아래는 멀티 패스

// 전진형 반복자:	*p=, ++ => 싱글리스트
// 양방향 반복자:	*p=, ++ , -- => 더블리스트
// 임의 접근 반복자  *p=, ++ , -- , +, -, []
*/

int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };


	// find 알고리즘
	// 최소 요구 조건 : 입력
	auto p = find(v.begin(), v.end(), 3);

	reverse(v.begin(), v.end());// 양방향

	sort(v.begin(), v.end());// 퀵 소트  임의 접근 : vector는 가능

	list<int>l = { 1,2,3,4 };
	sort(l.begin(), l.end()); // 리스트는 quick sort (반으로 나눠야 하는데 불가) 불가

	// 그래서 list는 내장 sort 함수 제공. 
	v.sort() // 이미 sort() 에서 vector를 sort 할 수 있음. 내장 함수로 만들 필요 없음.	
}

```

``` cpp
int main()
{
	//vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	auto p = v.begin();
	++p;	// 모든 반복자는 ++  연산이 가능하다.

	// p = p + 5;	// 좋지 않은 코드 : 임의 접근 반복자만 가능
	// container 를 타입을 보고서, p++ or p = p+5 를 하도록 함
	advance(p, 5); // <-- 이 방법이 좋음

	cout << *p << endl;
}
```

#### advance를 만들자
``` cpp
// 5개의 반복자 종류를 타입화 - empty class 활용
// 5개의 개념을 타입화 했으므로 함수 오버로딩등에 활용 가능
/*
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag					: input_iterator_tag {};
struct bidirectional_iterator_tag			: forward_iterator_tag {};
struct random_access_iterator_tag	: bidirectional_iterator_tag {};

// 이제 다양한 반복자를 만드는 사람은 반드시 iterator_category를 제공해야 함

template<typename T> class vector_iterator {
public:
	typedef  random_access_iterator_tag iterator_category;
};

template<typename T> class list_iterator {
public:
	typedef  bidirectional_iterator_tag iterator_category;
};
*/


//  "Tag Dispatching" 이라고 불리는 기술
// is_pointer<> () => true_type, false_type 함수 호출과 유사한 개념
// empty class로 만들면, 최소한의 메모리를 사용해서 만들 수 있음

template <typename T> void  xadvance_imp(T& p, int n,  random_access_iterator_tag) {
	cout << "random 일때" << endl;
	p = p + n;
}

template <typename T> void  xadvance_imp(T& p, int n, input_iterator_tag) {
	cout << "random 아닐때" << endl;
	while (n--) ++p;
}

// ^^^ 이미 표준에 있음
template <typename T> void  xadvance(T& p, int n) {
	// list와 vector인지 , 반복자 타입을 조사한 후 처리 필요
	xadvance_imp(p, n, typename T::iterator_category());  // 함수 호출할때 타입이 아닌 객체를 보내야 하므로 () 를 붙여줌
}

int main()
{
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	auto p = v.begin();
	xadvance(p, 5);
	cout << *p << endl;
}
``` cpp
>> 빌드 못함

template <typename T> 
enable_if_t<is_same_v<decay_t<typename T::iterator_catetory >, random_access_iterator_tag> >
 xadvance(T& p, int n) {
	cout << "random 일때" << endl;
	p = p + n;
}

template <typename T> 
enable_if_t<! is_same_v<decay_t<typename T::iterator_catetory>, random_access_iterator_tag> >
xadvance(T& p, int n) {
	cout << "random 아닐때" << endl;
	while (n--) ++p;
}

int main()
{
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	auto p = v.begin();
	xadvance(p, 5);
	cout << *p << endl;
}
```
``` cpp
using namespace std;

template <typename T>
void xadvance(T& p, int n) {
	if constexpr (is_same_v<decay_t<typename T::iterator_catetory >, 
								random_access_iterator_tag>) {
		p = p + n;
	}
	else {
		while (n--) p++;
	}
}


int main()
{
	list<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	auto p = v.begin();
	xadvance(p, 5);
	cout << *p << endl;
}
```

``` cpp
```

``` cpp
```
``` cpp
```

``` cpp
```

``` cpp
```