#pragma once
#include "constant.h"
#include <Windows.h>
#include <bitset>

class Response;
/*
Storing user inputs
	* extrem lightweight class, only one type of stored data.
	* stores mouse inputs despite calling "keyboard". 
	* the mouse inputs from the message queue needs to be manuelly converted into the VK version. 
	* dont forget to reset the keyboard when losing focus or switching responses. 
*/
class Keyboard {
public:
	Keyboard() = delete;
	Keyboard(Response& response) : response(response) {};
public: // keyboard
	void press(const UCHAR vKey);
	void release(const UCHAR vKey);
	bool is_pressing(const UCHAR vKey);
	bool is_released(const UCHAR vKey);
	void reset();
private:
	Response& response;
	std::bitset<MAX_VIRTUAL_KEY> state;
};