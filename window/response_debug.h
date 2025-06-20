#pragma once
#include <Windows.h>

class App;
void load_response_debug(App& app);

namespace response_debug {
	void print_frame_interval(App& app, const UCHAR vKey);
	void set_magenta_transparent(App& app, const UCHAR vKey);
	void set_black_transparent(App& app, const UCHAR vKey);
}