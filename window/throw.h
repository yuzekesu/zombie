#pragma once
#include <Windows.h>

#ifndef NDEBUG
#define THROW_IF_HRESULT(function) OutputDebugString(L"|----------BREAK----------|\n"); if (HRESULT hr = function; FAILED(hr)) {Throw::HResult::throw_if(hr, #function, __FILE__, __LINE__);}
#endif // !NDEBUG

class Throw {
public:
	class HResult {
	public:
		static void throw_if(HRESULT hr, const char* function, const char* file, const int line);
	};
};
