#pragma once
#include "constant.h"
#include <Windows.h>

class App;

class Response {
public:
	Response() = delete;
	Response(App& app) : app(app){}
	void operator()(UCHAR vKey);
public:
	void learn(UCHAR vKey, void(*how_to_response)(App& app, const UCHAR vKey));
	void download(void(**how_to_response)(App& app, const UCHAR vKey));
	void forget(UCHAR vKey);
	void reset();
private:
	App& app; // constructed by the constructor.
	void(*responses[MAX_VIRTUAL_KEY])(App& app, const UCHAR vKey) = {nullptr};
};