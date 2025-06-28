#include "throw.h"
#include <comdef.h>
#include <iomanip>
#include <sstream>

void Throw::HResult::throw_if(HRESULT hr, const char* function, const char* file, const int line) {
	{
		_com_error error = _com_error(hr);
		std::wstringstream str;
		str << error.ErrorMessage() << "\n" << "\n" << "\n";
		str << "[HRESULT]: " << "0x" << std::uppercase << std::hex << hr << "\n" << std::dec;
		str << "[FILE]: " << file << "\n";
		str << "[LINE]: " << line << "\n";
		str << "[FUNCTION]: " << function << "\n";
		MessageBox(NULL, str.str().c_str(), NULL, NULL);
		throw(hr);
	}
}