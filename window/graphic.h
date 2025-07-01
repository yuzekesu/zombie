#pragma once
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include "unit.h"
#include <Windows.h>
#include <wrl.h>

class Graphic {
public:
	Graphic() = delete;
	Graphic(HWND hWnd);
	void present() {
		pSwapChain->Present(1u, 0u);
	}
	void clear_view(float r, float g, float b, float a = 1.f);
	void test_cube_draw(POINT coordinate, RECT window_position, float angel_rotation);
	void draw_single_unit(HWND hWnd, std::shared_ptr<Unit::Data> unit_data, Camera& camera);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
};