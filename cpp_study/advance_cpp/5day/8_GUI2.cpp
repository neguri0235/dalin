#define USING_GUI
#include <iostream>
#include <string>
#include "cppmaster.h"

using namespace std;
using namespace cppmaster;

class Window {
	int handle;
public:
	void Create(string title) {
		handle = ec_make_window(&handler, title);
	}


	// 핵심 1. C의 callback 함수(인자의 갯수가 규칙으로 정해져 있다)를 
	//					C++멤버로 만들때는 반드시 static으로 해야 한다.
	static int handler(int hwnd, int msg, int a, int b) {
		switch (msg) {
		case WM_LBUTTONDOWN: cout << hwnd << " LBUTTON" << endl; break;
		case WM_KEYDOWN: cout << hwnd << " KEYDOWN" << endl; break;
		}
		return 0;
	}


};

int main()
{
	Window w;
	w.Create("A");

	ec_process_message();
}