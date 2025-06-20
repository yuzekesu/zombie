#pragma once
#include <chrono>

/*
Time and frame rate. 
	* the "operator()()" will return the time past since the last "update()".
	* please use "ti"
*/
class Time {
public:
	float operator()();
	void update();
	// for the "std::this_thread::sleep_for()". 
	// not accurate. 
	std::chrono::duration<float> get_sleep_time(float frame_rate) {
		auto work_time = std::chrono::steady_clock::now() - last_update;
		return std::chrono::duration<float>{1.0 / frame_rate} - work_time;
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> last_update = std::chrono::steady_clock::now();
	std::chrono::duration<float> time_since_last_update{0.0};
};