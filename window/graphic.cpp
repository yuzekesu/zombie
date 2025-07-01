#pragma comment (lib, "D3Dcompiler.lib")
#include <array>
#include "camera.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "graphic.h"
#include "throw.h"
#include <memory>
#include <Windows.h>
#include <wrl.h>

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

	// get render target view from the swap chain. 

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	THROW_IF_HRESULT(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(pBackBuffer.ReleaseAndGetAddressOf())));
	THROW_IF_HRESULT(pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, &pRenderTargetView));

	// make depth stencil view. 

	D3D11_DEPTH_STENCIL_DESC dsd{};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepth_stencil_state;
	THROW_IF_HRESULT(pDevice->CreateDepthStencilState(&dsd, &pDepth_stencil_state));
	pDeviceContext->OMSetDepthStencilState(pDepth_stencil_state.Get(), 1u);

	// depth stencil texture. 
	RECT window_rect{};
	assert(GetWindowRect(hWnd, &window_rect));
	D3D11_TEXTURE2D_DESC td{};
	td.Width = window_rect.right - window_rect.left;
	td.Height = window_rect.bottom - window_rect.top;
	td.MipLevels = 1u;
	td.ArraySize = 1u;
	td.Format = DXGI_FORMAT_D32_FLOAT;
	td.SampleDesc.Count = 1u;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
	THROW_IF_HRESULT(pDevice->CreateTexture2D(&td, NULL, &pTexture));
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd{};
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0u;
	THROW_IF_HRESULT(pDevice->CreateDepthStencilView(pTexture.Get(), &dsvd, &pDepthStencilView));
	pDeviceContext->OMSetRenderTargets(1u, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());
	clear_view(1.f, 1.f, 1.f, 1.f);
}

