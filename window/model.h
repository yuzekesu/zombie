#pragma once
#include <DirectXMath.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Model {
public:
	Model();
public:
	class Info {
	public:
		Info() = delete;
		Info(std::vector<DirectX::XMFLOAT3> a, std::vector<uint32_t> b);
		const DirectX::XMFLOAT3* get_vertices_raw_ptr();
		const uint32_t* get_indices_raw_ptr();
		const size_t get_vertices_size();
		const size_t get_indices_size();
	private:
		std::vector<DirectX::XMFLOAT3> vertices;
		std::vector<uint32_t> indices;
	};
public:
	const std::shared_ptr<Model::Info> get_info(std::string model_name);
private:
	std::unordered_map<std::string, std::shared_ptr<Model::Info>> models;
};