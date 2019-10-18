#include <iostream>
#include <list>
#include <vector>

using namespace std;

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