#include "app.h"

void App::run() {
	MSG msg{};
	while (msg.message != WM_QUIT) {
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			DispatchMessageW(&msg);
			handle_message(msg);
		}
	}
	
}

 void App::handle_message(MSG msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	default:
		break;
	}
}
