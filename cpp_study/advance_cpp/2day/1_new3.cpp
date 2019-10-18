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
	
	// value를 받지만, 혹시 안주면 T의 default 값을 사용 : zero initialization 이라고 부름
	// T 가  primitive 또는 포인터이면  : 0
	//           user type이면 디폴트 생성자

	vector(int s, T value = T()) : sz(s) {
		
		// 1. 이렇게 컨테이너를 만들면, 안됨. 디폴트 생성자 없으면 동작 안함
		// 결국 컨테이너 생성 시 요구 조건 및 제약이 많아 짐
		//buff = new T[sz];

		// 2. 따라서 이렇게 만들어야 함
		buff = static_cast<T*>(operator new(sizeof(T)*s));

		// 3. 할당된 메모리에 생성자 호출
		// 하지만 T 가 어떤 타입인지 모르니 어떤 생성자를 부를 수 없음.
		// 복사 생성자를 부르는 것이 기본 조건

		// 4. 메모리 할당 및 생성자 호출 시 예외 상황 발생시 자원해제를 하도록 함
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
		
	}

	~vector(){
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

}