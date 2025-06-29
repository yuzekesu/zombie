#pragma once
#include "model.h"
#include "time.h"
#include "window.h"
#include <Windows.h>

/*
the boss of the program, has access to anything. 
*/
class App {
public:
	App() : window(*this) {};	
public:
	// "peek message" loop. 
	void run();	
public:
	Window& get_window();
	Time& get_time();
	float& get_frame_rate();
private:
	MSG msg{};
	Window window;		
	Time time;
	float frame_rate = 30.f;
	Model model;
private:
	/*
	handling windows messages : WM_EXEMPLE.
	*/ 
	void handle_message();		
	/*
	handling user inputs and giving the right responses.
	*/
	void handle_user_input();	
	void handle_graphic();
};