#include "keyboard.h"
#include <cassert>

void Keyboard::press(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	this->state[vKey] = true;
}

void Keyboard::release(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	this->state[vKey] = false;
}

bool Keyboard::is_pressing(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	return this->state[vKey];
}

bool Keyboard::is_released(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	return !(this->state[vKey]);
}

void Keyboard::reset() {
	
	// the reset function is handled by the "std::bitset" class. 

	this->state.reset();
}
