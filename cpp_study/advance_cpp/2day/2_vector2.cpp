#include <iostream>
using namespace std;

template<typename T> class vector {
	T* buff;
	int sz;
public:

	vector(int s, T value = T()) : sz(s) {
		buff = static_cast<T*>(operator new(sizeof(T)*s));

		try {
			std::uninitialized_fill_n(buff, sz, value);
		}
		catch (...) {
			operator delete(buff);
		}
	}

	~vector() {
		for (int i = 0; i < sz; i++) {
			buff[i].~T();
		}
		operator delete(buff);
	}

	// (2) 연산자를 재정의 해보자
	// T operator[] (int idx) { 값을 반환하면 안됨. 값을 반환하면 , v[0] = 0; 같은 연산을 할 수 없음
		T& operator[] (int idx) {
		return buff[idx];
	}
};

int main()
{
	vector<int> v(10);

	// (1) 아래 코드가 되려면 연산자 재정의를 해야 함
	v[0] = 100;			// v.operator[](0) = 100;
	cout << v[0] << endl;
}