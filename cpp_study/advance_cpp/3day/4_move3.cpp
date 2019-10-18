#include <iostream>

using namespace std;


class Buffer {
	int* resource;
	int size;
public:
	Buffer(int sz) : size(sz) { resource = new int[sz]; }
	~Buffer() { delete[] resource; }

	// C++11 이전에는 복사 생성자만 있었음.
	// 이름 있는 객체나 없는 객체나 동일한 알고리즘 사용

	// C++11 이후 : 임시객체일때 복사하는 방법
	//								이름 있는 객체일때와 복사하는 방법을 분리해서 최적화하자.

	Buffer(const Buffer& b) : size(b.size) {
		resource = new int[size];
		memcpy(resource, b.resource, sizeof(int)*size);
		cout << "복사 생성자" << endl;
	}

	// 인자로 임시객체가 올때는 메모리를 통째로 복사할 필요가 없다.
	// 주소만 복사해오면 된다. 
	Buffer( Buffer&& b) : size(b.size) {  // <------(3)
		resource = b.resource;
		b.resource = 0;   // 이전 주소 포인터에 0을 넣어야 하므로, const를 빼야 함.
		cout << "이동 생성자" << endl;
	}
};

Buffer foo() {
	Buffer buf(1024);
	return buf;
}

int main()
{
	Buffer ret = foo();  // 임시 객체인 경우만 , 얕은 복사가 필요
	cout << "----" << endl;
	Buffer b1(1024);
	cout << "----" << endl;
	Buffer b2 = b1;
}