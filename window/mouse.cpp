#include "mouse.h"
#include <cassert>

const POINT& Mouse::operator()() {
	return cursor_pos;
}

void Mouse::update_cursor_pos(const RECT& window_position) {
	BOOL got_cursor_pos = GetCursorPos(&(cursor_pos));
	assert(got_cursor_pos);
	cursor_pos.x = cursor_pos.x < window_position.left ? window_position.left : cursor_pos.x;
	cursor_pos.x = window_position.right < cursor_pos.x ? window_position.right : cursor_pos.x;
	cursor_pos.y = cursor_pos.y < window_position.top ? window_position.top : cursor_pos.y;
	cursor_pos.y = window_position.bottom < cursor_pos.y ? window_position.bottom : cursor_pos.y;
}

int Mouse::get_wheel_delta() {
	int Return = wheel_delta / 120;
	if (0 < abs(Return)) {
		wheel_delta %= 120;
	}
	return Return;
}

void Mouse::update_wheel_delta(WPARAM wParam) {
	wheel_delta += HIWORD(wParam) * 120;
}

const POINT& Mouse::get_cursor_pos()
{
	return cursor_pos;
}
