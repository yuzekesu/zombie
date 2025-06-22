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
		mouse.update_cursor_pos(window.get_position());
		PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE);
		DispatchMessageW(&msg);

		// put the logic here. 

		handle_message();		// we read the user inputs here. 
		handle_user_input();	// we respond to the user inputs here. 
		std::this_thread::sleep_for(time.get_sleep_time(frame_rate));
	}
}

 void App::handle_message()
{
	 switch (msg.message) // "msg". 
	{
	case WM_KILLFOCUS:
		keyboard.reset();
		response.reset_ignoration();
		break;

	/*
	keyboard input.
	no explicit convertion need here.
	*/

	case WM_KEYDOWN:
		keyboard.press(static_cast<UCHAR>(msg.wParam));
		break;
	case WM_KEYUP:
		keyboard.release(static_cast<UCHAR>(msg.wParam));
		break;

	// mouse input. 

	case WM_LBUTTONUP:
		keyboard.press(VK_LBUTTON);
		break;
	case WM_LBUTTONDOWN:
		keyboard.release(VK_LBUTTON);
		break;
	case WM_MBUTTONUP:
		keyboard.press(VK_MBUTTON);
		break;
	case WM_MBUTTONDOWN:
		keyboard.release(VK_MBUTTON);
		break;
	case WM_RBUTTONUP:
		keyboard.press(VK_RBUTTON);
		break;
	case WM_RBUTTONDOWN:
		keyboard.release(VK_RBUTTON);
		break;
	case WM_XBUTTONUP:
		if (LOWORD(msg.wParam) & 0x0001) {
			keyboard.press(VK_XBUTTON1);
		}
		else {
			keyboard.press(VK_XBUTTON2);
		}
		break;
	case WM_XBUTTONDOWN:
		if (LOWORD(msg.wParam) & 0x0001) {
			keyboard.release(VK_XBUTTON1);
		}
		else {
			keyboard.release(VK_XBUTTON2);
		}
		break;
	default:
		break;
	}
}

 void App::handle_user_input()
 {
	 auto inputs = keyboard.get_inputs();
	 for (auto i = inputs.begin(); i != inputs.end(); ++i) {
		 response(*i);
	 }
 }
