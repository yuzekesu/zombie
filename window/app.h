#pragma once
#include <Windows.h>
#include "window.h"

class App {
public:
	void run();
private: // initialized in the constructor
	Window window;
private:
	void handle_message(MSG msg);
};