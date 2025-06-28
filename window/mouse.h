#pragma once
#include <Windows.h>

class Mouse {
public:
	const POINT& operator()();
	void update_cursor_pos(const RECT& window_position);
	int get_wheel_delta();
	void update_wheel_delta(WPARAM wParam);
	const POINT& get_cursor_pos();
private:
	POINT cursor_pos{};
	int wheel_delta = 0;
};