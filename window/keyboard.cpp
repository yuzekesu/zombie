#include "keyboard.h"

void Keyboard::press(const UCHAR vKey)
{
	this->state[vKey] = true;
}

void Keyboard::release(const UCHAR vKey)
{
	this->state[vKey] = false;
}

bool Keyboard::is_pressing(const UCHAR vKey)
{
	return this->state[vKey];
}

bool Keyboard::is_released(const UCHAR vKey)
{
	return !(this->state[vKey]);
}

void Keyboard::reset() {
	
	// the reset function is handled by the "std::bitset" class. 

	this->state.reset();
}
