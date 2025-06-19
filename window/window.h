#pragma once
#include <Windows.h>


class Window {
public:
	Window();
public:
	HWND get_hWnd();
private: // initialized in the constructor
	HWND hWnd;
};