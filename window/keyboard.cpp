#include "keyboard.h"
#include "response.h"
#include <cassert>


// keyboard
 void Keyboard::press(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	state[vKey] = true;
}

 void Keyboard::release(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	state[vKey] = false;
	response.unignore(vKey);
}

 bool Keyboard::is_pressing(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	return state[vKey];
}

bool Keyboard::is_released(const UCHAR vKey)
{
	assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	return !(state[vKey]);
}

void Keyboard::reset() {
	
	// the reset function is handled by the "std::bitset" class. 

	state.reset();
}
