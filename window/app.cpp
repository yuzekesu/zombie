#include "app.h"
#include "constant.h"
#include <cassert>

void App::run() {
	while (msg.message != WM_QUIT) {

		// only get the cursor position once per frame. 

		assert(GetCursorPos(&(this->cursor)));
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			DispatchMessageW(&msg);

			// put the logic here. 

			handle_message();
			handle_user_input();
		}
	}
}

 void App::handle_message()
{
	switch (this->msg.message) // "msg". 
	{

	// keyboard input. 

	case WM_KEYDOWN:
		keyboard.press(this->msg.wParam);
		break;
	case WM_KEYUP:
		keyboard.release(this->msg.wParam);
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

	 /* 
	 probably not efficient, 
	 it checks around 50 "if" statements per frame.
	 but if i use queue to store the inputs, 
	 how would i know if the user has released the key or not in the next frame ??
	 dont want to make it complicate for now.
	 */

	 // mouse + backspace + !! no longer "tab".
	 for (int i = VK_LBUTTON; i <= VK_BACK; i++) {
		 if (keyboard.is_pressing(i)) {
			 response(i);
		 }
	 }
	 // enter + shift + ctrl + !! no longer "alt".
	 for (int i = VK_RETURN; i <= VK_CONTROL; i++) {
		 if (keyboard.is_pressing(i)) {
			 response(i);
		 }
	 }
	 // esc.
	 if (keyboard.is_pressing(VK_ESCAPE)) {
		 response(VK_ESCAPE);
	 }
	 // spacebar.
	 if (keyboard.is_pressing(VK_SPACE)) {
		 response(VK_SPACE);
	 }
	 // arrows.
	 for (int i = VK_LEFT; i <= VK_DOWN; i++) {
		 if (keyboard.is_pressing(i)) {
			 response(i);
		 }
	 }
	 // numbers and alphabets.
	 for (int i = '0'; i <= 'Z'; i++) {
		 if (keyboard.is_pressing(i)) {
			 response(i);
		 }
	 }
 }
