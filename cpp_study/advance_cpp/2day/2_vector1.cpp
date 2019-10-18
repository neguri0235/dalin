#include <iostream>

using namespace std;

class Point {
	int x, y;
public:
	Point(int a, int b) :x(a), y(b) {
		cout << "Point()" << endl;
	}

	Point(const Point& p)
	{
		cout << "Point copy" << endl;
	}

	~Point() { cout << "~Point()" << endl; }
};

template<typename T> class vector {
	T* buff;
	int sz;
public:

	vector(int s, T value = T()) : sz(s) {
		buff = static_cast<T*>(operator new(sizeof(T)*s));

		/*
		int cnt = 0;
		try {
			for (int i = 0; i < sz; i++) {
				// new (&buff[[i]) T;			// 디폴트 생성자
				new(&buff[i])T(value);  // 복사 생성자
				cnt = i;
			}
		}
		catch (...) {
			// 생성자 호출에 성공한 객체는 다시 소멸자 호출
			for (int i = 0; i < cnt; i++) {
				buff[i].~T();
			}
			operator delete(buff);
		}
		*/

		// buff 부터 sz 개수만 큼 value로 채워라 (복사 생성자)
		// 실패하면 성공한 것은 소멸 자 호출 후 예외 발생
		try{
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
};

int main()
{
	vector<int> v(10);
	Point pt(0, 0);
	vector<Point> p(10, pt);

	// 혹은
	vector<Point>p2(10, { 0,0 });
}