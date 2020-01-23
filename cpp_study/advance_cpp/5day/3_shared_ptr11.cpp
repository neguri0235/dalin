#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 상속 받을 때 자기 이름 보내는 것. CRTP
class ConnectDB :  public enable_shared_from_this<ConnectDB> {

	// 스레드를 사용하는 클래스가 있다면
	// 자신의 수명을 스레스가 종료될 때 까지 유지해야 한다
	// 자신을 가리키는 스마트 포인터가 있어야 한다.
	shared_ptr<ConnectDB> holdMe;

public:
	// 문제점 1. this는 raw pointer이므로 관리 객체가 따로 생성됨
	// 문제점 2.생성자에서는 스레드가 생성되기 전이다. 참조 계수가 증가될 필요 없다.
	/*
	ConnectDB() : holdMe(this) {
	}
	*/

	void start() {
		// holdMe = this; // error. 

		holdMe = shared_from_this(); // 외부에서 만들었던 관리 객체를 공유하게 해준다.

		thread t(&ConnectDB::Main, this);
		t.detach();
	}

	virtual void Main() {
		
		// (2) 그래서 이렇게 함.
		shared_ptr<ConnectDB> sp(holdMe);
		holdMe.reset();

		this_thread::sleep_for(3s);
		cout << "DB접속" << endl;
		// 멤버 데이타 사용중


		 holdMe.reset();  // << 이걸 제거하고 테스트해보면 차이를 확인 가능
				// (1) 이렇게 하면 위쪽에서 예외 발생시 수행못됨. 
	}
	~ConnectDB() {
		cout << "파괴" << endl;
	}
};

int main()
{
	{
		shared_ptr<ConnectDB> p(new ConnectDB);
		p->start();
		// (1) 여기 빠져나가면 제거됨. 나중에 문제 발생
	}
	
	getchar();
}

/*
https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/include/utils/Thread.h
	
	volatile bool           mRunning;
			sp<Thread>      mHoldSelf;

https://github.com/aosp-mirror/platform_system_core/blob/master/libutils/Threads.cpp

int Thread::_threadLoop(void* user)
{
	Thread* const self = static_cast<Thread*>(user);

	sp<Thread> strong(self->mHoldSelf);
	wp<Thread> weak(strong);
	self->mHoldSelf.clear()

*/