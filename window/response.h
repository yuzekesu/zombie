#pragma once
#include "constant.h"
#include <Windows.h>
#include <bitset>

class App;
/*
Respond to the user inputs.
	* this class stores the policy of how the program react to the user inputs. 
	* the policy needs to have the pattern of "void(*)(App& app, const UCHAR vKey)".
	* the stored policy can be changed in run time. 
	* has the same access-ablity as the class "App".
	* default constructor is disabled due to this class is one-to-one class for the "App". 
	* be careful of what policy to be implemented. since the user has "access" to everything in side of the "App".  
	* the "reset_ignoration()" is called when losing focus. 
*/
class Response {
public:
	Response() = delete;
	Response(App& app) : app(app){}
	// call the responding response to that user inputs.
public:
	void learn(const UCHAR vKey, void(*how_to_response)(App& app, const UCHAR vKey));
	void respond(UCHAR vKey);
	void forget(const UCHAR vKey);
	void ignore(const UCHAR vKey);
	void unignore(const UCHAR vKey);
	bool is_ignoring(const UCHAR vKey);
	void reset_memory();
	void reset_ignoration();
private:
	bool is_valid_offset(const UCHAR vKey) {
		return 0 <= vKey && vKey < MAX_VIRTUAL_KEY;
	}
private:
	App& app; // constructed by the constructor.
	std::bitset<MAX_VIRTUAL_KEY> ignoration;
	void(*responses[MAX_VIRTUAL_KEY])(App& app, const UCHAR vKey) = {nullptr};
};