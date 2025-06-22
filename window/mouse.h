#pragma once
#include <Windows.h>

class Mouse {
public:
	const POINT& operator()();
	void update_cursor_pos(const RECT& window_position);
	int get_wheel_delta() {
		int Return = wheel_delta / 120;
		if (0 < abs(Return)) {
			wheel_delta %= 120;
		}
		return Return;
	}
	void update_wheel_delta(WPARAM wParam) {
		wheel_delta += HIWORD(wParam) * 120;
	}
private:
	POINT cursor_pos{};
	int wheel_delta = 0;
};