#include "model.h"
#include <cassert>
#include <Windows.h>

Model::Model()
{
	const std::vector <DirectX::XMFLOAT3> cube_vertices = {
		{-1.f, -1.f, -1.f}, // 0
		{ 1.f, -1.f, -1.f}, // 1
		{-1.f,  1.f, -1.f}, // 2
		{-1.f, -1.f,  1.f}, // 3
		{ 1.f,  1.f, -1.f}, // 4
		{ 1.f, -1.f,  1.f}, // 5
		{-1.f,  1.f,  1.f}, // 6
		{ 1.f,  1.f,  1.f}  // 7
	};
	const std::vector <uint32_t> cube_indices = {
		0,4,1,   0,2,4, // front
		0,5,3,   0,1,5, // bottom
		0,3,6,   0,6,2, // left
		1,4,7,   1,7,5, // right
		7,6,3,   7,3,5, // back
		7,2,6,   7,4,2  // top
	};
	auto cube_info = std::make_shared<Model::Info>(cube_vertices, cube_indices);
	models.emplace("cube", std::move(cube_info));
	auto found_iterator_cube = models.find("cube");
	assert(found_iterator_cube != models.end());

	// debug

	/*const uint32_t* a = found_iterator_cube->second->get_indices_raw_ptr();
	for (int i = 0; i < found_iterator_cube->second->get_indices_size(); i++) {
		char test[100];
		_itoa_s(a[i], test, 99, 10);
		OutputDebugStringA(test);
		OutputDebugStringA(", ");
	}
	MessageBox(NULL, L"pause", NULL, NULL);*/
}

const std::shared_ptr<Model::Info> Model::get_info(std::string model_name)
{
	auto found_iterator = models.find(model_name);
	assert(found_iterator != models.end());
	return found_iterator->second;
}

Model::Info::Info(std::vector<DirectX::XMFLOAT3> a, std::vector<uint32_t> b) {
	vertices = std::move(a);
	indices = std::move(b);
}

const DirectX::XMFLOAT3* Model::Info::get_vertices_raw_ptr() {
	return vertices.begin()._Ptr;
}

const uint32_t* Model::Info::get_indices_raw_ptr() {
	return indices.begin()._Ptr;
}

const size_t Model::Info::get_vertices_size() {
	return vertices.size();
}

const size_t Model::Info::get_indices_size() {
	return indices.size();
}

