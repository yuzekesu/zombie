#include <Windows.h>
#include "app.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nShowCmd) {
	try {
		App game;
		game.run();
	}
	catch (...) {
		return 1;
	}
	return 0;
}