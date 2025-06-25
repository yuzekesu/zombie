#include "graphic.h"

Graphic::Graphic(HWND hWnd) {
	DXGI_SWAP_CHAIN_DESC dc{};
	dc.BufferDesc.Width = 0u;
	dc.BufferDesc.Height = 0u;
	dc.BufferDesc.RefreshRate.Numerator = 30u;
	dc.BufferDesc.RefreshRate.Denominator = 1u;
	dc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	dc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	dc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	dc.SampleDesc.Count = 1;
	dc.SampleDesc.Quality = 0;
	dc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	dc.BufferCount = 1;
	dc.OutputWindow = hWnd;
	dc.Windowed = TRUE;
	dc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	dc.Flags = 0u;
	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		6u,
		D3D11_SDK_VERSION,
		&dc,
		&pSwapChain,
		&pDevice,
		NULL,
		&pDeviceContext);
}
