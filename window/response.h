#pragma once
#include "constant.h"
#include <Windows.h>

class App;

/*
Respond to the user inputs. 
	* this class stores the policy of how the program react to the user inputs. 
	* the policy needs to have the pattern of "void(*)(App& app, const UCHAR vKey)".
	* the stored policy can be changed in run time. 
	* has the same access-ablity as the class "App". 
	* default constructor is disabled due to this class is one-to-one class for the "App". 
	* be careful of what policy to be implemented. since the user has "access" to everything in side of the "App".  
*/
class Response {
public:
	Response() = delete;
	Response(App& app) : app(app){}
	// call the responding response to that user inputs.
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