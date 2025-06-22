#pragma once
#include "constant.h"
#include <bitset>
#include <Windows.h>
#include <vector>

class Response;
/*
Storing user inputs
	* stores mouse inputs as well despite calling "keyboard". 
	* the mouse inputs from the message queue needs to be manuelly converted into the VK version. 
	* dont forget to reset the keyboard when losing focus or switching responses. 
*/
class Keyboard {
public:
	Keyboard() = delete;
	Keyboard(Response& response) : response(response) {
		inputs.reserve(MAX_VIRTUAL_KEY);
	};
public: // keyboard
	void press(const UCHAR vKey);
	void release(const UCHAR vKey);
	bool is_pressing(const UCHAR vKey);
	bool is_released(const UCHAR vKey);
	void reset();
	const std::vector<UCHAR>& get_inputs();
private:
	Response& response;
	std::bitset<MAX_VIRTUAL_KEY> state;
	std::vector<UCHAR> inputs;
};