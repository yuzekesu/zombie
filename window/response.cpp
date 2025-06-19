#include "response.h"

void Response::operator()(UCHAR vKey) {
	if (this->responses[vKey] != nullptr) {
		responses[vKey](this->app, vKey);
	}
}

void Response::learn(UCHAR vKey, void(*how_to_response)(App& app, const UCHAR vKey)) {
	responses[vKey] = how_to_response;
}

void Response::download(void(**how_to_response)(App& app, const UCHAR vKey)) {
	for (int i = 0; i < MAX_VIRTUAL_KEY; i++) {
		responses[i] = how_to_response[i];
	}
}

void Response::forget(UCHAR vKey) {
	responses[vKey] = nullptr;
}

void Response::reset() {
	for (int i = 0; i < MAX_VIRTUAL_KEY; i++) {
		forget(i);
	}
}
