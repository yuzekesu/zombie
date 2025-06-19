#pragma once
#include "keyboard.h"
#include "response.h"
#include "window.h"
#include <Windows.h>
class App {
public:
	App() : response(*this) {};
	void run();
private: // initialized in the constructor
	Window window;
	MSG msg{};
	Keyboard keyboard;
	Response response;
private:
	void handle_message();
	void handle_user_input();
};