void Graphic::clear_view(float r, float g, float b, float a) {
	
	FLOAT color[] = {r, g, b, a};
	pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
	pDeviceContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphic::test_cube_draw(POINT coordinate, RECT window_position, float angel_rotation)
{
	// vertex buffer. 

	struct Vertex { float x; float y; float z; };
	const Vertex cube_vertices[] = {
		{-1.f, -1.f, -1.f}, // 0
		{ 1.f, -1.f, -1.f}, // 1
		{-1.f,  1.f, -1.f}, // 2
		{-1.f, -1.f,  1.f}, // 3
		{ 1.f,  1.f, -1.f}, // 4
		{ 1.f, -1.f,  1.f}, // 5
		{-1.f,  1.f,  1.f}, // 6
		{ 1.f,  1.f,  1.f}  // 7
	};
	D3D11_BUFFER_DESC bd_vertex_buffer{};
	bd_vertex_buffer.ByteWidth = sizeof(cube_vertices); 
	bd_vertex_buffer.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex_buffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex_buffer.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd_vertex_buffer{};
	sd_vertex_buffer.pSysMem = cube_vertices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertex_buffer;
	THROW_IF_HRESULT(pDevice->CreateBuffer(&bd_vertex_buffer, &sd_vertex_buffer, &pVertex_buffer));
	UINT stride = sizeof(Vertex);
	UINT offset = 0u;
	pDeviceContext->IASetVertexBuffers(0u, 1u, pVertex_buffer.GetAddressOf(), &stride, &offset);

	// index buffer for the vertex buffer. 

	//const UINT16 cube_indices[] = {
	//	0,4,1,   0,2,4, // front
	//	0,3,5,   0,5,1, // bottom
	//	0,3,6,   0,6,4, // left
	//	1,4,7,   1,5,7, // right
	//	7,6,3,   7,3,5, // back
	//	7,2,6,   7,4,2  // top
	//};
	const UINT16 cube_indices[] = {
		0,4,1,   0,2,4, // front
		0,5,3,   0,1,5, // bottom
		0,3,6,   0,6,2, // left
		1,4,7,   1,7,5, // right
		7,6,3,   7,3,5, // back
		7,2,6,   7,4,2  // top
	};
	D3D11_BUFFER_DESC bd_index_buffer{};
	bd_index_buffer.ByteWidth = sizeof(cube_indices);
	bd_index_buffer.Usage = D3D11_USAGE_DEFAULT;
	bd_index_buffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index_buffer.StructureByteStride = sizeof(UINT16);
	D3D11_SUBRESOURCE_DATA sd_index_buffer{};
	sd_index_buffer.pSysMem = cube_indices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndex_buffer;
	THROW_IF_HRESULT(pDevice->CreateBuffer(&bd_index_buffer, &sd_index_buffer, &pIndex_buffer));
	pDeviceContext->IASetIndexBuffer(pIndex_buffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	// topologi stuffs for the vertex shader. 

	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// vertex shader.

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob_vertex_shader;
	THROW_IF_HRESULT(D3DReadFileToBlob(L"test_cube_VertexShader.cso", &pBlob_vertex_shader));
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertex_shader;
	THROW_IF_HRESULT(pDevice->CreateVertexShader(pBlob_vertex_shader->GetBufferPointer(), pBlob_vertex_shader->GetBufferSize(), NULL, &pVertex_shader));
	pDeviceContext->VSSetShader(pVertex_shader.Get(), NULL, NULL);

	// input layout for the vertex buffer. 

	D3D11_INPUT_ELEMENT_DESC ied_vertex{};
	ied_vertex.SemanticName = "Position";
	ied_vertex.SemanticIndex = 0u;
	ied_vertex.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	ied_vertex.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInput_layout_vertex;
	THROW_IF_HRESULT(pDevice->CreateInputLayout(&ied_vertex, 1u, pBlob_vertex_shader->GetBufferPointer(), pBlob_vertex_shader->GetBufferSize(), pInput_layout_vertex.GetAddressOf()));
	pDeviceContext->IASetInputLayout(pInput_layout_vertex.Get());
	

	// constant buffer for the vertex shader. 

	struct Constant_Buffer_Vertex { DirectX::XMMATRIX transform; };
	float factor_x_to_y = static_cast<float>(window_position.right - window_position.left) / static_cast<float>(window_position.bottom - window_position.top);
	const Constant_Buffer_Vertex cube_transform_matrix = {
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationX(angel_rotation)*
			DirectX::XMMatrixRotationY(0.65f) *
			DirectX::XMMatrixRotationY(angel_rotation)*
			DirectX::XMMatrixRotationZ(angel_rotation / 10)*
			DirectX::XMMatrixTranslation( 0.f, 0.f, 5.f ) *
			DirectX::XMMatrixPerspectiveFovLH(1.f, factor_x_to_y, 0.5f, 10.f )
		)
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstant_buffer_vertex;
	D3D11_BUFFER_DESC bd_constant_buffer_vertex{};
	bd_constant_buffer_vertex.ByteWidth = sizeof(cube_transform_matrix);
	bd_constant_buffer_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_constant_buffer_vertex.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd_constant_buffer_vertex.CPUAccessFlags = NULL;
	bd_constant_buffer_vertex.MiscFlags = NULL;
	bd_constant_buffer_vertex.StructureByteStride = NULL; // not array of transform matrices. 
	D3D11_SUBRESOURCE_DATA sd_constant_buffer_vertex{};
	sd_constant_buffer_vertex.pSysMem = &cube_transform_matrix;
	THROW_IF_HRESULT(pDevice->CreateBuffer(&bd_constant_buffer_vertex, &sd_constant_buffer_vertex, &pConstant_buffer_vertex));
	pDeviceContext->VSSetConstantBuffers(0u, 1u, pConstant_buffer_vertex.GetAddressOf());

	// pixel shader

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob_pixel_shader;
	THROW_IF_HRESULT(D3DReadFileToBlob(L"test_cube_PixelShader.cso", &pBlob_pixel_shader));
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixel_shader;
	THROW_IF_HRESULT(pDevice->CreatePixelShader(pBlob_pixel_shader->GetBufferPointer(), pBlob_pixel_shader->GetBufferSize(), NULL, &pPixel_shader));
	pDeviceContext->PSSetShader(pPixel_shader.Get(), NULL, NULL);
	
	// constant buffer for the pixel shader. 

	struct Constant_Buffer_Pixel { DirectX::XMFLOAT4 color; };
	const Constant_Buffer_Pixel cube_colors[6] =
	{
		DirectX::XMFLOAT4(0.f, 1.f, 1.f, 1.f),
		DirectX::XMFLOAT4(1.f, 0.f, 0.9f, 1.f),
		DirectX::XMFLOAT4(1.f, 1.f, 0.f, 1.f),
		DirectX::XMFLOAT4(0.f, 0.f, 1.f, 1.f),
		DirectX::XMFLOAT4(0.f, 1.f, 0.f, 1.f),
		DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f)
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstant_buffer_pixel{};
	D3D11_BUFFER_DESC bd_constant_buffer_pixel{};
	bd_constant_buffer_pixel.ByteWidth = sizeof(cube_colors);
	bd_constant_buffer_pixel.StructureByteStride = 0u;
	bd_constant_buffer_pixel.Usage = D3D11_USAGE_DEFAULT;
	bd_constant_buffer_pixel.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	D3D11_SUBRESOURCE_DATA sd_constant_buffer_pixel{};
	sd_constant_buffer_pixel.pSysMem = &cube_colors;
	THROW_IF_HRESULT(pDevice->CreateBuffer(&bd_constant_buffer_pixel, &sd_constant_buffer_pixel, &pConstant_buffer_pixel));
	pDeviceContext->PSSetConstantBuffers(0u, 1u, pConstant_buffer_pixel.GetAddressOf());

	// binding render target. DID IN THE CONSTRUCTOR WITH DEPTH STENCIL. 

	//pDeviceContext->OMSetRenderTargets(1u, pRenderTargetView.GetAddressOf(), NULL);

	// set viewport. 
	D3D11_VIEWPORT vp{};
	vp.Width = static_cast<FLOAT>(window_position.right - window_position.left);
	vp.Height = static_cast<FLOAT>(window_position.bottom - window_position.top);
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	pDeviceContext->RSSetViewports(1u, &vp);

	// draw. 

	pDeviceContext->DrawIndexed(static_cast<UINT>(std::size(cube_indices)), 0u, 0u);
}

void Graphic::draw_single_unit(HWND hWnd, std::shared_ptr<Unit::Data> unit_data, Camera& camera)
{
	std::shared_ptr<Mesh::Data> mesh_data = unit_data->get_mesh_data();

	// vertex buffer

	D3D11_BUFFER_DESC bd_vertex{};
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.ByteWidth = static_cast<UINT>(sizeof(DirectX::XMFLOAT3) * mesh_data->get_vertices_size());
	bd_vertex.CPUAccessFlags = 0u;
	bd_vertex.MiscFlags = 0u;
	bd_vertex.StructureByteStride = static_cast <UINT>(sizeof(DirectX::XMFLOAT3));
	D3D11_SUBRESOURCE_DATA sd_vertex{};
	sd_vertex.pSysMem = mesh_data->get_vertices_raw_ptr();
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertex_buffer;
	THROW_IF_HRESULT(pDevice->CreateBuffer(&bd_vertex, &sd_vertex, &pVertex_buffer));
	UINT stride = static_cast<UINT>(sizeof(DirectX::XMFLOAT3));
	UINT offset = 0u;
	pDeviceContext->IASetVertexBuffers(0u, 1u, pVertex_buffer.GetAddressOf(), &stride, &offset);

	// index buffer

	D3D11_BUFFER_DESC bd_index{};
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.ByteWidth = static_cast<UINT>(sizeof(uint32_t) * mesh_data->get_indices_size());
	bd_index.CPUAccessFlags = 0u;
	bd_index.MiscFlags = 0u;
	bd_index.StructureByteStride = sizeof(uint32_t);
	D3D11_SUBRESOURCE_DATA sd_index{};
	sd_index.pSysMem = mesh_data->get_indices_raw_ptr();
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndex_buffer;
	THROW_IF_HRESULT(pDevice->CreateBuffer(&bd_index, &sd_index, &pIndex_buffer));
	pDeviceContext->IASetIndexBuffer(pIndex_buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);

	// vertex shader. 

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob_vertex_shader;
	THROW_IF_HRESULT(D3DReadFileToBlob(L"debug_VertexShader.cso", &pBlob_vertex_shader));
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertex_shader;
	THROW_IF_HRESULT(pDevice->CreateVertexShader(pBlob_vertex_shader->GetBufferPointer(), pBlob_vertex_shader->GetBufferSize(), NULL, &pVertex_shader));
	pDeviceContext->VSSetShader(pVertex_shader.Get(), NULL, NULL);

	// input layout.

	D3D11_INPUT_ELEMENT_DESC ied{};
	ied.AlignedByteOffset = 0u;
	ied.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	ied.InputSlot = 0u;
	ied.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	ied.InstanceDataStepRate = 0u;
	ied.SemanticIndex = 0;
	ied.SemanticName = "POSITION";
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInput_layout;
	THROW_IF_HRESULT(pDevice->CreateInputLayout(&ied, 1u, pBlob_vertex_shader->GetBufferPointer(), pBlob_vertex_shader->GetBufferSize(), &pInput_layout));
	pDeviceContext->IASetInputLayout(pInput_layout.Get());
	
	// topologi

	pDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// pixel shader.

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob_pixel_shader;
	THROW_IF_HRESULT(D3DReadFileToBlob(L"debug_PixelShader.cso", &pBlob_pixel_shader));
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixel_shader;
	THROW_IF_HRESULT(pDevice->CreatePixelShader(pBlob_pixel_shader->GetBufferPointer(), pBlob_pixel_shader->GetBufferSize(), NULL, &pPixel_shader));
	pDeviceContext->PSSetShader(pPixel_shader.Get(), NULL, NULL);

	// set viewport. 
	D3D11_VIEWPORT vp{};
	RECT window_position{};
	GetWindowRect(hWnd, &window_position);
	vp.Width = static_cast<FLOAT>(window_position.right - window_position.left);
	vp.Height = static_cast<FLOAT>(window_position.bottom - window_position.top);
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	pDeviceContext->RSSetViewports(1u, &vp);

	// constant buffer for the vertex shader. 

	struct Constant_Buffer_Vertex { DirectX::XMMATRIX transform; };
	float factor_x_to_y = static_cast<float>(window_position.right - window_position.left) / static_cast<float>(window_position.bottom - window_position.top);
	float x_delta = unit_data->get_position().m128_f32[0] - camera.get_position().m128_f32[0];
	float y_delta = unit_data->get_position().m128_f32[1] - camera.get_position().m128_f32[1];
	float z_delta = unit_data->get_position().m128_f32[2] - camera.get_position().m128_f32[2];
	const Constant_Buffer_Vertex cube_transform_matrix = {
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationRollPitchYawFromVector(unit_data->get_facing()) *
			/*DirectX::XMMatrixRotationX(unit_data->get_facing().m128_f32[0]) *
			DirectX::XMMatrixRotationY(unit_data->get_facing().m128_f32[1]) *
			DirectX::XMMatrixRotationZ(unit_data->get_facing().m128_f32[2]) **/
			
			DirectX::XMMatrixTranslation(x_delta, y_delta, z_delta) * 
			//DirectX::XMMatrixTranslation(unit_data->get_position().m128_f32[0], unit_data->get_position().m128_f32[1], unit_data->get_position().m128_f32[2]) * 
			DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixRotationRollPitchYawFromVector(camera.get_facing())) *
			/*DirectX::XMMatrixRotationRollPitchYawFromVector(camera.get_facing()) **/
			/*DirectX::XMMatrixRotationX(camera.get_facing().m128_f32[0]) *
			DirectX::XMMatrixRotationY(camera.get_facing().m128_f32[1]) *
			DirectX::XMMatrixRotationZ(camera.get_facing().m128_f32[2]) * */
			DirectX::XMMatrixPerspectiveFovLH(1.f, factor_x_to_y, 0.5f, 10.f)
		)
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstant_buffer_vertex;
	D3D11_BUFFER_DESC bd_constant_buffer_vertex{};
	bd_constant_buffer_vertex.ByteWidth = sizeof(cube_transform_matrix);
	bd_constant_buffer_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_constant_buffer_vertex.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd_constant_buffer_vertex.CPUAccessFlags = NULL;
	bd_constant_buffer_vertex.MiscFlags = NULL;
	bd_constant_buffer_vertex.StructureByteStride = NULL; // not array of transform matrices. 
	D3D11_SUBRESOURCE_DATA sd_constant_buffer_vertex{};
	sd_constant_buffer_vertex.pSysMem = &cube_transform_matrix;
	THROW_IF_HRESULT(pDevice->CreateBuffer(&bd_constant_buffer_vertex, &sd_constant_buffer_vertex, &pConstant_buffer_vertex));
	pDeviceContext->VSSetConstantBuffers(0u, 1u, pConstant_buffer_vertex.GetAddressOf());

	// draw. 

	pDeviceContext->DrawIndexed(static_cast<UINT>(mesh_data->get_indices_size()), 0u, 0u);
}
