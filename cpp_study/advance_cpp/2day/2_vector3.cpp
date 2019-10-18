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
	T& operator[] (int idx) {
		return buff[idx];
	}
};


template<> class vector <bool> {
	int* buff;
	int sz;
public:

	vector(int s, bool value = false) : sz(s) {
		int cnt = sz / 32 + 1;
		buff = static_cast<int*>(operator new(sizeof(int)*cnt));
		
		// buff 부터 sz 비트를 value로 채우기

	}
	~vector() {
		operator delete(buff);
	}

	// bit를 반환해야 하는데 어떻게 반환할 수 있을까???
	?& operator[] (int idx) {
		return buff[idx];
	}
};

int main()
{
	vector<int> v(10);
	// (1) bool을 저장하기엔 메모리 낭비가 있다.
	vector<bool> v2(30);
}