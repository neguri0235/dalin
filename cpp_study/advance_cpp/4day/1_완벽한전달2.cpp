#include <iostream>
#include <vector>

using namespace std;

class Data {};
class Test {
	Data data;
public:
	// setter 만들기
	void SetData(const Data& d) { data = d; }

	// (2) . 1번 동작을 위해서 move를 위한 setter추가
	//void SetData(Data&& d) { data = move(d); }

	// ==> move 연산을 지원하기 위해 함수를 두개씩 만들어야 함

	// 그래서, 중복적인 코드 작성을 하지 않기 위해  forwarding reference 를 사용
	// T&&	: Data& 와 Data&&의 함수를 자동 생성 (int가 전달된다면)
	template<typename T > void SetData(T&& d) {
	
		// 그렇다면 어떤 표현이 맞는 것인가?
		data = d;						// 이렇게 하면 항상 복사만 함.
		
		// 이렇게 하면 항상 move (단 객체에 const가 아니고 move 생성자가 있으면)
		data = std::move(d); 
		
		// forward는 main에서 rvalue를 보내면 rvalue를, lvalue를 보내면 lvalue는 캐스팅
		// 결론은 forward< > 를 사용하자.
		data = std::forward<T>(d);
	}
};

int main()
{
	Data d;
	Test t;
	t.SetData(d);
	t.SetData(move(d));  // (1) move 동작 하고 싶다. 
}