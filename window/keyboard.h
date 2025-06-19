#pragma once
#include "constant.h"
#include <Windows.h>
#include <bitset>

class Keyboard {
public: // keyboard
	void press(const UCHAR vKey);
	void release(const UCHAR vKey);
	bool is_pressing(const UCHAR vKey);
	bool is_released(const UCHAR vKey);
	void reset();
private:
	std::bitset<MAX_VIRTUAL_KEY> state;
};