#include "time.h"

float Time::operator()() {
	return time_since_last_update.count();
}

void Time::update() {/*
	steady_clock is default in mili sceond. 
	*/

	auto now = std::chrono::steady_clock::now();

	/*
	implicit convertion is fine, since no truncation needed from "int" -> "float".
	*/

	time_since_last_update = now - last_update;
	last_update = std::chrono::steady_clock::now();
}
