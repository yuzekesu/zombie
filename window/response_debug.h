#pragma once
#include "camera.h"
#include <DirectXMath.h>
#include <Windows.h>

class App;
void load_response_debug(App& app);

namespace response_debug {

	void quit_the_program(App& app, const UCHAR vKey);
	void print_frame_interval(App& app, const UCHAR vKey);
	void print_approximate_frame_rate(App& app, const UCHAR vKey);
	void set_magenta_transparent(App& app, const UCHAR vKey);
	void set_black_transparent(App& app, const UCHAR vKey);
	// depend on the default refresh rate of your window, the result might be different. 
	void set_frame_rate_60(App& app, const UCHAR vKey);
	void set_frame_rate_30(App& app, const UCHAR vKey);
	void popup_message_box(App& app, const UCHAR vKey);
	void camera_move_forward(App& app, const UCHAR vKey);
	void camera_move_backward(App& app, const UCHAR vKey);
	void camera_move_left(App& app, const UCHAR vKey);
	void camera_move_right(App& app, const UCHAR vKey);
	void camera_rotate_yaw_increase(App& app, const UCHAR vKey);
	void camera_rotate_yaw_decrease(App& app, const UCHAR vKey);
	void camera_rotate_pitch_increase(App& app, const UCHAR vKey);
	void camera_rotate_pitch_decrease(App& app, const UCHAR vKey);
	void camera_move_up(App& app, const UCHAR vKey);
	void camera_move_down(App& app, const UCHAR vKey);


}