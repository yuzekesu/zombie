#include "app.h"
#include "window.h"
#include "window_procedure.h"
#include <cassert>
#include <ratio>

Window::Window(App& app) : response(app), keyboard(response)
{
	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0u;
	wc.lpfnWndProc = window_procedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.hIcon = NULL;
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wc.lpszMenuName = NULL;

	// the program name is based on "wc.lpszClassName". change this will change the program name. 

	wc.lpszClassName = L"zombie_window";
	wc.hIconSm = NULL;
	ATOM registred_window_class = RegisterClassExW(&wc);
	assert(registred_window_class);

	// to get the resolution of the primary monitor. 

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	/* 
	the ratios represent the edge of the window on the primary monitor.
	set "8" -> "1" for borderless full screen. 
	*/
	using factor_left_top = std::ratio<1, 8>;
	using factor_right_bottom = std::ratio_subtract<std::ratio<1>, factor_left_top>;
	position.left = x * factor_left_top::num / factor_left_top::den;
	position.top = y * factor_left_top::num / factor_left_top::den;
	position.right = x * factor_right_bottom::num / factor_right_bottom::den;
	position.bottom = y * factor_right_bottom::num / factor_right_bottom::den;
	int width_window = position.right - position.left;
	int height_window = position.bottom - position.top;
	BOOL adjusted_window_rect = AdjustWindowRect(&position, NULL, NULL);
	assert(adjusted_window_rect);
	hWnd = CreateWindowExW(WS_EX_LAYERED, wc.lpszClassName, wc.lpszClassName, WS_POPUP, position.left, position.top, width_window, height_window, NULL, NULL, wc.hInstance, NULL);
	assert(hWnd);

	// the transparence color is "magenta". 

	SetLayeredWindowAttributes(get_hWnd(), RGB(255,0,255), NULL, LWA_COLORKEY);
	pGraphic = std::make_unique<Graphic>(hWnd);
	ShowWindow(hWnd, SW_SHOW);
}

HWND Window::get_hWnd()
{
	return hWnd;
}
const RECT& Window::get_position() {
	return position;
}

Mouse& Window::get_mouse() {
	return mouse;
}

Keyboard& Window::get_keyboard() {
	return keyboard;
}

Response& Window::get_response() {
	return response;
}

