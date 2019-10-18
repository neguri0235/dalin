#include <iostream>

using namespace std;
/*
template<typename T> 
class Window {
public:
	void msgLoop() {			// void msgLoop(Window* this)
		// 이벤트 발생을 대기하다가 특정 멤버 함수 호출
		LButtonDown();
		// (2) 이렇게 쓰고 싶음
		//static_cast<MyWindow*> (this)->LButtonDown();
		static_cast<T*> (this)->LButtonDown();
	}
	// void LButtonDown() { cout << "Window LButton" << endl; }  virtual 이란게 붙으면 타입을 보지 말고, table을 따라감
	// (1)그런데 가상 함수 오버헤드가 있으니 virtual 을 빼고자 함.
	 void LButtonDown() { cout << "Window LButton" << endl; }
};

// (3) CRTP 형식으로 만듬.  가상 함수를 사용할 때 보다 속도가 빠름.
class MyWindow : public Window <MyWindow>{
//class MyWindow : public Window {
public:
	void LButtonDown() {
		cout << "MyWindow LButton" << endl;
	}
};

int main()
{
	MyWindow w;
	w.msgLoop();  // (msgLoop(&w))
	return 0;
}

*/

// T 를 사용하지 않는 모든 함수는 기반 클래스로 옮겨야 함. (thin template, template hoisting)

class Window {
	int handle;
public:
	void moveWindow() {
		LButtonDown();
	}
};

template<typename T>
class MsgWindow : public Window{
public:
	void msgLoop() {
		LButtonDown();
	}
	void LButtonDown() {
			static_cast<T*> (this)->LButtonDown();
	}
};

class MyWindow : public MsgWindow <MyWindow>{
//class MyWindow : public Window {
public:
	void LButtonDown() {
		cout << "MyWindow LButton" << endl;
	}
};

int main()
{
	MyWindow w;
	w.msgLoop();  // (msgLoop(&w))
	return 0;
}
