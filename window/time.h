#pragma once
#include <chrono>
#include <Windows.h>

/*
Time and frame rate. 
	* the "operator()()" will return the time past since the last "update()".
	* please use "ti"
*/
class Time {
public:
	void update();
	
	// get delta. 
	float get_delta();
	// for the "std::this_thread::sleep_for()". 
	// not accurate. 
	std::chrono::duration<float> get_sleep_time(float frame_rate);
private:
	std::chrono::time_point<std::chrono::steady_clock> last_update = std::chrono::steady_clock::now();
	std::chrono::duration<float> time_since_last_update{0.0};
};