#define USING_GUI
#include <iostream>
#include <string>
#include "cppmaster.h"

#include <map>

using namespace std;
using namespace cppmaster;

class Window;

map<int, Window*> this_map;

struct AFX_MSG {
	int message;									// 메시지 번호
	void (Window::*handler)();		// 메세지를 처리할 함수 주소
};

class Window {
	int handle;
public:
	void Create(string title) {
		handle = ec_make_window(&handler, title);
		this_map[handle] = this;
	}


	virtual AFX_MSG* GetMessageMap() {
		return nullptr;
	}

	static int handler(int hwnd, int msg, int a, int b) {
		Window* self = this_map[hwnd];

		if (self == nullptr) return 0;

		AFX_MSG* arr = self->GetMessageMap();

		if (arr == nullptr) return 0;

		while (arr->message != 0) {
			if (arr->message == msg) {
				void(Window::*f)() = arr->handler;
				
				(self->*f)();
			}
			++arr;
		}

		return 0;
	}

};

class Frame : public Window {
public:
	virtual AFX_MSG*		GetMessageMap() {
		
		typedef void(Window::*HANDLER)();
		static AFX_MSG arr[] = {
			{WM_LBUTTONDOWN,(HANDLER) &Frame::OnLButtonDown},
			{WM_KEYDOWN,(HANDLER) &Frame::OnKeyDown},
			{0,0}
		};
		return arr;
	}
	void OnLButtonDown() { cout << "Frame Button" << endl; }
	void OnKeyDown() { cout << "KeyDown" << endl; }
};

int main()
{
	Frame f;
	f.Create("A");
	ec_process_message();
}