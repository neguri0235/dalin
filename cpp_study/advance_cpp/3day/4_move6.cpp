#include <iostream>
#include <vector>
#include <string>

using namespace std;



// 알고리즘 함수 제작과 move

class Buffer {
	int* resource;
	int size;
public:
	Buffer(int sz) : size(sz) { resource = new int[sz]; }
	~Buffer() { delete[] resource; }

	Buffer(const Buffer& b) : size(b.size) {
		resource = new int[size];
		memcpy(resource, b.resource, sizeof(int)*size);
		cout << "복사 생성자" << endl;
	}


	Buffer(Buffer&& b) : size(b.size) {
		resource = b.resource;
		b.resource = 0;
		cout << "이동 생성자" << endl;
	}
};


template <typename T> void Swap(T& a, T& b) {
	// 복사 생성자에 의한 swap - 느리다
	/*
	T tmp = a;
	a = b;
	b = tmp;
	*/
	// move 생성자에 의한 swap - 빠르다

	T tmp = std::move(a);
	a = std::move(b);  // move 대입 연산자.
	b = std::move(tmp);
}

int main()
{
	Buffer b1(1024);
	Buffer b2(1024);
	Swap(b1, b2);

	string s1 = "hello";
	string s2 = "world";
	Swap(s1, s2);
	cout << s1 << s2 << endl;

	int n = 10; 
	int n1 = static_cast<int&&>(n);  // 컴파일 시점이므로 오버헤드 없음.
	int n2 = move(n);								// 동적할당된 자원이 없으니 빨라지는 것은 아님
}