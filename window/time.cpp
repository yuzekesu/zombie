#include "time.h"

void Time::update() {/*
	steady_clock is default in mili sceond. 
	*/

	auto now = std::chrono::steady_clock::now();

	/*
	implicit convertion is fine, since no truncation needed from "int" -> "float".
	*/

	time_since_last_update = std::chrono::duration_cast<std::chrono::duration<float>>(now - last_update);
	last_update = std::chrono::steady_clock::now();
}

float Time::get_delta() {
	return time_since_last_update.count();
}

std::chrono::duration<float> Time::get_sleep_time(float frame_rate) {
	std::chrono::duration<float> work_time = std::chrono::steady_clock::now() - last_update;
	return std::chrono::duration<float>{1.f / frame_rate} - work_time;
}
