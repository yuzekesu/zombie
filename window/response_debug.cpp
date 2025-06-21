#include "app.h"
#include <Windows.h>
#include <sstream>
#include "response_debug.h"


void load_response_debug(App& app) {
	using namespace response_debug;
	app.response.learn(VK_ESCAPE, quit_the_program);
	app.response.learn('T', set_black_transparent);
	app.response.learn('R', set_magenta_transparent);
	app.response.learn('M', print_frame_interval);
	app.response.learn('B', set_frame_rate_60);
	app.response.learn('N', set_frame_rate_30);
	app.response.learn(VK_SPACE, popup_message_box);
}

void response_debug::quit_the_program(App& app, const UCHAR vKey) {
	PostMessage(app.window.get_hWnd(), WM_CLOSE, NULL, NULL);
	app.response.ignore(vKey);
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

void response_debug::set_frame_rate_60(App& app, const UCHAR vKey) {
	app.frame_rate = 60;
	std::wstringstream test;
	test << "Frame rate: " << app.frame_rate << "\n";
	OutputDebugString(test.str().c_str());
	app.response.ignore(vKey);
}

void response_debug::set_frame_rate_30(App& app, const UCHAR vKey) {
	app.frame_rate = 30;
	std::wstringstream test;
	test << "Frame rate: " << app.frame_rate << "\n";
	OutputDebugString(test.str().c_str());
	app.response.ignore(vKey);
}

void response_debug::popup_message_box(App& app, const UCHAR vKey) {
	MessageBoxA(NULL, "RESPONSE_DEBUG", NULL, NULL);
	app.response.ignore(vKey);
	PostMessage(app.window.get_hWnd(), WM_KEYUP, vKey, NULL);
}

