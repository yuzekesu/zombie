#pragma once
#include <Windows.h>

/*
windows window. 
	* this class create the pre-defined window upon creation. 
	* the window is "layered" for transparency. 
	* the window is "popup" for not having the menu bar. 
	* HWND is stored here if needed. 
*/
class Window {
public:
	// constructor that construct a window. 
	Window();
public:
	HWND get_hWnd();
	const RECT& get_position();
private: 
	// initialized in the constructor "Window::Window()". 
	HWND hWnd;
	RECT position{};
};