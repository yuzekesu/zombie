#pragma once
#include <DirectXMath.h>
#include <memory>
#include "unit.h"

class Camera {
public:
	void follow(std::shared_ptr<Unit::Data> unit_data);
	void follow_stop();
	const DirectX::XMVECTOR& get_position();
	const DirectX::XMVECTOR& get_facing();
	const DirectX::XMVECTOR& get_translation();
	void set_position(DirectX::XMVECTOR new_position) {
		position = new_position;
	}
	void set_facing(DirectX::XMVECTOR new_facing) {
		facing = new_facing;
	}
	void set_translation(DirectX::XMVECTOR new_translation) {
		translation = new_translation;
	}
private:
	void transfer_data_to_camera();
private:
	bool is_following = 0;
	std::shared_ptr<Unit::Data> unit_data_following;
	DirectX::XMVECTOR position{ 0.f, 0.f, 0.f, 1.f };
	DirectX::XMVECTOR facing{ 0.f, 0.f, 0.f, 1.f };
	DirectX::XMVECTOR translation{ 0.f, 0.f, 0.f, 1.f };
};