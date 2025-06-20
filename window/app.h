#pragma once
#include "keyboard.h"
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
	// "seek message" loop. 
	void run();	
public:

	// win32 library datas

	// storing windows messages from the queue. 
	MSG msg{};
	// position of the cursor, update once per frame. 
	POINT cursor{};
public: 

	// user defined datas

	// window creation
	Window window;		
	// user input
	Keyboard keyboard;	
	// how the computer responds to the user inputs. 
	Response response;	
	// reading time here. 
	Time time;
	// frame rate per second
	float frame_rate = 30.0;
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