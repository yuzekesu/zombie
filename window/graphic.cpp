#include "graphic.h"
#include "throw.h"

Graphic::Graphic(HWND hWnd) {
	DXGI_SWAP_CHAIN_DESC dc{};
	dc.BufferDesc.Width = 0u;
	dc.BufferDesc.Height = 0u;
	dc.BufferDesc.RefreshRate.Numerator = 30u;
	dc.BufferDesc.RefreshRate.Denominator = 1u;
	dc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	dc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	dc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	dc.SampleDesc.Count = 1u;
	dc.SampleDesc.Quality = 0u;
	dc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dc.BufferCount = 1u;
	dc.OutputWindow = hWnd;
	dc.Windowed = TRUE;
	dc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	dc.Flags = 0u;
	THROW_IF_HRESULT(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &dc, &pSwapChain, &pDevice, NULL, &pDeviceContext));
	clearRenderTargetView(1.f, 1.f, 1.f, 1.f);
}

void Graphic::clearRenderTargetView(float r, float g, float b, float a) {
	ID3D11Resource* pBackBuffer = nullptr;
	THROW_IF_HRESULT(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer)));
	THROW_IF_HRESULT(pDevice->CreateRenderTargetView(pBackBuffer, NULL, pRenderTargetView.GetAddressOf()));
	pBackBuffer->Release();
	FLOAT color[] = {r, g, b, a};
	pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
}
