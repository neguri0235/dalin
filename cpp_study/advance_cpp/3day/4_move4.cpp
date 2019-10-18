#include <iostream>

using namespace std;


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

Buffer foo() {
	Buffer buf(1024);
	return buf;
}

int main()
{
	Buffer ret = foo();	 // move
	Buffer b1(1024);
	Buffer b2 = b1;		 //copy
							 
    //Buffer b3 = b2;													// (1) 이 시점에 더이상 b2가 필요 없음. move 연산이 더 좋다.
	Buffer b3 = static_cast<Buffer&&>(b2);     // (2) move연산하기 위해서 b2를 rvalue로 캐스팅
	//Buffer b4 = std::move(b3);							 // (3) 위와 같은 casting을  move 안에서 처리하고 있음(표준 방식)

	const Buffer cb(1024);

	Buffer b5 = cb;													 // const 객체 이므로 복사 생성
	//Buffer b6 = static_cast<Buffer&&>(cb); // (4) 빌드 에러. const 속성에서 변환 불가
	Buffer b6 = static_cast<const Buffer&&>(cb); // (5) 복사를 부름. && 로 캐스팅하지만 const가 있어서 복사를 호출
	Buffer b7 = std::move(cb);   // 복사 생성자

	// 결론 : const 객체는 move 될 수 없다.
}