#pragma once
#include <DirectXMath.h>
#include <memory>
#include "models.h"
#include <string>
#include <vector>

class Units {
public:
	void add_unit(std::string name);
public:
	class Info {
	public:
		Units::Info() = delete;
		Units::Info(Models& models, std::string name);
		virtual void move(DirectX::XMVECTOR angel, float time_delta);
	private:
		std::string name = "cube";
		std::shared_ptr<Models::Info> model;
		float size = 1.f;
		DirectX::XMVECTOR position{ 0.f, 0.f, 0.f, 1.f };
		DirectX::XMVECTOR facing{ 0.f, 0.f, 0.f, 1.f };
		DirectX::XMVECTOR translation{ 0.f, 0.f, 0.f, 1.f };
	};
private:
	Models models;
	std::vector<std::shared_ptr<Units::Info>> units;
};