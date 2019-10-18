#include <iostream>

using namespace std;

// 1. 클래스 안데 포인터 변수가 있으면 얕은 복사 현상이 있음.
// 2. 반드시 복사 생성자를 사용자가 만들어야 한다.

class Buffer {
	int* resource;
	int size;
public:
	Buffer(int sz) : size(sz) { resource = new int[sz]; }
	~Buffer() { delete[] resource; }

	// (2) 깊은 복사를 하는 복사 생성자 만들기
	Buffer(const Buffer& b) : size(b.size) {
		resource = new int[size];
		memcpy(resource, b.resource, sizeof(int)*size);
	}
};

int main()
{
	Buffer b1(1024);
	Buffer b2 = b1;  // (1) 이순간 얕은 복사가 되어 종료시 죽게 됨
}