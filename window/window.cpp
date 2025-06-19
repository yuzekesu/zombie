#include "window.h"
#include "window_procedure.h"
#include <cassert>

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
	wc.lpszClassName = L"zombie_window";
	wc.hIconSm = NULL;
	assert(RegisterClassExW(&wc));
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	LONG resizeFactor_window = 8;
	RECT position_window{};
	position_window.left = 0 + x / resizeFactor_window;
	position_window.top = 0 + y / resizeFactor_window;
	position_window.right = x - x / resizeFactor_window;
	position_window.bottom = y - y / resizeFactor_window;
	int width = position_window.right - position_window.left;
	int height = position_window.bottom - position_window.top;
	assert(AdjustWindowRect(&position_window, NULL, NULL));
	assert(this->hWnd = CreateWindowExW(WS_EX_LAYERED, wc.lpszClassName, wc.lpszClassName, WS_POPUP, position_window.left, position_window.top, width, height, NULL, NULL, wc.hInstance, NULL));
	SetLayeredWindowAttributes(this->get_hWnd(), RGB(255,0,255), NULL, LWA_COLORKEY);
	ShowWindow(hWnd, SW_SHOW);
}

HWND Window::get_hWnd()
{
	return this->hWnd;
}

