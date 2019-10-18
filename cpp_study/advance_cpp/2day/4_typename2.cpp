#include <iostream>
//#include <vector>

using namespace std;

template<typename T> class vector {
public:
	typedef unsigned int size_type;
	// size( )라는 멤버 함수가 있어야 하고
	// size_type 이라는 것이 구현되어 있어야 함
	size_type size() const { return 10; }
};

//void foo(vector<int>&v) {
template<typename T> void foo(vector<int>&v) {
	// ? 에 들어갈 최적의 타입은? 
	//? = v.size();
	vector<int>::size_type n = v.size();
	typename T::size_type n = v.size();
}
 
int main()
{
	vector<int> v(10);
	foo(v);
}