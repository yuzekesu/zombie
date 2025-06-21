#pragma once
#include <Windows.h>

class Mouse {
public:
	const POINT& operator()();
	void update_cursor_pos(const RECT& window_position);
private:
	POINT cursor_pos{};
};