#include "response.h"
#include <cassert>

void Response::learn(const UCHAR vKey, void(*how_to_response)(App& app, const UCHAR vKey)) {
	assert(is_valid_offset(vKey));
	responses[vKey] = how_to_response;
}

void Response::respond(UCHAR vKey)
{
	assert(is_valid_offset(vKey));
	if (responses[vKey] != nullptr && !is_ignoring(vKey)) {
		responses[vKey](app, vKey);
	}
}

void Response::forget(const UCHAR vKey) {
	assert(is_valid_offset(vKey));
	responses[vKey] = nullptr;
}

void Response::ignore(const UCHAR vKey) {
	assert(is_valid_offset(vKey));
	ignoration[vKey] = true;
}

void Response::unignore(const UCHAR vKey) {
	assert(is_valid_offset(vKey));
	ignoration[vKey] = false;
}

bool Response::is_ignoring(const UCHAR vKey) {
	assert(is_valid_offset(vKey));
	return ignoration[vKey];
}

void Response::reset_memory() {
	for (int i = 0; i < MAX_VIRTUAL_KEY; i++) {
		forget(i);
	}
}

void Response::reset_ignoration() {
	ignoration.reset();
}

