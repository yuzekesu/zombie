#pragma once
#include "keyboard.h"
#include "response.h"
#include "window.h"
#include <Windows.h>
class App {
public:
	// constructor. the "response" class needs to be initialized here
	App() : response(*this) {};	
public:
	// "seek message" loop
	void run();					
private: 
	// window creation
	Window window;	
	// storing windows messages from the queue
	MSG msg{};		
	// user input
	Keyboard keyboard;	
	// how the computer responds to the user inputs
	Response response;			
private:
	// handling windows messages: WM_EXEMPLE
	void handle_message();		
	// handling user inputs and giving the right responses
	void handle_user_input();	
};