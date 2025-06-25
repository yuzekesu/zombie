#include "app.h"
#include "constant.h"
#include "response_debug.h"
#include <cassert>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>

void App::run() {

	// load the default response here.

	load_response_debug(*this);
	while (msg.message != WM_QUIT) {
		time.update();
		window.get_mouse().update_cursor_pos(window.get_position());
		PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE);
		DispatchMessageW(&msg);

		// put the logic here. 

		handle_message();		// we read the user inputs here. 
		handle_user_input();	// we respond to the user inputs here. 
		std::this_thread::sleep_for(time.get_sleep_time(frame_rate));
	}
}

Window& App::get_window() {
	return window;
}

Time& App::get_time() {
	return time;
}

float& App::get_frame_rate() {
	return frame_rate;
}

 void App::handle_message()
{
	 switch (msg.message) // "msg". 
	{
	case WM_KILLFOCUS:
		window.get_keyboard().reset();
		window.get_response().reset_ignoration();
		break;

	/*
	keyboard input.
	no explicit convertion need here.
	*/

	case WM_KEYDOWN:
		window.get_keyboard().press(static_cast<UCHAR>(msg.wParam));
		break;
	case WM_KEYUP:
		window.get_keyboard().release(static_cast<UCHAR>(msg.wParam));
		break;

	// mouse input. 

	case WM_LBUTTONUP:
		window.get_keyboard().press(VK_LBUTTON);
		break;
	case WM_LBUTTONDOWN:
		window.get_keyboard().release(VK_LBUTTON);
		break;
	case WM_MBUTTONUP:
		window.get_keyboard().press(VK_MBUTTON);
		break;
	case WM_MBUTTONDOWN:
		window.get_keyboard().release(VK_MBUTTON);
		break;
	case WM_RBUTTONUP:
		window.get_keyboard().press(VK_RBUTTON);
		break;
	case WM_RBUTTONDOWN:
		window.get_keyboard().release(VK_RBUTTON);
		break;
	case WM_XBUTTONUP:
		if (LOWORD(msg.wParam) & 0x0001) {
			window.get_keyboard().press(VK_XBUTTON1);
		}
		else {
			window.get_keyboard().press(VK_XBUTTON2);
		}
		break;
	case WM_XBUTTONDOWN:
		if (LOWORD(msg.wParam) & 0x0001) {
			window.get_keyboard().release(VK_XBUTTON1);
		}
		else {
			window.get_keyboard().release(VK_XBUTTON2);
		}
		break;
	case WM_MOUSEWHEEL:
		window.get_mouse().update_wheel_delta(msg.wParam);
		break;
	default:
		break;
	}
}

 void App::handle_user_input()
 {
	 int mouse_wheel = window.get_mouse().get_wheel_delta();
	 if (mouse_wheel) {
		 window.get_response().respond(VK_MOUSEWHEEL);
	 }
	 auto inputs = window.get_keyboard().get_inputs();
	 for (auto i = inputs.begin(); i != inputs.end(); ++i) {
		 window.get_response().respond(*i);
	 }
 }
