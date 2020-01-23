#define USING_GUI
#include <iostream>
#include <string>
#include "cppmaster.h"

#include <map>

using namespace std;
using namespace cppmaster;

class Window;

map<int, Window*> this_map; 
// 또는 핸들 맵이라고 부름
// 대부분의 GUI 라이브러리에 이 개념이 있음

class Window {
	int handle;
public:
	void Create(string title) {
		handle = ec_make_window(&handler, title);
		this_map[handle] = this;
	}
	// static에는 this가 없어서 this를 보관하는 자료 구조가 필요함
	static int handler(int hwnd, int msg, int a, int b) {
		Window* self = this_map[hwnd];
		switch (msg) {
		case WM_LBUTTONDOWN:     self->OnLButtonDown(); 	break;
		case WM_KEYDOWN:					self->OnKeyDown(); break;
		}
		return 0;
	}

	virtual void OnLButtonDown() {}
	virtual void OnKeyDown() { }
};

class Frame : public Window {
public:
	virtual void OnLButtonDown() { cout << "Frame Button" << endl; }
	virtual void OnKeyDown() { cout << "Frame Key" << endl; }
};

int main()
{
	Frame f;
	f.Create("A");
	ec_process_message();
}