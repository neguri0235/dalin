#define USING_GUI
#include <iostream>
#include "cppmaster.h"

using namespace std;
using namespace cppmaster;

int handler(int hwnd, int msg, int a, int b) {
	switch(msg) {
	case WM_LBUTTONDOWN: cout << hwnd<<" LBUTTON" << endl; break;
	case WM_KEYDOWN: cout << hwnd<< " KEYDOWN" << endl; break;
	}
	return 0;
}
int main()
{
	int h1 = ec_make_window(&handler, "A");
	int h2 = ec_make_window(&handler, "B");

	ec_process_message();
}