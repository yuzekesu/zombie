#pragma once
#include <DirectXMath.h>
#include <memory>
#include "mesh.h"
#include <string>
#include <vector>

class Unit {
public:
	class Data {
	public:
		Unit::Data() = delete;
		Unit::Data(Mesh& mesh, std::string name);
		const DirectX::XMVECTOR& get_position();
		const DirectX::XMVECTOR& get_facing();
		const DirectX::XMVECTOR& get_translation();
		std::shared_ptr<Mesh::Data> get_mesh_data();
		virtual void move(DirectX::XMVECTOR angel, float time_delta);
	private:
		std::string name = "cube";
		std::shared_ptr<Mesh::Data> mesh_data;
		float size = 1.f;
		DirectX::XMVECTOR position{ 0.f, 0.f, 5.f, 1.f };
		DirectX::XMVECTOR facing{ 0.f, 0.f, 0.f, 1.f };
		DirectX::XMVECTOR translation{ 0.f, 0.f, 0.f, 1.f };
	};
public:
	void add_unit_data(std::string name);
	void clear_all_unit_data() {
		units.clear();
	}
	std::shared_ptr<Unit::Data> get_unit_data(size_t offset) {
		return units[offset];
	}
private:
	Mesh mesh;
	std::vector<std::shared_ptr<Unit::Data>> units;
};