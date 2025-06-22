#include "keyboard.h"
#include "response.h"
#include <cassert>


// keyboard
 void Keyboard::press(const UCHAR vKey) 
 {
	 assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	 if (!is_pressing(vKey)) {
		 inputs.push_back(vKey);
	 }
	 state[vKey] = true;
}

 void Keyboard::release(const UCHAR vKey)
{
	 assert(VK_LBUTTON <= vKey && vKey <= VK_OEM_CLEAR);
	 if (is_pressing(vKey)) {
		 auto iterator = std::find(inputs.begin(), inputs.end(), vKey);
		 inputs.erase(iterator);
	 }
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
	state.reset();
	inputs.erase(inputs.begin(), inputs.end());
}

const std::vector<UCHAR>& Keyboard::get_inputs() {
	return inputs;
}
