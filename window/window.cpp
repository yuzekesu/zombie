#include "window.h"
#include "window_procedure.h"
#include <cassert>
#include <ratio>

Window::Window()
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
	RECT position_edge_window{};
	position_edge_window.left = x * factor_left_top::num / factor_left_top::den;
	position_edge_window.top = y * factor_left_top::num / factor_left_top::den;
	position_edge_window.right = x * factor_right_bottom::num / factor_right_bottom::den;
	position_edge_window.bottom = y * factor_right_bottom::num / factor_right_bottom::den;
	int width_window = position_edge_window.right - position_edge_window.left;
	int height_window = position_edge_window.bottom - position_edge_window.top;
	BOOL adjusted_window_rect = AdjustWindowRect(&position_edge_window, NULL, NULL);
	assert(adjusted_window_rect);
	hWnd = CreateWindowExW(WS_EX_LAYERED, wc.lpszClassName, wc.lpszClassName, WS_POPUP, position_edge_window.left, position_edge_window.top, width_window, height_window, NULL, NULL, wc.hInstance, NULL);
	assert(hWnd);

	// the transparence color is "magenta". 

	SetLayeredWindowAttributes(get_hWnd(), RGB(255,0,255), NULL, LWA_COLORKEY);
	ShowWindow(hWnd, SW_SHOW);
}

HWND Window::get_hWnd()
{
	return hWnd;
}

