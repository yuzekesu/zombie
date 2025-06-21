#pragma once
#include "keyboard.h"
#include "mouse.h"
#include "response.h"
#include "time.h"
#include "window.h"
#include <Windows.h>

/*
the boss of the program, has access to anything. 
*/
class App {
public:
	/*
	it is like: App -> Keyboard -> Response -> App -> ... a Input Output loop. 
	*/
	App() : response(*this), keyboard(response) {};	
public:
	// "peek message" loop. 
	void run();	
public:
	MSG msg{};
public: 
	// window creation.
	Window window;		
	// position of the cursor, update once per frame. 
	Mouse mouse;
	// user inputs from keyboard an mouse. 
	Keyboard keyboard;	
	// how the computer responds to the user inputs. 
	Response response;	
	// reading time here. 
	Time time;
	// frame rate per second
	float frame_rate = 30.0f;
private:
	/*
	handling windows messages : WM_EXEMPLE.
	*/ 
	void handle_message();		
	/*
	handling user inputs and giving the right responses.
	*/
	void handle_user_input();	
};