#include "app.h"
#include <Windows.h>
#include <sstream>
#include "response_debug.h"


void load_response_debug(App& app) {
	using namespace response_debug;
	app.response.learn('A', set_black_transparent);
	app.response.learn('D', set_magenta_transparent);
	app.response.learn('W', print_frame_interval);
}

void response_debug::print_frame_interval(App& app, const UCHAR vKey) {
	std::wstringstream test;
	test << app.time() << "\n";
	OutputDebugString(test.str().c_str());
	app.response.ignore(vKey);
}
void response_debug::set_magenta_transparent(App& app, const UCHAR vKey) {
	SetLayeredWindowAttributes(app.window.get_hWnd(), RGB(255, 0, 255), NULL, LWA_COLORKEY);
	app.response.ignore(vKey);
}
void response_debug::set_black_transparent(App& app, const UCHAR vKey) {
	SetLayeredWindowAttributes(app.window.get_hWnd(), RGB(0,0,0), NULL, LWA_COLORKEY);
	app.response.ignore(vKey);
}

