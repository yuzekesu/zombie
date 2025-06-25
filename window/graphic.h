#pragma once
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>

class Graphic {
public:
	Graphic() = delete;
	Graphic(HWND hWnd);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
};