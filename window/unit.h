#pragma once
#include <DirectXMath.h>
#include <memory>
#include "model.h"
#include <string>
#include <vector>

class Unit {
public:
	void add_unit(std::string name);
public:
	class Data {
	public:
		Unit::Data() = delete;
		Unit::Data(Model& model, std::string name);
		const DirectX::XMVECTOR& get_position();
		const DirectX::XMVECTOR& get_facing();
		const DirectX::XMVECTOR& get_translation();
		virtual void move(DirectX::XMVECTOR angel, float time_delta);
	private:
		std::string name = "cube";
		std::shared_ptr<Model::Data> model_data;
		float size = 1.f;
		DirectX::XMVECTOR position{ 0.f, 0.f, 0.f, 1.f };
		DirectX::XMVECTOR facing{ 0.f, 0.f, 0.f, 1.f };
		DirectX::XMVECTOR translation{ 0.f, 0.f, 0.f, 1.f };
	};
private:
	Model model;
	std::vector<std::shared_ptr<Unit::Data>> pack;
};