#pragma once
#include "graphic.h"
#include <memory>
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
	Window() = delete;
	Window(App& app);
public:
	HWND get_hWnd();
	const RECT& get_position();
	Mouse& get_mouse();
	Keyboard& get_keyboard();
	Response& get_response();
private: 
	// initialized in the constructor "Window::Window()". 
	HWND hWnd;
	RECT position{};// position of the cursor, update once per frame. 
	Mouse mouse;
	// user inputs from keyboard an mouse. 
	Keyboard keyboard;
	// how the computer responds to the user inputs. 
	Response response;
	std::unique_ptr<Graphic> pGraphic = nullptr;
};